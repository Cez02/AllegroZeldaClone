#pragma once

#include "Generics.h"


#define KEY_SEEN     1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];
int MouseX, MouseY;
bool MouseClicked;

void keyboard_init();

void keyboard_update(ALLEGRO_EVENT* event);

bool ButtonClicked(int keycode);
bool ButtonHeldDown(int keycode);
