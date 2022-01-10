#!/bin/bash

gcc src/DungeonCrawler/lowlevel/Generics.c src/DungeonCrawler/lowlevel/Physics.c src/DungeonCrawler/lowlevel/InputHandler.c src/DungeonCrawler/lowlevel/DisplayHandler.c src/DungeonCrawler/Menu/MainMenuHandler.c src/DungeonCrawler/Ingame/TerrainHandler.c src/DungeonCrawler/Ingame/PlayerHandler.c src/DungeonCrawler/Ingame/GameHandler.c src/DungeonCrawler/main.c -o play $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)
./play