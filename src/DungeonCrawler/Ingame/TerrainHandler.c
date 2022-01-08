#include "TerrainHandler.h"

#include "../lowlevel/Generics.h"


const int ROOM_COUNT = 10;

bool spritesLoaded = false;
Sprite TerrainSprites[64];
/*
    0    = dungeon border
    1-4  = doors open
    5-8  = doors closed
    9-12 = floor tiles    
    13   = exit floor tile
*/

Level *Rooms[10][10];
int RoomsToCreate = ROOM_COUNT;
Vector2 RoomQueue[101];
bool isOnQueue[10][10];
int currentRoomIndex=0, nextRoomIndex=1;
Vector2 CurrentRoomCoords;

bool CollidersSet = false;
bool collidersUpdated = false;


BoxCollider DoorColliders[4];

//there are two spots for each wall
//if theres a door then we need to two colliders
//otherwise 1 collider suffices
BoxCollider WallColliders[8];

BoxCollider NewFloorTile;

Vector2 PlayerSpawnPositions[4];


void LoadSprites(){

    ALLEGRO_BITMAP *sheet = al_load_bitmap("src/DungeonCrawler/Assets/Ingame/DungeonTileset.png");
    must_init(sheet, "terrain sprite sheet");

    TerrainSprites[0].bitmap = sprite_grab(sheet, 0, 80, 256, 176);
    
    //get the doors
    for(int i = 1; i<=8; i++){
        TerrainSprites[i].bitmap = sprite_grab(sheet, 32*(i-1), 48, 32, 32);
    }
    
    //get the floor tiles
    for(int i = 9; i<=12; i++){
        TerrainSprites[i].bitmap = sprite_grab(sheet, 16*(i-9), 0, 16, 16);
    }

    TerrainSprites[13].bitmap = sprite_grab(sheet, 64, 0, 16, 16);

    spritesLoaded = true;

    //al_destroy_bitmap(sheet);
}



bool AvailableRoom(Vector2 dir, int i, int j){
    if(dir.x + i < 0 || dir.x + i > 9) return false;
    if(dir.y + j < 0 || dir.y + j > 9) return false;

    return (Rooms[dir.x + i][dir.y + j] == 0 && !isOnQueue[dir.x + i][dir.y + j]);
}

void SetRoomTiles(int x, int y){
    
    //set the default tiles
    for(int i = 0; i<7; i++){
        for(int j = 0; j<12; j++){
            Rooms[x][y]->levelTiles[i][j] = 9;
        }
    }

    if(Rooms[x][y]->ThisLevelType == ROOM_NEXT_FLOOR){
        Rooms[x][y]->levelTiles[3][5] = 13;
    }
}

void ResetRooms(){
    RoomsToCreate = ROOM_COUNT;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            if(Rooms[i][j] != 0){
                free(Rooms[i][j]);
            }
            Rooms[i][j] = 0;
            isOnQueue[i][j] = false;
        }
    }

    for(int i = 0; i<100; i++){
        SetVector2(&RoomQueue[i], 0, 0);
    }
}

