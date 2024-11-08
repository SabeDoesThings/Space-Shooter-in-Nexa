#include "../nexa.h"
#include "player.h"
#include "game.h"
#include <stdbool.h>

int speed = 270;

bool is_moving = false;

nxAnimation* player_center;
nxAnimation* player_left;
nxAnimation* player_right;

nxAnimation* player_boosters;

void init_player(Player* player) {
	player->tex = nx_load_texture("./res/player_ship.png");
	player->x = 233;
	player->y = 707;

	player_center = nx_create_animation(player->tex, 16, 16, 3, 0.0f, 2, 2);
	player_left = nx_create_animation(player->tex, 16, 16, 3, 0.0f, 1, 1);
	player_right = nx_create_animation(player->tex, 16, 16, 3, 0.0f, 3, 3);

	player_boosters = nx_create_animation(nx_load_texture("./res/boosters.png"), 16, 16, 2, 0.1f, 1, 2);
}

void reset_player(Player* player) {
	player->x = 233;
	player->y = 707;
}

void update_player(Player* player, float dt) {
	player->bounds = (nxRectangle){player->x, player->y, 48, 48};

	if (nx_is_key_down(nxKEY_W)) {
		nx_update_animation(player_left, dt, false);
		player->y -= speed * dt;
		is_moving = true;
	}
	if (nx_is_key_down(nxKEY_S)) {
		nx_update_animation(player_right, dt, false);
		player->y += speed * dt;
		is_moving = true;
	}

	if (nx_is_key_down(nxKEY_A)) {
		nx_update_animation(player_left, dt, false);
		player->x -= speed * dt;
		is_moving = true;
	}
	if (nx_is_key_down(nxKEY_D)) {
		nx_update_animation(player_right, dt, false);
		player->x += speed * dt;
		is_moving = true;
	}

	if (player->y >= WINDOW_HEIGHT - 64) {
		player->y = WINDOW_HEIGHT - 64;
	}
	else if (player->y <= 0) {
		player->y = 0;
	}

	if (player->x >= WINDOW_WIDTH + 48) {
		player->y = -48;
	}
	else if (player->x <= -48) {
		player->x = WINDOW_WIDTH + 48;
	}

	nx_update_animation(player_boosters, dt, true);
}

void render_player(Player* player, nxContext* ctx) {
	float scale_mul = 3.0f;

	if (nx_is_key_down(nxKEY_A)) {
		nx_render_animation(ctx, player_left, player->x, player->y, scale_mul, scale_mul, 0.0f);
	}
	else if (nx_is_key_down(nxKEY_D)) {
		nx_render_animation(ctx, player_right, player->x, player->y, scale_mul, scale_mul, 0.0f);
	}
	else {
		nx_render_animation(ctx, player_center, player->x, player->y, scale_mul, scale_mul, 0.0f);
	}

	nx_render_animation(ctx, player_boosters, player->x + 8, player->y+50, 2.0f, 2.0f, 0.0f);
}
