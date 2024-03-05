#pragma once
#include "ParticleSystem.hpp"
#include <SDL_image.h>

class Particle : public ParticleSystem
{
public:
    Particle() {}
    virtual ~Particle() {}

    enum PatticleStyle
    {
        NONE,
        FIRE,
        FIRE_WORK,
        SUN,
        GALAXY,
        FLOWER,
        METEOR,
        SPIRAL,
        EXPLOSION,
        SMOKE,
        SNOW,
        RAIN,
    };

    PatticleStyle style_ = NONE;
    void setStyle(PatticleStyle style);
    SDL_Texture* getDefaultTexture()
    {
        static SDL_Texture* t = IMG_LoadTexture(_renderer, "assets/fire.png");
        //printf(SDL_GetError());
        return t;
    }
};
