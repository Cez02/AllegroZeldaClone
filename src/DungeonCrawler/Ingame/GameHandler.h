#ifndef INCLUDE_GAME_HANDLER
    #define INCLUDE_GAME_HANDLER

#include "PlayerHandler.h"
#include "../lowlevel/DisplayHandler.h"

void HandleGame(ALLEGRO_EVENT *event, bool *done, bool *redraw);
void DrawGame();
void InitiateGame();
void DeinitGame();
void DrawNewFloorText();

#endif