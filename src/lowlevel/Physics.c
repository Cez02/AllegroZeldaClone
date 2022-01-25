#include "Physics.h"



//now this is a chore
bool CheckCollision(BoxCollider A, BoxCollider B){

    Vector2 BottomRightA, BottomRightB;
    BottomRightA.x = A.Origin.x + A.Dimensions.x;
    BottomRightA.y = A.Origin.y + A.Dimensions.y;
    BottomRightB.x = B.Origin.x + B.Dimensions.x;
    BottomRightB.y = B.Origin.y + B.Dimensions.y;


    if(A.Origin.x > BottomRightB.x) return false;
    if(BottomRightA.x < B.Origin.x) return false;
    if(BottomRightA.y < B.Origin.y) return false;
    if(A.Origin.y > BottomRightB.y) return false;


    return true;
}

bool CheckCollisionF(BoxColliderF A, BoxColliderF B){

    Vector2f BottomRightA, BottomRightB;
    BottomRightA.x = A.Origin.x + A.Dimensions.x;
    BottomRightA.y = A.Origin.y + A.Dimensions.y;
    BottomRightB.x = B.Origin.x + B.Dimensions.x;
    BottomRightB.y = B.Origin.y + B.Dimensions.y;


    if(A.Origin.x > BottomRightB.x) return false;
    if(BottomRightA.x < B.Origin.x) return false;
    if(BottomRightA.y < B.Origin.y) return false;
    if(A.Origin.y > BottomRightB.y) return false;


    return true;
}


void SetVector2(Vector2 *dest, int x, int y){
    dest->x = x;
    dest->y = y;
}

void SetVector2f(Vector2f *dest, float x, float y){
    dest->x = x;
    dest->y = y;
}

Vector2 Vector2ToF(Vector2f src){
    Vector2 tmp;
    tmp.x = (int)src.x;
    tmp.y = (int)src.y;
    return tmp;
}

BoxCollider BCFtoBC(BoxColliderF src){
    BoxCollider tmp;
    tmp.Origin = Vector2ToF(src.Origin);
    tmp.Dimensions = Vector2ToF(src.Dimensions);
    return tmp;
}

Vector2 GetDirectionVector(DIRECTION dir){
    Vector2 tmp;
    if(dir == NORTH){ tmp.x =  0;  tmp.y =  1;  }
    if(dir == EAST ){ tmp.x =  1;  tmp.y =  0;  }
    if(dir == SOUTH){ tmp.x =  0;  tmp.y = -1;  }
    if(dir == WEST ){ tmp.x = -1;  tmp.y =  0;  }

    return tmp;
}

void SetBoxCollider(BoxCollider *dest, int x, int y, int w, int h){
    SetVector2(&(dest->Dimensions), w, h);
    SetVector2(&(dest->Origin), x, y);
}

void SetBoxColliderF(BoxColliderF *dest, float x, float y, float w, float h){
    SetVector2f(&(dest->Dimensions), w, h);
    SetVector2f(&(dest->Origin), x, y);
}

bool EqualVectors(Vector2f a, Vector2f b, float MarginOfError){ 
    return (Abs(a.x - b.x) <= MarginOfError) && (Abs(a.y - b.y) <= MarginOfError); 
}

bool EqualVectorsInt(Vector2 a, Vector2 b, int MarginOfError){ 
    return (Abs(a.x - b.x) <= MarginOfError) && (Abs(a.y - b.y) <= MarginOfError); 
}
