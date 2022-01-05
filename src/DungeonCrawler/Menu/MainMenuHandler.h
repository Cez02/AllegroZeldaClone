#ifndef INCLUDE_MAIN_MENU_HANDLER
    #define INCLUDE_MAIN_MENU_HANDLER

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include "../lowlevel/Generics.h"
#include "../lowlevel/InputHandler.h"

void init_main_menu();

void HandleMainMenu(ALLEGRO_EVENT *event, bool *done, bool *redraw);

void DrawMainMenu();

void UpdateMainMenuInfo();
#endif