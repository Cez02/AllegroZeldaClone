#include "UIHandler.h"

#include "../lowlevel/SoundHandler.h"

Sprite UISprites[16];
/*
0 - UI background
1 - Heart background
2 - Heart filled
3 - Heart half-filled
*/

void init_ui(){

    char buffer[100];
    strcpy(buffer, AssetDirectory);
    strcat(buffer, "Ingame/UISprites.png");

    ALLEGRO_BITMAP *sheet = al_load_bitmap(buffer);
    must_init(sheet, "UI sprite sheet");

    UISprites[0].bitmap = sprite_grab(sheet, 0, 0, 97, 28);
    UISprites[1].bitmap = sprite_grab(sheet, 97, 0, 7, 6);
    UISprites[2].bitmap = sprite_grab(sheet, 104, 0, 7, 6);
    UISprites[3].bitmap = sprite_grab(sheet, 111, 0, 7, 6);


}

void DrawUI(){

    //draw the UI background
    al_draw_bitmap(UISprites[0].bitmap, 157, 0, 0);

    //draw the heart backgrounds
    int current = GetPlayerStats().currentHealth;
    int maxH = GetPlayerStats().maxHealth;

    Vector2 HeartOrigin;
    SetVector2(&HeartOrigin, 163, 6);
    int heartIndex = 0;

    while(maxH){

        //draw the background
        al_draw_bitmap(UISprites[1].bitmap, (heartIndex%5)*9 + HeartOrigin.x, (heartIndex/5)*9 + HeartOrigin.y, 0);

        //draw filled
        if(current >= 100){
            al_draw_bitmap(UISprites[2].bitmap, (heartIndex%5)*9 + HeartOrigin.x, (heartIndex/5)*9 + HeartOrigin.y, 0);
            current -= 100;
        }
        else if(current >= 50){
            al_draw_bitmap(UISprites[3].bitmap, (heartIndex%5)*9 + HeartOrigin.x, (heartIndex/5)*9 + HeartOrigin.y, 0);
            current -= 50;
        }
        
        
        maxH -= 100;
        heartIndex++;
    }

    char buffer[50];
    sprintf(buffer, "Floor \n%d", CurrentFloor);

    al_draw_text(GAME_UI_FONT, al_map_rgb(255,255,255), 210, 10, ALLEGRO_ALIGN_LEFT, buffer);
}

int DeathCounter = 0;
bool dying = false;

void DrawGameDeath(){
    if(DeathCounter == 0 && !dying){
        dying = true;
        DeathCounter = 120;
    }

    al_draw_text(GAME_FONT,al_map_rgb(255,255,255), 128, 79, ALLEGRO_ALIGN_CENTER, "GAME OVER" );
    DeathCounter--;

    if(DeathCounter==0){
        CurrentLevel = MENU;
        PlayerDead = false;
        ResetGameSettings = true;
        dying = false;
        PlayMusic(0);
    }

}

