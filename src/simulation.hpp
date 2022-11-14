#ifndef SIMULATION_H
#define SIMULATION_H

#include "SDL.h"
#include <stdint.h>

namespace sim
{

//TODO: move this somewhere else
struct Color
{
	uint8_t r, g, b, a;
};

struct Particle
{
	float vx, vy;
	bool updated;

	enum Type
	{
		Air,
		Sand,
		Water,
		Dirt
	} type;
};

class World //TODO: infinite terrain
{
private:
	SDL_Texture* tex;

public:
	int w, h;
	Particle* p;

	World(SDL_Renderer* renderer, const char* path);
	~World();

	void update();
	void render(SDL_Renderer* renderer, int camX, int camY, int renderSize);
};

}

#endif