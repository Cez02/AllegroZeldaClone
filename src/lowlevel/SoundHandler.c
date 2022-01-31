#include "SoundHandler.h"

#include "Generics.h"


ALLEGRO_SAMPLE *SFXSamples[10];
ALLEGRO_SAMPLE *MusicSamples[2];

#define SAMPLE_COUNT 16

ALLEGRO_SAMPLE_ID currentMusicSample;

void GetAssetDirectory(char buf[], char name[]){
    strcpy(buf, AssetDirectory);
    strcat(buf, name);   
}

ALLEGRO_SAMPLE *LoadSound(char buffer[], char name[]){
    ALLEGRO_SAMPLE *tmp;
    GetAssetDirectory(buffer, name);
    tmp = al_load_sample(buffer);
    must_init(tmp, name);
    return tmp;
}

void init_audio(){

    MusicVolume = 0.4;
    SFXVolume = 0.4;

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(SAMPLE_COUNT), "reserve samples");

    char buffer[200];

    //load SFX
    SFXSamples[SOUND_BUTTON_CLICK] = LoadSound(buffer, "MainMenu/Button.wav");

    //load music
    MusicSamples[0] = LoadSound(buffer, "Ingame/GameMusic.wav");
    MusicSamples[1] = LoadSound(buffer, "Ingame/GameMusic.wav");

}

void ChangeMusicVolume(float newValue){
    MusicVolume = newValue;
}

void ChangeSFXVolume(float newValue){
    SFXVolume = newValue;
}

void PlaySound(enum Sounds sound){
    al_play_sample(SFXSamples[sound], SFXVolume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

bool musicPlaying = false;

void PlayMusic(int MusicIndex){
    if(musicPlaying) al_stop_sample(&currentMusicSample);
    al_play_sample(MusicSamples[MusicIndex], MusicVolume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &currentMusicSample);
    musicPlaying = true;
}
