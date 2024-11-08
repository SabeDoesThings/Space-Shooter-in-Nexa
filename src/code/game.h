#pragma once

#include "../nexa.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 900

#define PARTICLE1_COUNT 40
#define PARTICLE2_COUNT 30

#define MAX_ALIENS 100

#define MAX_BULLETS 100

typedef enum {
	MAIN_MENU,
	PLAYING,
	GAME_OVER
} GameState;

void reset_game();
void on_run();
void update(float dt);
void render(nxContext* ctx);
void start_game();
