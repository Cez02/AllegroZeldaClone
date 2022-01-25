#pragma once

#include "PlayerHandler.h"
#include "../lowlevel/DisplayHandler.h"
#include "EnemyHandler.h"

void HandleGame(ALLEGRO_EVENT *event, bool *done, bool *redraw);
void DrawGame();
void InitiateGame();
void DeinitGame();
void DrawNewFloorText();
