#include "simulation.hpp"
#include "quickmath.h"
#include "SDL_image.h"

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

	SDL_LockSurface(map);

	Color* pixels = (Color*)map->pixels;
	for(int i = 0; i < w * h; i++)
	{
		if(pixels[i].a == 0)
			p[i].type = Particle::Air;
		else if(pixels[i].r == 255 && pixels[i].g == 255 && pixels[i].b == 0)
			p[i].type = Particle::Sand;
		else if(pixels[i].r == 0 && pixels[i].g == 0 && pixels[i].b == 0)
			p[i].type = Particle::Dirt;
		else
			p[i].type = Particle::Air;

	}

	SDL_UnlockSurface(map);
	//SDL_FreeSurface(map); //for some reason this causes a crash????
}

sim::World::~World()
{
	delete[] p;
	SDL_DestroyTexture(tex);
}

void sim::World::update()
{
	
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
		case Particle::Air:
		{
			col = {};
			break;
		}
		case Particle::Dirt:
		{
			col = {50, 50, 50, 255};
			break;
		}
		case Particle::Water:
		{
			col = {0, 0, 255, 255};
			break;
		}
		case Particle::Sand:
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