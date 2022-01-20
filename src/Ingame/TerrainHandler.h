#pragma once

#include "../lowlevel/Physics.h"

int CurrentFloor;
bool ChangingFloors;

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
bool CollidedWithNewFloorTile(BoxCollider player);