void GenerateRooms(){

    //flags:
    bool exitRoom = false;

    //room generation
    ResetRooms();

    currentRoomIndex = 0;
    nextRoomIndex = 1;
    RoomQueue[currentRoomIndex].x = 5;
    RoomQueue[currentRoomIndex].y = 5;
    isOnQueue[5][5] = true;
    RoomsToCreate--;

    while(currentRoomIndex < nextRoomIndex){
        //get the next room to build in the queue
        int i = RoomQueue[currentRoomIndex].x;
        int j = RoomQueue[currentRoomIndex].y;
        currentRoomIndex++;

        Rooms[i][j] = malloc(sizeof(Level));


        Rooms[i][j]->ThisLevelType = ROOM_TEST;

        int Chance = GetRandomDigit();

        if(((float)(Chance)/10 < 2 || currentRoomIndex == nextRoomIndex || RoomsToCreate == 0) && !exitRoom && currentRoomIndex > 4){
            exitRoom = true;
            printf("THIS ROOM IS EXIT %d %d\n", i, j);
            
            Rooms[i][j]->ThisLevelType = ROOM_NEXT_FLOOR;
        }

        SetRoomTiles(i, j);

        int howManyRoomsCanBeCreated = 0;

        //handle the doors that must exist (we'll add additional ones if need be)
        if(j != 9) Rooms[i][j]->doors[NORTH] = Rooms[i][j+1] != 0 ? Rooms[i][j+1]->doors[SOUTH] : 0;
        if(i !=  9) Rooms[i][j]->doors[EAST]  = Rooms[i+1][j] != 0 ? Rooms[i+1][j]->doors[WEST]  : 0;
        if(j !=  0) Rooms[i][j]->doors[SOUTH] = Rooms[i][j-1] != 0 ? Rooms[i][j-1]->doors[NORTH] : 0;
        if(i !=  0) Rooms[i][j]->doors[WEST]  = Rooms[i-1][j] != 0 ? Rooms[i-1][j]->doors[EAST]  : 0;


        Vector2 zeroVec; zeroVec.x = 0; zeroVec.y = 0;

        //if the adjacent place is empty and is not on the queue, then we can create a new room there
        if(AvailableRoom(GetDirectionVector(NORTH), i, j)) howManyRoomsCanBeCreated++;
        if(AvailableRoom(GetDirectionVector(EAST ), i, j)) howManyRoomsCanBeCreated++;
        if(AvailableRoom(GetDirectionVector(WEST ), i, j)) howManyRoomsCanBeCreated++;
        if(AvailableRoom(GetDirectionVector(SOUTH), i, j)) howManyRoomsCanBeCreated++;

        //now we decide whether we want to add new doors
        //which means creating new rooms

        /*

        if we have still yet to reach the desired number of rooms, we can
        choose a random number between 1 and min(rooms_left, rooms_available_to_create)
        to decide how many adjacent rooms to create

        from the available rooms we choose randomly according to the seed which rooms

        */

        //no rooms should be created
        if(RoomsToCreate == 0) continue;


        //how many new adjacent rooms to create
        int howManyNewDoors = GetRandomDigit()%4 + 1;
        howManyNewDoors = Min(howManyNewDoors, Min(RoomsToCreate, howManyRoomsCanBeCreated));

        RoomsToCreate -= howManyNewDoors;

        //cannot create new rooms here
        if(howManyNewDoors <= 0) continue;

        while(howManyNewDoors){

            int whereNewRoom = GetRandomDigit()%4;
            Vector2 dir = GetDirectionVector((DIRECTION)whereNewRoom);

            //if we chose a room thats not available, then go clockwise
            //until we get an available room
            while(!AvailableRoom(dir, i, j)){
                whereNewRoom++;
                whereNewRoom %= 4;
                dir = GetDirectionVector((DIRECTION)whereNewRoom);
            }

            //put the room on the queue
            Rooms[i][j]->doors[whereNewRoom] = true;
            isOnQueue[i + dir.x][j + dir.y] = true;

            RoomQueue[nextRoomIndex].x = i + dir.x;
            RoomQueue[nextRoomIndex].y = j + dir.y;
            nextRoomIndex++;

            howManyNewDoors--;
        }

    }

}

