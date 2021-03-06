#include "EnemyHandler.h"

#include "TerrainHandler.h"
#include "PlayerHandler.h"

//max 5 enemies per room
Enemy *enemies[10][10][5];

Sprite EnemySprites[64];
bool AssetsLoaded = false;
/*
    0 - 7: Knight sprites
    8: Heart

*/

void LoadEnemyAssets(){

    if(AssetsLoaded) return;
    AssetsLoaded = true;

    char buffer[100];
    strcpy(buffer, AssetDirectory);
    strcat(buffer, "Ingame/MonstersSprites.png");

    ALLEGRO_BITMAP *sheet = al_load_bitmap(buffer);
    must_init(sheet, "monster sprite sheet");

    //knight
    for(int i = 0; i<8; i++){
        EnemySprites[i].bitmap = sprite_grab(sheet, i*16, 0, 16, 16);
    }

    EnemySprites[8].bitmap = sprite_grab(sheet, 0, 16, 16, 16);

}

void ResetEnemies(){
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            for(int n = 0; n<5; n++){
                if(enemies[i][j][n] == NULL) continue;

                free(enemies[i][j][n]);
                enemies[i][j][n] = 0;
            }
        }
    }
}

//ENEMY CREATION

Enemy *CreateKnightEnemy(int posX, int posY){
    Enemy *newEnemy = malloc(sizeof(Enemy));

    //for now, always generate the test enemy
    SetVector2f(&(newEnemy->position), (float)posX, (float)posY);
    SetBoxColliderF(&(newEnemy->collider), posX, posY, 16, 16);
    
    newEnemy->attackPower = 50 + (CurrentFloor-1)*50;
    newEnemy->currentHealth = 30 + (CurrentFloor-1)*10;
    newEnemy->maxHealth = 30 + (CurrentFloor-1)*10;
    
    for(int i = 0; i<8; i++){
        newEnemy->WalkingAnimations[i/2][i%2] = EnemySprites[i];
    }

    newEnemy->currentSprite = newEnemy->WalkingAnimations[0][0];

    newEnemy->DamagedCounter = 0;
    newEnemy->CurrentDestination = newEnemy->position;
    newEnemy->speed = 0.4;
    newEnemy->FrameCounter = 0;
    //newEnemy->Velocity.x = newEnemy->speed;
    newEnemy->AnimFrame = 0;
    
    newEnemy->type = KnightEnemy;

    return newEnemy;
}

Enemy *CreateHeartEnemy(int posX, int posY){
    Enemy *newEnemy = malloc(sizeof(Enemy));

    //for now, always generate the test enemy
    SetVector2f(&(newEnemy->position), (float)posX, (float)posY);
    SetBoxColliderF(&(newEnemy->collider), posX, posY, 16, 16);
    
    newEnemy->attackPower = 0;
    newEnemy->currentHealth = 50;
    newEnemy->maxHealth = 50;
    
    for(int i = 0; i<8; i++){
        newEnemy->WalkingAnimations[i/2][i%2] = EnemySprites[8];
    }

    newEnemy->currentSprite = newEnemy->WalkingAnimations[0][0];

    newEnemy->DamagedCounter = 0;
    newEnemy->CurrentDestination = newEnemy->position;
    newEnemy->speed = 0;
    newEnemy->FrameCounter = 0;
    //newEnemy->Velocity.x = newEnemy->speed;
    newEnemy->AnimFrame = 0;

    newEnemy->type = Heart;

    return newEnemy;
}





//END OF ENEMY CREATION

Enemy *GenerateEnemy(Level *room, int posX, int posY){
    
    return CreateKnightEnemy(posX, posY);
}

bool CheckForEnemyCollision(Enemy *thisEnemy, int index){

    for(int otherEnemy = 0; otherEnemy < 5; otherEnemy++){

        if(otherEnemy == index || enemies[GetCurrentRoom().x][GetCurrentRoom().y][otherEnemy] == NULL) continue;

        if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][otherEnemy]->type == Heart) continue;

        if(CheckCollisionF(thisEnemy->collider, enemies[GetCurrentRoom().x][GetCurrentRoom().y][otherEnemy]->collider)){
            return true;
        }
    }

    if(CollidedWithWalls(thisEnemy->collider)) return true;

    return false;

}

