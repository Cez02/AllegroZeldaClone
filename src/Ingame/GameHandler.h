#pragma once

#include "../lowlevel/DisplayHandler.h"
#include "EnemyHandler.h"
#include "UIHandler.h"

void HandleGame(ALLEGRO_EVENT *event, bool *done, bool *redraw);
void DrawGame();
void InitiateGame();
void DeinitGame();
void DrawNewFloorText();
