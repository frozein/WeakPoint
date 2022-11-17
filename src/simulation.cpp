#include "simulation.hpp"
#include "SDL_image.h"
#include "globals.hpp"

//---------------------------------------------------------------------------------//

sim::World::World(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* map = IMG_Load(path);
	if(map == NULL)
	{
		printf("ERROR OPENING FILE \"%s\"", path);
		return;
	}

	this->w = map->w;
	this->h = map->h;
	p = new Particle[w * h];
	tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, w, h);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	SDL_LockSurface(map);

	Color* pixels = (Color*)map->pixels;
	for(int i = 0; i < w * h; i++)
	{
		p[i].xVel = 0.0f;
		p[i].yVel = 0.0f;
		p[i].updated = false;

		if(pixels[i].a == 0)
		{
			p[i].type = Particle::AIR;
			p[i].flag = Particle::EMPTY;
		}
		else if(pixels[i].r == 255 && pixels[i].g == 255 && pixels[i].b == 0)
		{
			p[i].type = Particle::SAND;
			p[i].flag = Particle::SOLID;
			p[i].freeFall = false;
		}
		else if(pixels[i].r == 0 && pixels[i].g == 0 && pixels[i].b == 0)
		{
			p[i].type = Particle::STONE;
			p[i].flag = Particle::SOLID;
			p[i].freeFall = false;
		}
		else if(pixels[i].r == 0 && pixels[i].g == 0 && pixels[i].b == 255)
		{
			p[i].type = Particle::WATER;
			p[i].flag = Particle::LIQUID;
		}
		else
		{
			p[i].type = Particle::AIR;
			p[i].flag = Particle::EMPTY;
		}

	}

	SDL_UnlockSurface(map);

	#if !DANIEL

	SDL_FreeSurface(map); //for some reason this causes a crash????

	#endif

	srand(123456);
}

sim::World::~World()
{
	delete[] p;
	SDL_DestroyTexture(tex);
}

void sim::World::inner_sim_loop(int x)
{
	for(int y = h - 1; y >= 0; y--)
	{
		switch(get_p(x, y)->type)
		{
		case Particle::SAND:
			update_sand(x, y);
			break;
		case Particle::WATER:
			update_water(x, y);
			break;
		}
	}
}

void sim::World::update()
{
	static bool dir = true;
	dir = !dir;

	if(dir)
		for(int x = 0; x < w; x++)
			inner_sim_loop(x);
	else
		for(int x = w - 1; x >= 0; x--)
			inner_sim_loop(x);

	for(int i = 0; i < w * h; i++)
		p[i].updated = false;
}

void sim::World::render(SDL_Renderer* renderer, int camX, int camY, int renderSize)
{
	Color* pix;
	int pitch;
	SDL_LockTexture(tex, NULL, (void**)&pix, &pitch);

	for(int i = 0; i < h; i++)
	for(int j = 0; j < w; j++)
	{
		Color col;
		switch(p[j + i * w].type)
		{
		case Particle::AIR:
		{
			col = {0, 0, 0, 0};
			break;
		}
		case Particle::STONE:
		{
			col = {50, 50, 50, 255};
			break;
		}
		case Particle::WATER:
		{
			col = {0, 0, 255, 255};
			break;
		}
		case Particle::SAND:
		{
			col = {255, 255, 0, 255};
			break;
		}
		}

		pix[j + i * w] = col;
	}

	SDL_UnlockTexture(tex);
	SDL_Rect dstRect = {-camX, -camY, renderSize * w, renderSize * h};
	SDL_RenderCopy(renderer, tex, NULL, &dstRect);
}

//---------------------------------------------------------------------------------//

sim::Particle* sim::World::get_p(int x, int y)
{
	return &p[x + y * w];
}

bool sim::World::in_bounds(int x, int y)
{
	return x >= 0 && x < w && y >= 0 && y < h;
}

void sim::World::swap(int x1, int y1, int x2, int y2)
{
	Particle temp = p[x1 + y1 * w];
	p[x1 + y1 * w] = p[x2 + y2 * w];
	p[x2 + y2 * w] = temp;
}

const float MAX_VELOCITY = 3.0f;
const float GRAVITY_ACCELERATION = 0.1f;
const float FRICTION = 0.5f;

