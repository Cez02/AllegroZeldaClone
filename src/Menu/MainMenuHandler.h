#pragma once

#include "../lowlevel/DisplayHandler.h"
#include "../lowlevel/InputHandler.h"

void init_main_menu();

void HandleMainMenu(ALLEGRO_EVENT *event, bool *done, bool *redraw);

void DrawMainMenu();

void UpdateMainMenuInfo();
