#include "DisplayHandler.h"

#define BUFFER_W 256
#define BUFFER_H 176

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

ALLEGRO_DISPLAY* Display;
ALLEGRO_BITMAP* DisplayBuffer;

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    Display = al_create_display(DISP_W, DISP_H);
    must_init(Display, "display");

    DisplayBuffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(DisplayBuffer, "bitmap buffer");

    al_register_event_source(queue, al_get_display_event_source(Display));
}

void disp_deinit()
{
    al_destroy_bitmap(DisplayBuffer);
    al_destroy_display(Display);
}

void disp_pre_draw()
{
    al_set_target_bitmap(DisplayBuffer);
}

void disp_post_draw()
{
    al_set_target_backbuffer(Display);
    al_draw_scaled_bitmap(DisplayBuffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}
