#pragma once

#include "Generics.h"

#define BUFFER_W 256
#define BUFFER_H 176

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

ALLEGRO_DISPLAY* Display;

void disp_init();

void disp_deinit();

void disp_pre_draw();

void disp_post_draw();
