#include "../nexa.h"
#include "muzzle_flash.h"

MuzzleFlash create_muzzle_flash(int x, int y) {
	MuzzleFlash flash = {x, y, 30, 1.0f, 0.1f};

	return flash;
}

void update_muzzle_flash(MuzzleFlash* flash, float dt) {
	flash->scale -= 5.0f * dt;
	flash->duration -= dt;
}

void render_muzzle_flash(nxContext* ctx, MuzzleFlash* flash) {
	int radius = (int)(flash->radius * flash->scale);
	if (flash->scale > 0) {
		nx_render_circle_filled(ctx, flash->x, flash->y, radius, nxWHITE);
	}
}