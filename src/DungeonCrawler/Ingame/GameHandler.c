#include "GameHandler.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "../lowlevel/Generics.h"
#include "./PlayerHandler.h"
#include "./TerrainHandler.h"

void InitiateGame(){
    InitPlayer();
    InitTerrain();
}

void HandleGame(ALLEGRO_EVENT *event, bool *done, bool *redraw){

    //printf("Handling\n");

    switch(event->type){

        //another frame
        case ALLEGRO_EVENT_TIMER:
            
            HandlePlayer(event, done, redraw);
            UpdateColliders();
            
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

void DrawGame(){
    DrawTerrain();
    DrawPlayer();
    
}

void DeinitGame(){
    DeinitPlayer();
}

