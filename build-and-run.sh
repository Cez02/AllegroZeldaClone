#!/bin/bash

lowlevel=src/lowlevel/
menu=src/Menu/
settings=src/Settings/
ingame=src/Ingame/

gcc ${lowlevel}Generics.c ${lowlevel}Physics.c ${lowlevel}InputHandler.c ${lowlevel}DisplayHandler.c ${menu}MainMenuHandler.c ${settings}SettingsHandler.c ${ingame}TerrainHandler.c ${ingame}PlayerHandler.c ${ingame}GameHandler.c src/main.c -o play $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)

./play