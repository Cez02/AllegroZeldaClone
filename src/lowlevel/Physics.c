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


void SetVector2(Vector2 *dest, int x, int y){
    dest->x = x;
    dest->y = y;
}

Vector2 GetDirectionVector(DIRECTION dir){
    Vector2 tmp;
    if(dir == NORTH){ tmp.x =  0;  tmp.y =  1;  }
    if(dir == EAST ){ tmp.x =  1;  tmp.y =  0;  }
    if(dir == SOUTH){ tmp.x =  0;  tmp.y = -1;  }
    if(dir == WEST ){ tmp.x = -1;  tmp.y =  0;  }

    return tmp;
}