#pragma once

#include "../lowlevel/InputHandler.h"
#include "../lowlevel/DisplayHandler.h"

void init_settings_menu();

void HandleSettings(ALLEGRO_EVENT *event, bool *done, bool *redraw);

void DrawSettings();
