#include "InputHandler.h"


#define KEY_SEEN     1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];
int MouseX, MouseY;
bool MouseClicked = false;

void keyboard_init()
{
    memset(key, 0, sizeof(key));
    must_init(al_install_keyboard(), "keyboard");
    al_register_event_source(queue, al_get_keyboard_event_source());
}



void keyboard_update(ALLEGRO_EVENT* event)
{
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            MouseX = event->mouse.x;
            MouseY = event->mouse.y;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            MouseClicked = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            MouseClicked = false;
            break;
    }
}

bool ButtonClicked(int keycode){
    return (key[keycode] == (KEY_SEEN | KEY_RELEASED));
}

bool ButtonHeldDown(int keycode){
    return (key[keycode] == KEY_SEEN) || (key[keycode] == (KEY_SEEN | KEY_RELEASED));
}