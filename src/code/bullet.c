#include "../nexa.h"
#include "game.h"
#include "bullet.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Bullet create_bullet(int x, int y, int vy) {
	Bullet bullet = {x, y, vy, (nxRectangle){0}};

	return bullet;
}

void update_bullets(Bullet* bullets, int* bullet_count, float dt) {
    for (int i = 0; i < *bullet_count; i++) {
        bullets[i].y += (int)(bullets[i].vy * dt);
        bullets[i].bounds = (nxRectangle){bullets[i].x, bullets[i].y, 32, 32};
    }

    int j = 0;
    for (int i = 0; i < *bullet_count; i++) {
        if (bullets[i].y > 0 && bullets[i].y < WINDOW_HEIGHT) {
            bullets[j++] = bullets[i];
        }
    }
    *bullet_count = j;
}

void render_bullets(nxContext* ctx, Bullet* bullets, int bullet_count) {
	nxTexture2D bullet_texture = nx_load_texture("./res/player_beam.png");

	for (int i = 0; i < bullet_count; i++) {
		nx_render_texture(ctx, &bullet_texture, bullets[i].x + 8, bullets[i].y - 32, 2.0f, 2.0f, 0.0f);
	}
}