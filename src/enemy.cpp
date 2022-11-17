#include "enemy.hpp"
#include "SDL.h"
#include "random"

Enemy::Enemy(QMvec2 p)
{
	spawnTime = SDL_GetTicks();
	dropTime = spawnTime + ANIM_TIME + 10000; //todo replace with random
	pos = p;
	angle = ((float)rand() / RAND_MAX) * 2.0f * 3.14159f;
}

bool Enemy::update()
{
	return SDL_GetTicks() >= dropTime;
}

void Enemy::render()
{

}