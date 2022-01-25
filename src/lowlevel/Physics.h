#pragma once

#include "Generics.h"

typedef struct Vector2{

    int x,y;

} Vector2;

typedef struct Vector2f{

    float x,y;

} Vector2f;

typedef struct BoxCollider{
    Vector2 Origin, Dimensions;

} BoxCollider;

typedef struct BoxColliderF{
    Vector2f Origin, Dimensions;

} BoxColliderF;

bool CheckCollision(BoxCollider A, BoxCollider B);
bool CheckCollisionF(BoxColliderF A, BoxColliderF B);

void SetVector2(Vector2 *dest, int x, int y);
void SetVector2f(Vector2f *dest, float x, float y);

Vector2 Vector2ToF(Vector2f src);
BoxCollider BCFtoBC(BoxColliderF src);

void SetBoxCollider(BoxCollider *dest, int x, int y, int w, int h);
void SetBoxColliderF(BoxColliderF *dest, float x, float y, float w, float h);

Vector2 GetDirectionVector(DIRECTION dir);

bool EqualVectors(Vector2f a, Vector2f b, float MarginOfError);

bool EqualVectorsInt(Vector2 a, Vector2 b, int MarginOfError);