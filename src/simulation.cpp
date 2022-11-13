#include "simulation.hpp"
#include "PerlinNoise.hpp"
#include "quickmath.h"

siv::PerlinNoise perlin{123456u};

sim::Chunk::Chunk()
{

}

sim::Chunk::~Chunk()
{
	SDL_DestroyTexture(tex);
}

void sim::Chunk::init(SDL_Renderer* renderer)
{
	tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SIM_CHUNK_SIZE, SIM_CHUNK_SIZE);

	for(int i = 0; i < SIM_CHUNK_SIZE; i++)
	for(int j = 0; j < SIM_CHUNK_SIZE; j++)
		p[i][j] = {};
}

void sim::Chunk::gen(int x, int y)
{
	for(int i = 0; i < SIM_CHUNK_SIZE; i++)
	for(int j = 0; j < SIM_CHUNK_SIZE; j++)
	{
		double noise = perlin.octave2D_01((j + x) * 0.05, (i + y) * 0.125, 4);

		if(noise > 0.65)
			p[j][i].type = Particle::Dirt;
		else
			p[j][i].type = Particle::Air;
	}

	for(int i = 0; i < SIM_CHUNK_SIZE; i++)
	for(int j = 0; j < SIM_CHUNK_SIZE; j++)
	{
		QMvec2 normal = {0.0f, 0.0f};

		if(p[j][i].type == Particle::Air)
			continue;

		const int normalRad = 2;
		for(int i2 = i - normalRad; i2 <= i + normalRad; i2++)
		for(int j2 = j - normalRad; j2 <= j + normalRad; j2++)
		{
			if(i2 == i && j2 == j)
				continue;

			bool solid;

			if(i2 < 0 || i2 >= SIM_CHUNK_SIZE || j2 < 0 || j2 >= SIM_CHUNK_SIZE)
				solid = perlin.octave2D_01((j2 + x) * 0.05, (i2 + y) * 0.125, 4) > 0.65;
			else
				solid = p[j2][i2].type != Particle::Air;

			if(solid)
			{
				QMvec2 toCenter = {(float)j2 - j, (float)i2 - i};
				float dist = QM_vec2_dot(toCenter, toCenter);
				dist *= dist;
				toCenter = QM_vec2_scale(toCenter, 1.0f / dist);
				normal = QM_vec2_add(normal, toCenter);
			}
		}

		if(QM_vec2_dot(normal, normal) < 0.01f)
			normal = {0.0f, 0.0f};
		else
			normal = QM_vec2_normalize(normal);

		p[j][i].vx = normal.x;
		p[j][i].vy = normal.y;

		float dot = QM_vec2_dot(normal, {0.0f, 1.0f});
		if(dot > 0.9f)
			p[j][i].type = Particle::Water;
		else if(dot < -0.1f)
			p[j][i].type = Particle::Dirt;
		else
			p[j][i].type = Particle::Sand;
	}
}

void sim::Chunk::render(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	Color* pix;
	int pitch;
	SDL_LockTexture(tex, NULL, (void**)&pix, &pitch);

	for(int i = 0; i < SIM_CHUNK_SIZE; i++)
	for(int j = 0; j < SIM_CHUNK_SIZE; j++)
	{
		Color col;
		switch(p[j][i].type)
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

		pix[j + i * SIM_CHUNK_SIZE] = col;
	}

	SDL_UnlockTexture(tex);
	SDL_Rect dstRect = {x, y, w, h};
	SDL_RenderCopy(renderer, tex, NULL, &dstRect);
}

//---------------------------------------------------------------------------------//

sim::World::World(SDL_Renderer* renderer, int w, int h)
{
	this->w = w;
	this->h = h;

	c = new Chunk[w * h]();

	for(int i = 0; i < w * h; i++)
		c[i].init(renderer);
}

sim::World::~World()
{
	delete[] c;
}

void sim::World::gen(unsigned int seed)
{
	perlin.reseed(seed);

	for(int y = 0; y < h; y++)
	for(int x = 0; x < w; x++)
		c[x + y * w].gen(x * SIM_CHUNK_SIZE, y * SIM_CHUNK_SIZE);
}

void sim::World::render(SDL_Renderer* renderer, int camX, int camY, int renderSize)
{
	for(int y = 0; y < h; y++)
	for(int x = 0; x < w; x++)
		c[x + y * w].render(renderer, x * renderSize - camX, y * renderSize - camY, renderSize, renderSize);
}