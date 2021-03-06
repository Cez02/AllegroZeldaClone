#include "PlayerHandler.h"


PlayerStats statistics;

Vector2f PlayerPosition;
Vector2f OldVelocity;
Vector2f PlayerVelocity;
Vector2f Speed;

//all two-frame cycles starting from up direction going clockiwse
Sprite PlayerSpritesMovement[8];
Sprite PlayerAttackSprites[4];
Sprite PlayerSwordSprites[4];
Sprite currentPlayerSprite;
Sprite currentSwordSprite;

bool assetsLoaded = false;

Vector2f SwordSpritePosition;

int PlayerDamagedCounter = 0;

#define PLAYER_SPRITE_SIZE 16


//Damage player functions
void DamagePlayer(int damage, Vector2f velocity){
    PlayerDamagedCounter = 90;
    if(PlayerVelocity.x != 0 || PlayerVelocity.y != 0)
        SetVector2f(&(velocity), -1*(float)(GetDirectionVector(PlayerDirection).x) * 10, (float)(GetDirectionVector(PlayerDirection).y) * 10);

    statistics.currentHealth -= damage;
    PlayerVelocity = velocity;
}

void GivePlayerHealth(int health){
    statistics.currentHealth += health;
    statistics.currentHealth = Min(statistics.currentHealth, statistics.maxHealth);
}



