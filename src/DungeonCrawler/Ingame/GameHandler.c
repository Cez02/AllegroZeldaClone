#include "GameHandler.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "../lowlevel/Generics.h"
#include "./PlayerHandler.h"
#include "./TerrainHandler.h"
#include "../lowlevel/DisplayHandler.h"



void InitiateGame(){
    CurrentFloor = 1;
    ChangingFloors = true;
    InitPlayer();
    InitTerrain();
}

bool TextDrawn = false;
int ChangingFloorsFrameCount = 0;

void HandleGame(ALLEGRO_EVENT *event, bool *done, bool *redraw){

    //printf("Handling\n");

    switch(event->type){

        //another frame
        case ALLEGRO_EVENT_TIMER:
            
            if(ChangingFloors){
                if((float)(ChangingFloorsFrameCount)/60 > 3){
                    ChangingFloors = false;
                    ChangingFloorsFrameCount = 0;
                    TextDrawn = false;
                    InitTerrain();
                    *redraw = true;
                }
                else if(!TextDrawn){
                    *redraw = true;
                }

                ChangingFloorsFrameCount++;

                break;
            }

            UpdateColliders();
            HandlePlayer(event, done, redraw);

            
        case ALLEGRO_EVENT_KEY_DOWN:
        /*
            if(event->keyboard.keycode == ALLEGRO_KEY_I){
                MoveLevel(0,1, NORTH);
                *redraw = true;
            }
            if(event->keyboard.keycode == ALLEGRO_KEY_L){
                MoveLevel(1, 0, EAST);
                *redraw = true;
            }
            if(event->keyboard.keycode == ALLEGRO_KEY_K){
                MoveLevel(0, -1, SOUTH);
                *redraw = true;
            }
            if(event->keyboard.keycode == ALLEGRO_KEY_J){
                MoveLevel(, WEST);
                *redraw = true;
            }*/



            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            (*done) = true;
            break;

    }
}

char s[12] = "Floor      ";
void DrawNewFloorText(){
    TextDrawn = true;

    int reversedFloorNumber = 0, tmp = CurrentFloor;

    while(tmp){
        reversedFloorNumber *= 10;
        reversedFloorNumber += tmp%10;
        tmp /= 10;
    }

    int ind = 6;
    while(reversedFloorNumber){
        s[ind] = '0' + reversedFloorNumber%10;
        reversedFloorNumber /= 10;
    }

    al_draw_text(GAME_FONT, al_map_rgb(255, 255, 255), BUFFER_W/2,  BUFFER_H/2, ALLEGRO_ALIGN_CENTER, s);

}

void DrawGame(){
    if(ChangingFloors){
        DrawNewFloorText();
        return;
    }
    DrawTerrain();
    DrawPlayer();
    
}

void DeinitGame(){
    DeinitPlayer();
}

