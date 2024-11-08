#pragma once

#include "../nexa.h"

typedef struct {
	int x;
	int y;
	int radius;
	float scale;
	float duration;
} MuzzleFlash;

MuzzleFlash create_muzzle_flash(int x, int y);
void update_muzzle_flash(MuzzleFlash* flash, float dt);
void render_muzzle_flash(nxContext* ctx, MuzzleFlash* flash);