void sim::World::update_sand(int x, int y)
{
	const float SPREAD = 1.5f;
	const int INERTIAL_RESIST = 2;
	const int SLIP_CHANCE = 1000;

	int dir = rand() % 2 == 0 ? 1 : -1; //random direction for setting xVel and diagonal moving
	Particle* p = get_p(x, y);

	//setting last pos:
	p->lastX = x;
	p->lastY = y;

	//updating x and xVel:
	int xVelSign = (p->xVel > 0) - (p->xVel < 0);
	for (int i = 0; i < fabs(round(p->xVel)); i++)
	{
		if (in_bounds(x + xVelSign, y) && get_p(x + xVelSign, y)->flag != Particle::SOLID)
		{
			swap(x, y, x + xVelSign, y);
			x += xVelSign;

			p = get_p(x, y);
			if (in_bounds(x, y + 1) && get_p(x, y + 1)->flag == Particle::SOLID)
				p->xVel -= FRICTION;
		}
		else
		{
			p->xVel = 0.0f;
		}
	}

	//updating y and yVel:
	bool fell = false; //for telling if the particle fell vertically
	p->yVel = fmin(p->yVel + GRAVITY_ACCELERATION, MAX_VELOCITY);
	for (int i = 0; i < round(p->yVel) + 1; i++)
	{
		if (in_bounds(x, y + 1) && get_p(x, y + 1)->flag != Particle::SOLID)
		{
			swap(x, y, x, y + 1);
			y++;

			p = get_p(x, y);
			fell = true;
		}
		else
		{
			p->xVel = p->yVel * dir / SPREAD;
			p->yVel = 0.0;
			break;
		}
	}

	//checking for diagonal movement (add random chance to slip):
	if (!fell && (p->freeFall || (rand() % SLIP_CHANCE) == 1))
	{
		if (in_bounds(x + dir, y + 1) && get_p(x + dir, y + 1)->flag != Particle::SOLID)
		{
			swap(x, y, x + dir, y + 1);
			y++;
			x += dir;
		}
		else if (in_bounds(x - dir, y + 1) && get_p(x - dir, y + 1)->flag != Particle::SOLID)
		{
			swap(x, y, x - dir, y + 1);
			y++;
			x -= dir;
		}
	}

	//setting freeFall:
	p = get_p(x, y);
	if (p->lastX == x && p->lastY == y)
		p->freeFall = false;
	else
		p->freeFall = true;

	//setting freeFall for nearby particles:
	if (p->freeFall)
	{
		bool change = rand() % INERTIAL_RESIST == 1;

		if (in_bounds(x, y + 1) && get_p(x, y + 1)->flag == Particle::SOLID && !get_p(x, y + 1)->freeFall)
			get_p(x, y + 1)->freeFall = change;
		if (in_bounds(x + 1, y) && get_p(x + 1, y)->flag == Particle::SOLID && !get_p(x + 1, y)->freeFall)
			get_p(x + 1, y)->freeFall = change;
		if (in_bounds(x - 1, y) && get_p(x - 1, y)->flag == Particle::SOLID && !get_p(x - 1, y)->freeFall)
			get_p(x - 1, y)->freeFall = change;
	}
}

void sim::World::update_water(int x, int y)
{
	const int spreadDist = 4;

	int dir = rand() % 2 == 0 ? 1 : -1; //random direction for setting xVel and diagonal moving
	Particle* p = get_p(x, y);

	//updating y and yVel:
	bool fell = false; //for telling if the particle fell vertically
	p->yVel = fmin(p->yVel + GRAVITY_ACCELERATION, MAX_VELOCITY);
	for (int i = 0; i < round(p->yVel) + 1; i++)
	{
		if (in_bounds(x, y + 1) && (get_p(x, y + 1)->flag == Particle::EMPTY))
		{
			swap(x, y, x, y + 1);
			y++;

			p = get_p(x, y);
			fell = true;
		}
		else
		{
			p->yVel = 0.0;
			break;
		}
	}

	//checking for diagonal and lateral movement
	if (!fell)
	{
		if (in_bounds(x + dir, y + 1) && (get_p(x + dir, y + 1)->flag == Particle::EMPTY))
		{
			swap(x, y, x + dir, y + 1);
			y++;
			x += dir;
		}
		else if (in_bounds(x - dir, y + 1) && (get_p(x - dir, y + 1)->flag == Particle::EMPTY))
		{
			swap(x, y, x - dir, y + 1);
			y++;
			x -= dir;
		}
		else if (in_bounds(x + dir, y) && (get_p(x + dir, y)->flag == Particle::EMPTY))
		{
			swap(x, y, x + dir, y);
			x += dir;

			//iterate to find furthest lateral movement location
			for (int i = 1; i < spreadDist; i++)
			{
				if (in_bounds(x + dir, y) && (get_p(x + dir, y)->flag == Particle::EMPTY))
				{
					swap(x, y, x + dir, y);
					x += dir;
				}
				else
					break;
			}
		}
		else if (in_bounds(x - dir, y) && (get_p(x - dir, y)->flag == Particle::EMPTY))
		{
			swap(x, y, x - dir, y);
			x -= dir;

			//iterate to find furthest lateral movement location
			for (int i = 1; i < spreadDist; i++)
			{
				if (in_bounds(x - dir, y) && (get_p(x - dir, y)->flag == Particle::EMPTY))
				{
					swap(x, y, x - dir, y);
					x -= dir;
				}
				else
					break;
			}
		}
	}
}