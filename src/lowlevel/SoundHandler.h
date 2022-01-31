#pragma once

float MusicVolume;
float SFXVolume;

enum Sounds{
    SOUND_BUTTON_CLICK
};

void init_audio();

void ChangeMusicVolume(float newValue);

void ChangeSFXVolume(float newValue);

void PlaySound(enum Sounds sound);

void PlayMusic(int MusicIndex);