void SetColliders(){

    CollidersSet = true;

    //prepare doors colliders

    SetVector2(&DoorColliders[NORTH].Origin, 112, 0);
    SetVector2(&DoorColliders[NORTH].Dimensions, 31, 20);

    SetVector2(&DoorColliders[SOUTH].Origin, 112, 155);
    SetVector2(&DoorColliders[SOUTH].Dimensions, 31, 20);

    SetVector2(&DoorColliders[EAST].Origin, 236, 72);
    SetVector2(&DoorColliders[EAST].Dimensions, 19, 31);

    SetVector2(&DoorColliders[WEST].Origin, 0, 72);
    SetVector2(&DoorColliders[WEST].Dimensions, 19, 31);


    //prepare the player spawn positions (after room transitions)

    SetVector2(&PlayerSpawnPositions[NORTH], 120, 32);

    SetVector2(&PlayerSpawnPositions[SOUTH], 120, 128);

    SetVector2(&PlayerSpawnPositions[EAST], 207, 79);

    SetVector2(&PlayerSpawnPositions[WEST], 32, 79);
    
    
    //prepare the wall colliders

    SetVector2(&WallColliders[0].Origin,       0, 0);
    SetVector2(&WallColliders[0].Dimensions, 144, 32);
    SetVector2(&WallColliders[1].Origin,     144, 0);
    SetVector2(&WallColliders[1].Dimensions, 112, 32);

    SetVector2(&WallColliders[2].Origin,    224, 32);
    SetVector2(&WallColliders[2].Dimensions, 32, 72);
    SetVector2(&WallColliders[3].Origin,    224, 104);
    SetVector2(&WallColliders[3].Dimensions, 32, 72);

    SetVector2(&WallColliders[4].Origin,       0, 144);
    SetVector2(&WallColliders[4].Dimensions, 144, 32);
    SetVector2(&WallColliders[5].Origin,     144, 144);
    SetVector2(&WallColliders[5].Dimensions, 112, 32);

    SetVector2(&WallColliders[6].Origin,      0, 32);
    SetVector2(&WallColliders[6].Dimensions, 32, 72);
    SetVector2(&WallColliders[7].Origin,      0, 104);
    SetVector2(&WallColliders[7].Dimensions, 32, 72);

    SetVector2(&(NewFloorTile.Dimensions), 16, 16);
    SetVector2(&(NewFloorTile.Origin),      0, 0);
    

}

void InitTerrain(){
    if(!spritesLoaded) LoadSprites();
    GenerateRooms();

    CurrentRoomCoords.x = 5;
    CurrentRoomCoords.y = 5;

    collidersUpdated = false;

    //NewFloorTile.Origin.x = 0;
    //NewFloorTile.Origin.y = 0;

    if(!CollidersSet) SetColliders();
}

void DeinitTerrain(){

}

void DrawTerrain(){

/*
    for(int j = 9; j>=0; j--){
        for(int i = 0; i<=9; i++){
            if(i == CurrentRoomCoords.x && j == CurrentRoomCoords.y){
                printf("*");
                continue;
            }

            if(Rooms[i][j] != 0) printf("1");
            else printf("0");
        }
        putchar('\n');printf("What room: %d\n", entering);
    }

    printf("Redraw this shit\n");
    printf("%d %d\n", CurrentRoomCoords.x, CurrentRoomCoords.y);
    */

    //draw the border tiles
    al_draw_bitmap(TerrainSprites[0].bitmap, 0, 0, 0);


    //draw he current level tiles
    
    for(int i = 0; i<7; i++){
        for(int j = 0; j<12; j++){
            al_draw_bitmap(TerrainSprites[Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->levelTiles[i][j]].bitmap,
            32 + j * 16,
            32 + i * 16,
            0);
        }
    }

    //draw the doors

    if(Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[NORTH])
        al_draw_bitmap(TerrainSprites[1].bitmap, 112, 0, 0);
    else
        al_draw_bitmap(TerrainSprites[5].bitmap, 112, 0, 0);


    if(Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[WEST])
        al_draw_bitmap(TerrainSprites[2].bitmap, 0, 72, 0);
    else
        al_draw_bitmap(TerrainSprites[6].bitmap, 0, 72, 0);


    if(Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[EAST])
        al_draw_bitmap(TerrainSprites[3].bitmap, 224, 72, 0);
    else
        al_draw_bitmap(TerrainSprites[7].bitmap, 224, 72, 0);


    if(Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[SOUTH])
        al_draw_bitmap(TerrainSprites[4].bitmap, 112, 144, 0);
    else
        al_draw_bitmap(TerrainSprites[8].bitmap, 112, 144, 0);

}

