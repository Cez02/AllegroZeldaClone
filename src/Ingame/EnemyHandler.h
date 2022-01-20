#pragma once

#include "../lowlevel/Generics.h"
#include "../lowlevel/Physics.h"

typedef struct Enemy{
    int currentHealth;
    int maxHealth;
    int attackPower;

    Sprite sprite;
    Vector2 position;
    BoxCollider collider;
} Enemy;

void DrawEnemies();

//this will be used for generating enemies
//in each room at enemy spawn points
Enemy *GenerateEnemy();
