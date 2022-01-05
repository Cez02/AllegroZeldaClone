#ifndef INCLUDE_TERRAIN_HANDLER
    #define INCLUDE_TERRAIN_HANDLER

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "../lowlevel/Generics.h"
#include "../lowlevel/Physics.h"

typedef enum LevelType{
    ROOM_TEST,
    ROOM_SPAWN,
    ROOM_ENEMY,
    ROOM_NEXT_FLOOR
} LevelType;

typedef struct Level{

    int levelTiles[7][12];

    LevelType ThisLevelType;

    //doors starting from up clockwise
    bool doors[4];

} Level;

void DrawTerrain();
void InitTerrain();

void MoveLevel(Vector2 directionVec, DIRECTION dir);
void EnteringNewRoom(BoxCollider *PlayerCollider, Vector2 *PlayerPosition);

void UpdateColliders();

bool CollidedWithWalls(BoxCollider entity);
#endif