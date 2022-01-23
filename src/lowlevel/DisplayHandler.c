#include "DisplayHandler.h"

#define BUFFER_W 256
#define BUFFER_H 176

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

ALLEGRO_DISPLAY* Display;
ALLEGRO_BITMAP* DisplayBuffer;

ALLEGRO_MONITOR_INFO info;

int MonitorX = DISP_W, MonitorY = DISP_H;

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    al_get_monitor_info(0, &info);

    MonitorX = info.x2-info.x1;
    MonitorY = info.y2-info.y1;

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

    int newMonitorX = MonitorX, newMonitorY = MonitorY;

    if(MonitorX > MonitorY) newMonitorX = (float)MonitorY * (float)(BUFFER_W) / (float)(BUFFER_H);
    else newMonitorY = (float)MonitorX * (float)(BUFFER_H) / (float)(BUFFER_W);

    if(Fullscreen)
        al_draw_scaled_bitmap(DisplayBuffer, 0, 0, BUFFER_W, BUFFER_H, (MonitorX - newMonitorX)/2, (MonitorY - newMonitorY)/2, newMonitorX, newMonitorY, 0);
    else
        al_draw_scaled_bitmap(DisplayBuffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);


    al_flip_display();
}

void SwitchScreenMode(){

    Fullscreen = !Fullscreen;

    if(Fullscreen){
    
        al_destroy_display(Display);

        al_set_new_display_flags( ALLEGRO_FULLSCREEN_WINDOW );

        Display = al_create_display(MonitorX, MonitorY);
        must_init(Display, "display");

        al_register_event_source(queue, al_get_display_event_source(Display));
    }
    else{
    
        al_destroy_display(Display);

        al_set_new_display_flags( ALLEGRO_WINDOWED );

        Display = al_create_display(DISP_W, DISP_H);
        must_init(Display, "display");

        al_register_event_source(queue, al_get_display_event_source(Display));
    }

}