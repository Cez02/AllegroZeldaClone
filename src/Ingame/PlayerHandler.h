#pragma once

#include "TerrainHandler.h"
#include "../lowlevel/InputHandler.h"

BoxColliderF PlayerCollider;
BoxColliderF SwordCollider;

DIRECTION PlayerDirection;

bool PlayerDead;

typedef struct PlayerStats{
    int currentHealth;
    int maxHealth;
} PlayerStats;

void DrawPlayer();

void HandlePlayer(ALLEGRO_EVENT *event, bool *done, bool *redraw);

void InitPlayer();

void DeinitPlayer();

void DamagePlayer(int damage, Vector2f velocity);

bool IsPlayerDamaged();

//Accessors

PlayerStats GetPlayerStats();

Vector2f GetPlayerPosition();