void UpdateEnemyPosition(Enemy *thisEnemy, int index){
    thisEnemy->position.x += thisEnemy->Velocity.x;
    thisEnemy->position.y += thisEnemy->Velocity.y;

    thisEnemy->collider.Origin = thisEnemy->position;

    if(CheckForEnemyCollision(thisEnemy, index)){
        thisEnemy->position.x -= thisEnemy->Velocity.x;
        thisEnemy->position.y -= thisEnemy->Velocity.y;

        thisEnemy->collider.Origin = thisEnemy->position;

        thisEnemy->CurrentDestination = thisEnemy->position;   
    }

}

void ResetEnemyPositions(){
    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][0] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][0]->position), 96, 64);
    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][0] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][0]->collider.Origin), 96, 64);

    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][1] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][1]->position), 96, 96);
    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][1] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][1]->collider.Origin), 96, 96);

    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][2] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][2]->position), 144, 64);
    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][2] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][2]->collider.Origin), 144, 64);

    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][3] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][3]->position), 144, 96);
    if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][3] != 0) SetVector2f(&(enemies[GetCurrentRoom().x][GetCurrentRoom().y][3]->collider.Origin), 144, 96);
}

Vector2 oldRoom = {5, 5};

//update the position/collision and other stuff of enemies 
void HandleEnemies(){

    if(!EqualVectorsInt(oldRoom, GetCurrentRoom(), 0)){
        oldRoom = GetCurrentRoom();
        ResetEnemyPositions();
    }

    for(int i = 0; i<5; i++){
        if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][i] == 0) continue;

        Enemy *thisEnemy = enemies[GetCurrentRoom().x][GetCurrentRoom().y][i];


        //the enemy is feeling the knockback
        if(thisEnemy->DamagedCounter > 0){

            thisEnemy->DamagedCounter--;
            SetVector2f(&(thisEnemy->Velocity), thisEnemy->Velocity.x * 0.5, thisEnemy->Velocity.y * 0.5);
            
            UpdateEnemyPosition(thisEnemy, i);

            if(thisEnemy->DamagedCounter == 0){
                thisEnemy->CurrentDestination = thisEnemy->position;
                
                if(thisEnemy->currentHealth <= 0){
                    Score += 100;
                    

                    int heartChance = rand()%20;
                    if(heartChance >= 15){
                        //maybe spawn a heart
                        enemies[GetCurrentRoom().x][GetCurrentRoom().y][i] = CreateHeartEnemy(thisEnemy->position.x, thisEnemy->position.y);
                    }
                    else{
                        enemies[GetCurrentRoom().x][GetCurrentRoom().y][i] = 0;
                    }

                    free(thisEnemy);
                    //enemies[GetCurrentRoom().x][GetCurrentRoom().y][i] = 0;
                    continue;
                }
            }

            continue;
        }


        
        //handle collision with sword
        if(CheckCollisionF(thisEnemy->collider, SwordCollider) && thisEnemy->DamagedCounter == 0 && thisEnemy->attackPower > 0){
            
            //push according to player direction
            Vector2 tmp = GetDirectionVector(PlayerDirection);

            thisEnemy->currentHealth -= 10;
            
            SetVector2f(&(thisEnemy->Velocity), (float)(tmp.x) * thisEnemy->speed*32, -1*(float)(tmp.y) * thisEnemy->speed*32);

            thisEnemy->DamagedCounter = 10;

            UpdateEnemyPosition(thisEnemy, i);

            continue;
        }

        if(CheckCollisionF(thisEnemy->collider, PlayerCollider) && !IsPlayerDamaged() && thisEnemy->attackPower > 0){
            Vector2f pushVel;
            SetVector2f(&pushVel, (thisEnemy->Velocity.x/0.4)*16, (thisEnemy->Velocity.y/0.4)*16);
            DamagePlayer(thisEnemy->attackPower, pushVel);
            
        }
        else if(CheckCollisionF(thisEnemy->collider, PlayerCollider)){

            if(thisEnemy->type == Heart){

                GivePlayerHealth(thisEnemy->currentHealth);

                free(thisEnemy);
                enemies[GetCurrentRoom().x][GetCurrentRoom().y][i] = 0;
            }

            continue;

        }

        if(EqualVectors(thisEnemy->position, thisEnemy->CurrentDestination, 10)){
            //time to pick a new destination

            thisEnemy->CurrentDestination = GetPlayerPosition();

            while(EqualVectors(thisEnemy->position, thisEnemy->CurrentDestination, 30)){
                //thisEnemy->CurrentDestination = GetPlayerPosition();

                //if(EqualVectors(thisEnemy->position, GetPlayerPosition(), 10)){}
                thisEnemy->CurrentDestination.x = 32 + (rand()%177);
                thisEnemy->CurrentDestination.y = 32 + (rand()%97);
            }
        }

        //update the enemy velocity based on its current destination
        if(Abs(thisEnemy->position.x - thisEnemy->CurrentDestination.x) > 10){
            if(thisEnemy->position.x < thisEnemy->CurrentDestination.x){
                thisEnemy->Velocity.x = thisEnemy->speed;
                thisEnemy->Velocity.y = 0;
            }
            else{
                thisEnemy->Velocity.x = -thisEnemy->speed;
                thisEnemy->Velocity.y = 0;
            }
        }
        else{
            if(thisEnemy->position.y < thisEnemy->CurrentDestination.y){
                thisEnemy->Velocity.y = thisEnemy->speed;
                thisEnemy->Velocity.x = 0;
            }
            else{
                thisEnemy->Velocity.y = -thisEnemy->speed;
                thisEnemy->Velocity.x = 0;
            }
        }

        //printf("destination 1: %f %f\n", thisEnemy->CurrentDestination.x, thisEnemy->CurrentDestination.y);
        //printf("velocity 1: %f %f\n", thisEnemy->Velocity.x, thisEnemy->Velocity.y);
        //printf("position 1: %f %f\n", thisEnemy->position.x, thisEnemy->position.y);

        UpdateEnemyPosition(thisEnemy, i);
    
        //printf("destination 2: %f %f\n\n", thisEnemy->CurrentDestination.x, thisEnemy->CurrentDestination.y);

    }


}

