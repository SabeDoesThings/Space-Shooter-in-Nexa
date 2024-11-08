#include "../nexa.h"

#include "game.h"
#include "player.h"
#include "particle.h"
#include "muzzle_flash.h"
#include "bullet.h"
#include "alien.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

GameState current_state;

float alien_spawn_timer = 0.0f;

Player player;
Particle* particle1;
Particle* particle2;

bool muzzle_flash_active = false;
MuzzleFlash muzzle_flash;

Bullet bullet[MAX_BULLETS];
int bullet_count = 0;

Alien aliens[MAX_ALIENS];
int alien_count = 0;

nxFont game_font;

int score = 0;

void reset_game() {
	reset_player(&player);

    free(particle1);
    free(particle2);
    particle1 = generate_particles(PARTICLE1_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, (nxColor){44, 30, 87, 255});
    particle2 = generate_particles(PARTICLE2_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, (nxColor){255, 255, 255, 255});

    bullet_count = 0;

    alien_count = 0;
    alien_spawn_timer = 0.0f;

    muzzle_flash_active = false;

    score = 0;
}

void on_run() {
	game_font = nx_load_font("./res/Pixeled.ttf", 30);

	current_state = MAIN_MENU;

	init_player(&player);

	particle1 = generate_particles(PARTICLE1_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, (nxColor){44, 30, 87, 255});
	particle2 = generate_particles(PARTICLE2_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, (nxColor){255, 255, 255, 255});

	init_aliens();

	nx_play_music_looped("./res/bgmusic.wav");
}

void update(float dt) {
	printf("%d\n", current_state);

	if (nx_is_key_pressed(nxKEY_ESCAPE)) {
		exit(0);
	}

	switch (current_state) {
	case MAIN_MENU:
		if (nx_is_key_pressed(nxKEY_SPACE)) {
			current_state = PLAYING;

			reset_game();
		}
		break;
	case PLAYING:
		update_particles(particle1, PARTICLE1_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, dt, 100.0f);
		update_particles(particle2, PARTICLE2_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, dt, 150.0f);

		update_player(&player, dt);

		if (nx_is_key_pressed(nxKEY_SPACE)) {
			if (bullet_count < MAX_BULLETS) {
	            bullet[bullet_count++] = create_bullet(player.x, player.y, -500);
	        }

			muzzle_flash = create_muzzle_flash(player.x + 23, player.y - 10);
			muzzle_flash_active = true;

			nx_play_audio("./res/laserShoot.wav");
		}

		if (muzzle_flash_active) {
			update_muzzle_flash(&muzzle_flash, dt);
		}

		update_bullets(bullet, &bullet_count, dt);

		alien_spawn_timer += dt;
	    if (alien_spawn_timer >= 2.0f) {
	        if (alien_count < MAX_ALIENS) {
	        	aliens[alien_count++] = create_alien(MAX_ALIENS);
	    	}
	    	alien_spawn_timer = 0.0f;
	    }

	    update_aliens(aliens, &alien_count, dt);

	    for (int i = 0; i < bullet_count; i++) {
	        for (int j = 0; j < alien_count; j++) {
	            if (nx_check_collision_rect(bullet[i].bounds, aliens[j].bounds)) {
	                bullet[i] = bullet[--bullet_count];
	                aliens[j] = aliens[--alien_count];
	                score += 1;
	                break;
	            }
	        }
	    }

	    for (int i = 0; i < alien_count; i++) {
	        if (nx_check_collision_rect(player.bounds, aliens[i].bounds)) {
	            current_state = GAME_OVER;
	            break;
	        }
	    }
	    break;
	case GAME_OVER:
		nx_stop_music();

		if (nx_is_key_pressed(nxKEY_SPACE)) {
			reset_game();
			current_state = PLAYING;
			nx_play_music_looped("./res/bgmusic.wav");
		}
		break;
	}
}

void render(nxContext* ctx) {
	nx_clear_screen(ctx, (nxColor){8, 2, 20, 255});

	switch(current_state) {
	case MAIN_MENU:
		nxTexture2D menu_img = nx_load_texture("./res/menu_img.png");
		nx_render_texture(ctx, &menu_img, 0, 0, 1.0f, 1.0f, 0.0f);

		nx_render_text(ctx, game_font, "Space Shooter", nxYELLOW, 70, 25, 1.0f, 1.0f);
		nx_render_text(ctx, game_font, "'SPACE' to start", nxWHITE, 50, WINDOW_HEIGHT / 2, 1.0f, 1.0f);
		break;
	case PLAYING:
		render_particles(ctx, particle1, PARTICLE1_COUNT);
		render_particles(ctx, particle2, PARTICLE2_COUNT);

		render_player(&player, ctx);

		render_bullets(ctx, bullet, bullet_count);

		render_muzzle_flash(ctx, &muzzle_flash);

		render_aliens(ctx, aliens, alien_count);

		char score_text[32];
		snprintf(score_text, sizeof(score_text), "%d", score);
		nx_render_text(ctx, game_font, score_text, nxWHITE, WINDOW_WIDTH / 2 - 25, 0, 1.0f, 1.0f);
		break;
	case GAME_OVER:
		nx_clear_screen(ctx, (nxColor){31, 13, 13, 255});

		nx_render_text(ctx, game_font, "You are DEAD", nxRED, 90, 25, 1.0f, 1.0f);
		nx_render_text(ctx, game_font, "'SPACE' to restart", nxWHITE, 25, WINDOW_HEIGHT / 2, 1.0f, 1.0f);
		nx_render_text(ctx, game_font, "Highscore: ", nxWHITE, 25, WINDOW_HEIGHT / 3, 1.0f, 1.0f);
		break;
	}
}

void start_game() {
	nx_start(on_run, update, render, "Space Shooter", WINDOW_WIDTH, WINDOW_HEIGHT, false);

	free(particle1);
	free(particle2);
}