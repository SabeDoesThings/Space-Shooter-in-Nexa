#pragma once

#include "../nexa.h"

typedef struct {
	float x;
	float y;
	float speed;
	int size;
	nxColor color;
} Particle;

Particle* generate_particles(int n, int width, int height, nxColor color);
void update_particles(Particle* particles, int n, int width, int height, float dt, float speed);
void render_particles(nxContext* ctx, Particle* particles, int n);