void EnteringNewRoom(BoxCollider *PlayerCollider, Vector2 *PlayerPosition){
    int entering = -1;

         if(CheckCollision(*PlayerCollider, DoorColliders[NORTH]) && Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[NORTH])
        entering = NORTH;
    else if(CheckCollision(*PlayerCollider,  DoorColliders[EAST]) && Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[EAST] )
        entering = EAST;
    else if(CheckCollision(*PlayerCollider, DoorColliders[SOUTH]) && Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[SOUTH])
        entering = SOUTH;
    else if(CheckCollision(*PlayerCollider,  DoorColliders[WEST]) && Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[WEST] )
        entering = WEST;

    if(entering == -1) return;

    if(!Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[entering]) return;

    //move the level and set new position
    MoveLevel(GetDirectionVector(entering), entering);

    (*PlayerPosition).x = PlayerSpawnPositions[(entering+2)%4].x;
    (*PlayerPosition).y = PlayerSpawnPositions[(entering+2)%4].y;
    PlayerCollider->Origin.x = PlayerSpawnPositions[(entering+2)%4].x;
    PlayerCollider->Origin.y = PlayerSpawnPositions[(entering+2)%4].y;

    collidersUpdated = false;

}


void UpdateColliders(){

    if(collidersUpdated) return;
    collidersUpdated = true;

    //update each of the walls.

    Level *thisRoom = Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y];

    if(thisRoom->doors[NORTH]) SetVector2(&WallColliders[0].Dimensions, 112, 32);
                          else SetVector2(&WallColliders[0].Dimensions, 144, 32);
                    
    if(thisRoom->doors[EAST] ) SetVector2(&WallColliders[2].Dimensions, 32, 40);
                          else SetVector2(&WallColliders[2].Dimensions, 32, 72);

    if(thisRoom->doors[SOUTH]) SetVector2(&WallColliders[4].Dimensions, 112, 32);
                          else SetVector2(&WallColliders[4].Dimensions, 144, 32);
                    
    if(thisRoom->doors[WEST] ) SetVector2(&WallColliders[6].Dimensions, 32, 40);
                          else SetVector2(&WallColliders[6].Dimensions, 32, 72);

    //place the exit room tile
    if(thisRoom->ThisLevelType == ROOM_NEXT_FLOOR){
        SetVector2(&(NewFloorTile.Origin), 112, 80);
    }
    else{
        SetVector2(&(NewFloorTile.Origin), 0, 0);
    }

}

void MoveLevel(Vector2 directionVec, DIRECTION dir){

    if(!Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y]->doors[dir]) return;

    CurrentRoomCoords.x += directionVec.x;
    CurrentRoomCoords.y += directionVec.y;

    if(CurrentRoomCoords.x < 0 || CurrentRoomCoords.x > 9){
        CurrentRoomCoords.x -= directionVec.x;
        CurrentRoomCoords.y -= directionVec.y;
        return;
    }


    if(CurrentRoomCoords.y < 0 || CurrentRoomCoords.y > 9){
        CurrentRoomCoords.x -= directionVec.x;
        CurrentRoomCoords.y -= directionVec.y;
        return;
    }

    if(Rooms[CurrentRoomCoords.x][CurrentRoomCoords.y] == 0){
        CurrentRoomCoords.x -= directionVec.x;
        CurrentRoomCoords.y -= directionVec.y;
        return;
    }

    UpdateColliders();
}

bool CollidedWithWalls(BoxCollider entity){

    for(int i = 0; i<8; i++) if(CheckCollision(entity, WallColliders[i])) return true;

    return false;

}

bool CollidedWithNewFloorTile(BoxCollider player){
    return CheckCollision(player, NewFloorTile);
}
