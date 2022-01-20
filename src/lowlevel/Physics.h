#pragma once

#include "Generics.h"

typedef struct Vector2{

    int x,y;

} Vector2;

typedef struct BoxCollider{
    Vector2 Origin, Dimensions;

} BoxCollider;

bool CheckCollision(BoxCollider A, BoxCollider B);

void SetVector2(Vector2 *dest, int x, int y);

Vector2 GetDirectionVector(DIRECTION dir);
