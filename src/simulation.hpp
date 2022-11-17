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
	float xVel, yVel;
	int lastX, lastY;
	bool freeFall;
	bool updated;

	enum Type
	{
		AIR,
		SAND,
		WATER,
		STONE
	} type;

	enum Flag
	{
		LIQUID,
		SOLID,
		EMPTY
	} flag;
};

class World //TODO: infinite terrain
{
private:
	SDL_Texture* tex;

	bool in_bounds(int x, int y);
	void swap(int x1, int y1, int x2, int y2);

	void update_sand (int x, int y);
	void update_water(int x, int y);

	void inner_sim_loop(int x);

public:
	int w, h;
	Particle* p;

	World(SDL_Renderer* renderer, const char* path);
	~World();

	Particle* get_p(int x, int y);

	void update();
	void render(SDL_Renderer* renderer, int camX, int camY, int renderSize);
};

}

#endif