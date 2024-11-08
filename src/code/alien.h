#pragma once

#include "../nexa.h"

typedef struct {
	int x;
	int y;
	int vy;
	nxRectangle bounds;
} Alien;

void init_aliens();
Alien create_alien(int vy);
void update_aliens(Alien* aliens, int* alien_count, float dt);
void render_aliens(nxContext* ctx, Alien* aliens, int alien_count);