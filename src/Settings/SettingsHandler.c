#include "SettingsHandler.h"


int CurrentOption = 0;
int optionCount = 2;


void init_settings_menu(){}

void HandleOption(){
    
    switch(CurrentOption){

        case 0:
            SwitchScreenMode();
            break;
        case 1:
            CurrentLevel = MENU;
            break;
    }
    

}

void HandleSettings(ALLEGRO_EVENT *event, bool *done, bool *redraw){
    //keyboard_update(event);

    switch(event->type){

        //another frame
        case ALLEGRO_EVENT_TIMER:
            if(ButtonClicked(ALLEGRO_KEY_DOWN) || ButtonClicked(ALLEGRO_KEY_S)){
                CurrentOption++;
                CurrentOption %= optionCount;
                *redraw = true;
                break;
            }
            if(ButtonClicked(ALLEGRO_KEY_UP) || ButtonClicked(ALLEGRO_KEY_W)){
                CurrentOption--;
                if(CurrentOption < 0) CurrentOption += optionCount;
                *redraw = true;
                break;
            }

            if(ButtonClicked(ALLEGRO_KEY_SPACE) || ButtonClicked(ALLEGRO_KEY_D) || ButtonClicked(ALLEGRO_KEY_A) || ButtonClicked(ALLEGRO_KEY_RIGHT) || ButtonClicked(ALLEGRO_KEY_LEFT) || ButtonClicked(ALLEGRO_KEY_ENTER)){
                HandleOption();
                *redraw = true;
                break;
            }

            if(ButtonClicked(ALLEGRO_KEY_ESCAPE)){
                CurrentLevel = MENU;
                *redraw = true;
                break;
            }



            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            (*done) = true;
            break;

    }
}

void DrawOption(int option, char optionTag[]){

    al_draw_text(GAME_FONT, al_map_rgb(255,255,255), 20, 50 + option*20, ALLEGRO_ALIGN_LEFT, optionTag);
}

void DrawSettings(){

    //draw the window mode

    if(Fullscreen && CurrentOption == 0)
        DrawOption(0, ">Window mode: Fullscreen");
    else if(!Fullscreen && CurrentOption == 0)
        DrawOption(0, ">Window mode: Windowed");
    else if(Fullscreen)
        DrawOption(0, "Window mode: Fullscreen");
    else if(!Fullscreen)
        DrawOption(0, "Window mode: Windowed");

    if(CurrentOption == 1)
        DrawOption(1, ">Back to menu");
    else
        DrawOption(1, "Back to menu");
}
