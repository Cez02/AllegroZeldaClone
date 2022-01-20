#pragma once

#include "TerrainHandler.h"
#include "../lowlevel/InputHandler.h"

BoxCollider PlayerCollider;

void DrawPlayer();

void HandlePlayer(ALLEGRO_EVENT *event, bool *done, bool *redraw);

void InitPlayer();

void DeinitPlayer();