//Load player  sprites
void LoadPlayerSprites(){

    if(assetsLoaded) return;
    assetsLoaded = true;

    char buffer[100];
    strcpy(buffer, AssetDirectory);
    strcat(buffer, "Ingame/PlayerSprites.png");

    ALLEGRO_BITMAP *sheet = al_load_bitmap(buffer);
    must_init(sheet, "player sprite sheet");

    for(int i = 0; i<4; i++){
        PlayerSpritesMovement[i*2].bitmap     = sprite_grab(sheet, i*16, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
        PlayerSpritesMovement[i*2 + 1].bitmap = sprite_grab(sheet, i*16, 16, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
        PlayerAttackSprites[i].bitmap = sprite_grab(sheet, i*16, 32, 16, 16);
        PlayerSwordSprites[i].bitmap = sprite_grab(sheet, i*16, 48, 16, 16);
    }

    currentPlayerSprite = PlayerSpritesMovement[0];
    currentSwordSprite = PlayerSwordSprites[2];
}

void SetSwordPosition(DIRECTION dir){

    currentSwordSprite = PlayerSwordSprites[dir];
    SetVector2f(&SwordSpritePosition, PlayerPosition.x + GetDirectionVector(dir).x*16, PlayerPosition.y - GetDirectionVector(dir).y*16);

    switch(dir){

        case NORTH:
            SwordCollider.Origin.x = PlayerCollider.Origin.x + 3;
            SwordCollider.Origin.y = PlayerCollider.Origin.y - 12;
            SwordCollider.Dimensions.x = 7;
            SwordCollider.Dimensions.y = 12;
            break;
        case EAST:
            SwordCollider.Origin.x = PlayerCollider.Origin.x + 16;
            SwordCollider.Origin.y = PlayerCollider.Origin.y + 8;
            SwordCollider.Dimensions.x = 10;
            SwordCollider.Dimensions.y = 3;
            break;
        case SOUTH:
            SwordCollider.Origin.x = PlayerCollider.Origin.x + 7;
            SwordCollider.Origin.y = PlayerCollider.Origin.y + 16;
            SwordCollider.Dimensions.x = 3;
            SwordCollider.Dimensions.y = 11;
            break;
        case WEST:
            SwordCollider.Origin.x = PlayerCollider.Origin.x - 11;
            SwordCollider.Origin.y = PlayerCollider.Origin.y + 8;
            SwordCollider.Dimensions.x = 11;
            SwordCollider.Dimensions.y = 3;
            break;
    }

}

void InitPlayer(){
    
    LoadPlayerSprites();
    
    PlayerDead = false;
    
    PlayerVelocity.x = 0;
    PlayerVelocity.y = 0;
    Speed.x = 1;
    Speed.y = 1;
    PlayerPosition.x = 64;
    PlayerPosition.y = 64;
    PlayerDirection = NORTH;

    PlayerDead = false;

    statistics.currentHealth = 300 + (CurrentFloor/2)*100;
    statistics.maxHealth =  300 + (CurrentFloor/2)*100;
    PlayerDamagedCounter = 0;

    SetBoxColliderF(&PlayerCollider, 64, 64, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);

    SetBoxColliderF(&SwordCollider, 0, 0, 16, 16);

    SetVector2f(&SwordSpritePosition, PlayerPosition.x, PlayerPosition.y+16);


}

void DeinitPlayer(){
    for(int i = 0; i<4; i++){
        al_destroy_bitmap(PlayerSpritesMovement[i*2].bitmap);
        al_destroy_bitmap(PlayerSpritesMovement[i*2 + 1].bitmap);
    }
}

int frameCounter = 0;
bool currentSpriteOffset = 0;
void PlayerAnimation(bool *redraw){

    if(PlayerVelocity.x == 0 && PlayerVelocity.y == 0) return;

    //change player sprite every 2 frames

    frameCounter++;
    if(frameCounter % 10 != 0){
        return;
    }

    int dir = 0;

         if(PlayerVelocity.x > 0) dir = 1;
    else if(PlayerVelocity.y > 0) dir = 2;
    else if(PlayerVelocity.x < 0) dir = 3;

    currentSpriteOffset = !currentSpriteOffset;

    currentPlayerSprite = PlayerSpritesMovement[dir*2 + currentSpriteOffset];
    *redraw = true;
}

//the two following functions are generally more for the aesthetic

void ChangeDirection(){
    if(PlayerVelocity.x == OldVelocity.x && PlayerVelocity.y == OldVelocity.y) return;

    //going right
    if(PlayerVelocity.x > 0){
        currentPlayerSprite = PlayerSpritesMovement[2];
        
        return;
    }
    if(PlayerVelocity.x < 0){
        currentPlayerSprite = PlayerSpritesMovement[6];
        return;
    }
    if(PlayerVelocity.y < 0){
        currentPlayerSprite = PlayerSpritesMovement[0];
        return;
    }

    currentPlayerSprite = PlayerSpritesMovement[4];

    currentSpriteOffset = 0;

}

void ToIdle(){
    if(OldVelocity.x > 0){
        currentPlayerSprite = PlayerSpritesMovement[2];
        return;
    }
    if(OldVelocity.x < 0){
        currentPlayerSprite = PlayerSpritesMovement[6];
        return;
    }
    if(OldVelocity.y < 0){
        currentPlayerSprite = PlayerSpritesMovement[0];
        return;
    }

    currentPlayerSprite = PlayerSpritesMovement[4];

    currentSpriteOffset = 0;

}

int PlayerAttackingCounter = 0;
bool playerAttacking = false;

void PlayerAttack(){

    if(IsPlayerDamaged()) return;

    //set the sword collider and sprite
    SetSwordPosition(PlayerDirection);

    //frame counter
    PlayerAttackingCounter = 17;
    playerAttacking = true;

    currentPlayerSprite = PlayerAttackSprites[PlayerDirection];
}

//handles the player input and movement
void PlayerMovement(bool *redraw){

    if(PlayerDead) return;


    if(PlayerDamagedCounter > 64){

        ToIdle();

        //update the player position;
        PlayerPosition.x += PlayerVelocity.x;
        PlayerPosition.y += PlayerVelocity.y;

        OldVelocity = PlayerVelocity;

        PlayerPosition.y = Minf(127, Maxf(33, PlayerPosition.y));
        PlayerPosition.x = Minf(207, Maxf(33, PlayerPosition.x));

        //check if the player is colliding with a wall
        //if collided, then turn go back to the previous position
        if(CollidedWithWalls(PlayerCollider)){
            PlayerPosition.x -= PlayerVelocity.x;
            PlayerPosition.y -= PlayerVelocity.y;

        }


        PlayerCollider.Origin.x = PlayerPosition.x;
        PlayerCollider.Origin.y = PlayerPosition.y;

        return;
    }


    //player input
    PlayerVelocity.x = 0;
    PlayerVelocity.y = 0;

    if(ButtonClicked(ALLEGRO_KEY_X) && !IsPlayerDamaged()){
        PlayerAttack();
        *redraw = true;
    }

    if(playerAttacking) return;


    if(ButtonHeldDown(ALLEGRO_KEY_D) || ButtonHeldDown(ALLEGRO_KEY_RIGHT)){
        PlayerVelocity.x += Speed.x;
        PlayerDirection = EAST;
    }
    else if(ButtonHeldDown(ALLEGRO_KEY_A) || ButtonHeldDown(ALLEGRO_KEY_LEFT)){
        PlayerVelocity.x -= Speed.x;
        PlayerDirection = WEST;
    }
    else if(ButtonHeldDown(ALLEGRO_KEY_W) || ButtonHeldDown(ALLEGRO_KEY_UP)){
        PlayerVelocity.y -= Speed.y;
        PlayerDirection = NORTH;
    }
    else if(ButtonHeldDown(ALLEGRO_KEY_S) || ButtonHeldDown(ALLEGRO_KEY_DOWN)){
        PlayerVelocity.y += Speed.y;
        PlayerDirection = SOUTH;
    }

    if(PlayerVelocity.x != 0 || PlayerVelocity.y != 0) *redraw = true;
    if((OldVelocity.x != 0 || OldVelocity.y != 0) && PlayerVelocity.x == 0 && PlayerVelocity.y == 0){
        ToIdle();
        *redraw = true;
    }

    //update the player position;
    PlayerPosition.x += PlayerVelocity.x;
    PlayerPosition.y += PlayerVelocity.y;

    PlayerCollider.Origin.x = PlayerPosition.x;
    PlayerCollider.Origin.y = PlayerPosition.y;

    if(PlayerVelocity.x != 0 || PlayerVelocity.y != 0) ChangeDirection();

    OldVelocity = PlayerVelocity;


    //check if the player is colliding with a wall
    //if collided, then turn go back to the previous position
    if(CollidedWithWalls(PlayerCollider)){
        PlayerPosition.x -= PlayerVelocity.x;
        PlayerPosition.y -= PlayerVelocity.y;

        PlayerCollider.Origin.x = PlayerPosition.x;
        PlayerCollider.Origin.y = PlayerPosition.y;
    }

    if(CollidedWithNewFloorTile(PlayerCollider)){
        PlayerDamagedCounter = 0;
        CurrentFloor++;
        ChangingFloors = true;
    }

}

//simply draws the players current sprite
void DrawPlayer(){

    if(PlayerDead) return;

    if(playerAttacking && !IsPlayerDamaged()){
        al_draw_bitmap(currentSwordSprite.bitmap, SwordSpritePosition.x, SwordSpritePosition.y, 0);
    }

    if(IsPlayerDamaged() && (PlayerDamagedCounter%20 >= 10))
        al_draw_tinted_bitmap(currentPlayerSprite.bitmap, al_map_rgb(144, 0, 0) ,PlayerPosition.x, PlayerPosition.y, 0);
    else
        al_draw_bitmap(currentPlayerSprite.bitmap, PlayerPosition.x, PlayerPosition.y, 0);

}

int oldFloor = 0;

void HandlePlayer(ALLEGRO_EVENT *event, bool *done, bool *redraw){

    if(oldFloor != CurrentFloor){
        oldFloor = CurrentFloor;
        //statistics.currentHealth = 300 + (CurrentFloor/2)*100;
        statistics.maxHealth =  300 + (CurrentFloor/2)*100;
    }

    if(PlayerDead) return;

    if(statistics.currentHealth <= 0){
        PlayerDead = true;
        return;
    }

    //keyboard_update(event);

    PlayerMovement(redraw);
    PlayerAnimation(redraw);

    //handle being damaged
    if(IsPlayerDamaged()){
        if(PlayerDamagedCounter > 64)SetVector2f(&(PlayerVelocity), PlayerVelocity.x * 0.5, PlayerVelocity.y * 0.5);
        PlayerDamagedCounter--;
    }

    //handle the attacking
    if(PlayerAttackingCounter > 0){
        PlayerAttackingCounter--;
    }
    else if(playerAttacking){
        *redraw = true;
        playerAttacking = false;
        currentPlayerSprite = PlayerSpritesMovement[PlayerDirection*2];
        SetVector2f(&SwordCollider.Origin, 0, 0);
    }

    EnteringNewRoom(&PlayerCollider, &PlayerPosition);
}


//Accessors

PlayerStats GetPlayerStats(){
    return statistics;
}

Vector2f GetPlayerPosition(){
    return PlayerPosition;
}

bool IsPlayerDamaged(){
    return PlayerDamagedCounter > 0;
}