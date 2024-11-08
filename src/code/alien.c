#include "../nexa.h"
#include "alien.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

nxTexture2D alien_tex;
nxAnimation* alien_anim;

void init_aliens() {
    alien_tex = nx_load_texture("./res/alan.png");
    alien_anim = nx_create_animation(alien_tex, 16, 16, 6, 0.1f, 1, 6);
}

Alien create_alien(int vy) {
	Alien alien = {rand() % 400, -48, vy, (nxRectangle){0}};

	return alien;
}

void update_aliens(Alien* aliens, int* alien_count, float dt) {
	for (int i = 0; i < *alien_count; ++i) {
        aliens[i].bounds = (nxRectangle){aliens[i].x, aliens[i].y, 48, 48};
        aliens[i].y += (int)(aliens[i].vy * dt);
    }

    int j = 0;
    for (int i = 0; i < *alien_count; ++i) {
        aliens[i].bounds = (nxRectangle){aliens[i].x, aliens[i].y, 48, 48};
        aliens[i].y += (int)round(aliens[i].vy * dt);

        if (aliens[i].y <= WINDOW_HEIGHT) {
            aliens[j++] = aliens[i];
        }
    }

    *alien_count = j;

    nx_update_animation(alien_anim, dt, true);
}

void render_aliens(nxContext* ctx, Alien* aliens, int alien_count) {
    for (size_t i = 0; i < alien_count; ++i) {
        nx_render_animation(ctx, alien_anim, aliens[i].x, aliens[i].y, 3.0f, 3.0f, 0.0f);
    }
}