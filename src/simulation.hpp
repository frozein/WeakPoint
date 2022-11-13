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

class World;

#define SIM_CHUNK_SIZE 64 
class Chunk
{
private:
	SDL_Texture* tex;

public:
	Particle p[SIM_CHUNK_SIZE][SIM_CHUNK_SIZE];

	Chunk();
	~Chunk();
	void init(SDL_Renderer* renderer);

	void gen(int x, int y);
	void render(SDL_Renderer* renderer, int x, int y, int w, int h);
};

class World //TODO: infinite terrain
{
public:
	int w, h;
	Chunk* c;

	World(SDL_Renderer* renderer, int w, int h);
	~World();

	void gen(unsigned int seed);

	void update();
	void render(SDL_Renderer* renderer, int camX, int camY, int renderSize);
};

}

#endif