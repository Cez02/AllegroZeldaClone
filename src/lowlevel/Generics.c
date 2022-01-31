#include "Generics.h"

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

//used for grabbing only a part of the bitmap
ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}


//game font
ALLEGRO_FONT* GAME_FONT;
//game ui font
ALLEGRO_FONT* GAME_UI_FONT;
//game timer
ALLEGRO_TIMER* timer;
//game event queue
ALLEGRO_EVENT_QUEUE* queue;

LEVEL_TYPE CurrentLevel = MENU;

char GameSeedString[256];

int currentDigit;

ALLEGRO_FONT *LoadBitmapFont(){
    ALLEGRO_BITMAP *sheet = al_load_bitmap("./Assets/Ingame/testbitmap.png");
    must_init(sheet, "UI bitmap font");
    int ranges[] = {32,32,70,70,108,108,111,111,114,114,48,57,47,47};
    return al_grab_font_from_bitmap(sheet, 7, ranges);
}

void InitializeGenerics(){

    al_init_font_addon();
    al_init_ttf_addon();
    must_init(al_init_image_addon(), "image addon");
    must_init(al_init_font_addon(), "font addon");

    Score = 0;
    
    strcpy(AssetDirectory, "./Assets/");

    for(int i = 0; i<15; i++){
        GameSeed *= 10;
        GameSeed += rand()%10;
    }

    currentDigit = 0;
    sprintf(GameSeedString, "%lld", GameSeed);

    GAME_FONT = al_create_builtin_font();
    must_init(GAME_FONT, "font");
    GAME_UI_FONT = LoadBitmapFont();
    must_init(GAME_UI_FONT, "UI font");
    timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");
    queue = al_create_event_queue();
    must_init(queue, "queue");
}

int GetRandomDigit(){
    currentDigit = currentDigit == 14 ? 0 : currentDigit + 1;
    return GameSeedString[currentDigit] - '0';
}

int Min(int x, int y){
    return x < y ? x : y;
}

float Minf(float x, float y){
    return x < y ? x : y;
}

float Maxf(float x, float y){
    return x > y ? x : y;
}

float Abs(float x){
    if(x<0) return -x;
    return x;
}