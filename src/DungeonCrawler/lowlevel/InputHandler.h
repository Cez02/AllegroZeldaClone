#ifndef INCLUDE_INPUT_HANDLER
    #define INCLUDE_INPUT_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>


#define KEY_SEEN     1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];
int MouseX, MouseY;
bool MouseClicked;

void keyboard_init();

void keyboard_update(ALLEGRO_EVENT* event);

bool ButtonClicked(int keycode);
bool ButtonHeldDown(int keycode);

#endif