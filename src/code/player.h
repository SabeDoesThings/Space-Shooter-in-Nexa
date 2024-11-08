#pragma once

#include "../nexa.h"

typedef struct {
	nxTexture2D tex;
	int x;
	int y;
	nxRectangle bounds;
} Player;

void init_player(Player* player);
void reset_player(Player* player);
void update_player(Player* player, float dt);
void render_player(Player* player, nxContext* ctx);