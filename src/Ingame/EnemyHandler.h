#pragma once

#include "../lowlevel/Generics.h"
#include "../lowlevel/Physics.h"

typedef enum EnemyType{
    KnightEnemy,
    Heart
} EnemyType;

typedef struct Enemy{
    EnemyType type;

    int currentHealth;
    int maxHealth;
    int attackPower;

    Sprite WalkingAnimations[4][2];
    int FrameCounter;
    int AnimFrame;

    Sprite currentSprite;
    Vector2f position;
    BoxColliderF collider;

    float DamagedCounter;
    Vector2f CurrentDestination;

    Vector2f Velocity;
    float speed;
} Enemy;

void LoadEnemyAssets();

void DrawEnemies();

void HandleEnemies();

void init_enemies();