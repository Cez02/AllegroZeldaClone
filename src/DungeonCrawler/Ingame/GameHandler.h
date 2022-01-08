#ifndef INCLUDE_GAME_HANDLER
    #define INCLUDE_GAME_HANDLER

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "../lowlevel/Generics.h"

void HandleGame(ALLEGRO_EVENT *event, bool *done, bool *redraw);
void DrawGame();
void InitiateGame();
void DeinitGame();
void DrawNewFloorText();

#endif