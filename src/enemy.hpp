#include "quickmath.h"

class Enemy
{
private:
	QMvec2 pos;
	float angle;
	unsigned int spawnTime;
	unsigned int dropTime;
	const unsigned int ANIM_TIME = 5000;

public:
	Enemy(QMvec2 p);

	bool update();
	void render();

	//0 = miss, 1 = hit, wrong angle, 2 = proper hit
	int try_hit(QMvec2 pos, QMvec2 dir, float* dist);
};