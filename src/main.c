#include "Menu/MainMenuHandler.h"
#include "Ingame/GameHandler.h"
#include "Settings/SettingsHandler.h"


int main(){

    srand(time(0));

    //initialize allegro
    must_init(al_init(), "allegro");

    InitializeGenerics();

    //initialize display
    disp_init();

    //initialize input handler
    keyboard_init();

    //initialize audio
    init_audio();

    ALLEGRO_EVENT currentEvent;

    bool done = false, redraw = true;

    al_start_timer(timer);

    al_register_event_source(queue, al_get_timer_event_source(timer));


    InitiateGame();

    PlayMusic(0);

    init_ui();

    //main game loop
    while(1){

        al_wait_for_event(queue, &currentEvent);

        switch(CurrentLevel){
            case MENU:
                HandleMainMenu(&currentEvent, &done, &redraw);

                redraw = true;

                if(CurrentLevel == INGAME){
                    if(ResetGameSettings){

                        InitiateGame();

                        ResetGameSettings = false;
                    }

                    HandleGame(&currentEvent, &done, &redraw);
                }

                break;
            case SETTINGS:
                HandleSettings(&currentEvent, &done, &redraw);
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
                    DrawSettings();
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