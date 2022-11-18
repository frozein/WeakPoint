#include "enemy.hpp"
#include "SDL.h"
#include "random"
#include "io/graphics.hpp"

Enemy::Enemy(QMvec2 p)
{
	spawnTime = SDL_GetTicks();
	dropTime = spawnTime + ANIM_TIME + 10000; //todo replace with random
	pos = p;
	angle = ((float)rand() / RAND_MAX) * 2.0f * 3.14159f;
}

bool Enemy::update()
{
	return true;
}

void Enemy::render()
{
	unsigned int ticks = SDL_GetTicks();
	float t = (ticks - spawnTime) < ANIM_TIME ? (float)(ticks - spawnTime) / ANIM_TIME : 1.0f;
	t = 1.0f - powf(2.0f, -10.0f * t);

	//animate:
	QMvec2 renderPos = {pos.x, pos.y * t + (pos.y - 300.0f) * (1.0f - t)};
	float renderSize = t;

	TextureAttributes attrib = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, {0, 0, 1, 1}, {(int)renderPos.x, (int)renderPos.y, 300, 300}, 
												 angle, NULL, SDL_FLIP_NONE, {255, 255, 255, 255}, true, renderSize);
	graphics::render_texture(attrib);
}