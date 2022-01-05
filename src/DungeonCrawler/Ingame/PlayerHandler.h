#ifndef INCLUDE_PLAYER_HANDLER
    #define INCLUDE_PLAYER_HANDLER

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "../lowlevel/Generics.h"

void DrawPlayer();

void HandlePlayer(ALLEGRO_EVENT *event, bool *done, bool *redraw);

void InitPlayer();

void DeinitPlayer();

#endif