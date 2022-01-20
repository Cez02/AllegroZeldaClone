#include "MainMenuHandler.h"


//variables
char options[3][20] = {" Play ", " Settings ", " Exit "};
int numberOfOptions = 3;
int currentOption = 0;

/*

    the text should be drawn in the middle
    going down  

*/


void init_main_menu(bool *redraw){
    
    UpdateMainMenuInfo(redraw);

}

void UpdateMainMenuInfo(bool *redraw){

    //update the option selected
    if(ButtonClicked(ALLEGRO_KEY_S) || ButtonClicked(ALLEGRO_KEY_DOWN)){
        ButtonClicked(ALLEGRO_KEY_DOWN);
        currentOption++;
        *redraw = true;
    }
    else if(ButtonClicked(ALLEGRO_KEY_W) || ButtonClicked(ALLEGRO_KEY_UP)){
        currentOption--;
        *redraw = true;
    }


    if(currentOption < 0) currentOption += 3;
    else currentOption %= 3;

}


void HandleMainMenu(ALLEGRO_EVENT *event, bool *done, bool *redraw){

    //keyboard_update(event);

    switch(event->type){

        //another frame
        case ALLEGRO_EVENT_TIMER:
            UpdateMainMenuInfo(redraw);

            //player wants to quit
            if(ButtonClicked(ALLEGRO_KEY_ESCAPE)){
                *done = true;
                break;
            }

            //player wants to select the option
            if(ButtonClicked(ALLEGRO_KEY_ENTER)){
                *redraw = true;

                     if(currentOption == 0) CurrentLevel = INGAME;
                else if(currentOption == 1) CurrentLevel = SETTINGS;
                else{
                    *done = true;
                }
                break;
            }


            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            (*done) = true;
            break;

    }

}

void DrawMainMenu(){

    //write text to screen
    

    for(int i = 0; i<numberOfOptions; i++){
        if(currentOption == i){
            options[i][0] = '>';
            options[i][strlen(options[i])-1] = '<'; 
        }
        else if(options[i][0]=='>'){
            options[i][0] = ' ';
            options[i][strlen(options[i])-1] = ' '; 
        }

        al_draw_text(GAME_FONT, al_map_rgb(255,255,255), BUFFER_W/2, 50 + i*20, ALLEGRO_ALIGN_CENTER, options[i]);
    }
}
