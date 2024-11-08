#include "../nexa.h"
#include "particle.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

Particle* generate_particles(int n, int width, int height, nxColor color) {
	Particle* particles = (Particle*)malloc(n * sizeof(Particle));
	if (particles == NULL) return NULL;

	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		particles[i].x = ((float)rand() / RAND_MAX) * width;
        particles[i].y = ((float)rand() / RAND_MAX) * height;
        particles[i].speed = 2.0f + ((float)rand() / RAND_MAX) * 3.0f;
        particles[i].size = 2 + rand() % 2; 
        particles[i].color = color;
	}

	return particles;
}

void update_particles(Particle* particles, int n, int width, int height, float dt, float speed) {
	for (int i = 0; i < n; i++) {
        particles[i].y += particles[i].speed * dt * speed;
        if (particles[i].y > height) {
            particles[i].y = 0;
            particles[i].x = rand() % width;
            particles[i].speed = 2.0f + (rand() % 3);
            particles[i].size = 2 + (rand() % 3);
        }
    }
}

void render_particles(nxContext* ctx, Particle* particles, int n) {
	for (int i = 0; i < n; i++) {
        nx_render_rect_filled(ctx, (int)(particles[i].x), (int)(particles[i].y), particles[i].size, particles[i].size, particles[i].color);
    }
}