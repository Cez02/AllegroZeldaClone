#ifndef INCLUDE_PHYSICS
    #define INCLUDE_PHYSICS

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "../lowlevel/Generics.h"

typedef struct Vector2{

    int x,y;

} Vector2;

typedef struct BoxCollider{
    Vector2 Origin, Dimensions;

} BoxCollider;

bool CheckCollision(BoxCollider A, BoxCollider B);

void SetVector2(Vector2 *dest, int x, int y);

Vector2 GetDirectionVector(DIRECTION dir);

#endif