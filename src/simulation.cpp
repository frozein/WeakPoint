#include "simulation.hpp"

sim::Chunk::Chunk(SDL_Renderer* renderer)
{
	tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SIM_CHUNK_SIZE, SIM_CHUNK_SIZE);

	for(int i = 0; i < SIM_CHUNK_SIZE; i++)
	for(int j = 0; j < SIM_CHUNK_SIZE; j++)
		p[i][j] = {};
}

sim::Chunk::~Chunk()
{
	SDL_DestroyTexture(tex);
}

void sim::Chunk::render(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	Color* pix;
	int pitch;
	SDL_LockTexture(tex, NULL, (void**)&pix, &pitch);

	for(int i = 0; i < SIM_CHUNK_SIZE; i++)
	for(int j = 0; j < SIM_CHUNK_SIZE; j++)
	{
		uint8_t col  = (uint8_t)(((float)i / SIM_CHUNK_SIZE) * 255);
		uint8_t col2 = (uint8_t)(((float)j / SIM_CHUNK_SIZE) * 255);
		pix[j + i * SIM_CHUNK_SIZE] = {col, col2, 30, 255};
	}

	SDL_UnlockTexture(tex);
	SDL_Rect dstRect = {x, y, w, h};
	SDL_RenderCopy(renderer, tex, NULL, &dstRect);
}