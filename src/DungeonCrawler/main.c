#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <time.h>

#include "./lowlevel/DisplayHandler.h"
#include "./lowlevel/DisplayHandler.h"
#include "./lowlevel/Generics.h"
#include "./Menu/MainMenuHandler.h"
#include "./lowlevel/InputHandler.h"
#include "./Ingame/GameHandler.h"



int main(){

    srand(time(0));

    //initialize allegro
    must_init(al_init(), "allegro");

    InitializeGenerics();

    //initialize display
    disp_init();

    //initialize input handler
    keyboard_init();

    must_init(al_init_image_addon(), "image addon");
    must_init(al_init_font_addon(), "font addon");

    ALLEGRO_EVENT currentEvent;

    bool done = false, redraw = true;

    al_start_timer(timer);

    al_register_event_source(queue, al_get_timer_event_source(timer));

    //init_main_menu(&redraw);

    InitiateGame();

    //main game loop
    while(1){

        al_wait_for_event(queue, &currentEvent);

        switch(CurrentLevel){
            case MENU:
                HandleMainMenu(&currentEvent, &done, &redraw);

                if(CurrentLevel == INGAME) HandleGame(&currentEvent, &done, &redraw);

                break;
            case SETTINGS:
                break;
            case INGAME:
                HandleGame(&currentEvent, &done, &redraw);
                break;
        }


        keyboard_update(&currentEvent);

        if(done) break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0,0,0));

            switch(CurrentLevel){

                case MENU:
                    DrawMainMenu();
                    break;
                case SETTINGS:
                    break;
                case INGAME:
                    DrawGame();
                    break;
            }


            disp_post_draw();
            redraw = false;
        }
    }

    DeinitGame();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_font(GAME_FONT);

}