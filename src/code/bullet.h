#pragma once

#include "../nexa.h"

typedef struct {
	int x;
	int y;
	int vy;
	nxRectangle bounds;
} Bullet;

Bullet create_bullet(int x, int y, int vy);
void update_bullets(Bullet* bullets, int* bullet_count, float dt);
void render_bullets(nxContext* ctx, Bullet* bullets, int bullet_count);