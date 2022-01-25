#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//game font
ALLEGRO_FONT* GAME_FONT;
//game timer
ALLEGRO_TIMER* timer;
//game event queue
ALLEGRO_EVENT_QUEUE* queue;

long long GameSeed;
int currentDigit;

typedef struct Sprite{

    ALLEGRO_BITMAP *bitmap;

} Sprite;

char AssetDirectory[100];


typedef enum LEVEL_TYPE{
    MENU,
    SETTINGS,
    INGAME

} LEVEL_TYPE;

typedef enum DIRECTION{
    NORTH,
    EAST,
    SOUTH,
    WEST
} DIRECTION;

LEVEL_TYPE CurrentLevel;

ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

void must_init(bool test, const char *description);

void InitializeGenerics();

int GetRandomDigit();

int Min(int x, int y);

float Abs(float x);