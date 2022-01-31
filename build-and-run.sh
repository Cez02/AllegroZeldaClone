#!/bin/bash

lowlevel=src/lowlevel/
menu=src/Menu/
settings=src/Settings/
ingame=src/Ingame/

#create the build directory

if [ -d "./build" ] 
then
    rm -r build
fi

mkdir build

cp -r src/Assets build

gcc -fcommon ${lowlevel}Generics.c ${lowlevel}SoundHandler.c ${lowlevel}Physics.c ${lowlevel}InputHandler.c ${lowlevel}DisplayHandler.c ${menu}MainMenuHandler.c ${settings}SettingsHandler.c ${ingame}TerrainHandler.c ${ingame}PlayerHandler.c ${ingame}EnemyHandler.c ${ingame}UIHandler.c ${ingame}GameHandler.c src/main.c -o ./build/play $(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)

cd build

./play

cd ..