void GenerateEnemies(int x, int y){
    Level *thisRoom = GetRoom(x, y);
    if(thisRoom == NULL || (x==5 && y==5)) return;

    enemies[x][y][0] = GenerateEnemy(thisRoom, 96, 64);
    enemies[x][y][1] = GenerateEnemy(thisRoom, 96, 96);
    enemies[x][y][2] = GenerateEnemy(thisRoom, 144, 64);
    enemies[x][y][3] = GenerateEnemy(thisRoom, 144, 96);
}

void init_enemies(){

    ResetEnemies();

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            GenerateEnemies(i,j);
        }
    }
}


void DrawEnemies(){

    for(int i = 0; i<5; i++){

        if(enemies[GetCurrentRoom().x][GetCurrentRoom().y][i] == 0) continue;

        Enemy *thisEnemy = enemies[GetCurrentRoom().x][GetCurrentRoom().y][i];

        if(thisEnemy->DamagedCounter > 0){
            al_draw_tinted_bitmap(thisEnemy->currentSprite.bitmap, al_map_rgb(144,0,0), (int)thisEnemy->position.x, (int)thisEnemy->position.y, 0);
            continue;
        }


        thisEnemy->FrameCounter++;

        if(thisEnemy->FrameCounter > 6){
            thisEnemy->FrameCounter = 0;
            thisEnemy->AnimFrame++;
            thisEnemy->AnimFrame %= 2;
        }

             if(thisEnemy->Velocity.y < 0) thisEnemy->currentSprite = thisEnemy->WalkingAnimations[NORTH][thisEnemy->AnimFrame];
        else if(thisEnemy->Velocity.x > 0) thisEnemy->currentSprite = thisEnemy->WalkingAnimations[EAST][thisEnemy->AnimFrame];
        else if(thisEnemy->Velocity.y > 0) thisEnemy->currentSprite = thisEnemy->WalkingAnimations[SOUTH][thisEnemy->AnimFrame];
        else if(thisEnemy->Velocity.x < 0) thisEnemy->currentSprite = thisEnemy->WalkingAnimations[WEST][thisEnemy->AnimFrame];

        //printf("%d\n", thisEnemy->currentSprite.bitmap);
        al_draw_bitmap(thisEnemy->currentSprite.bitmap, (int)thisEnemy->position.x, (int)thisEnemy->position.y, 0);
    }
}
