#include <iostream>
#include "kick_sample.h"

#define TAU M_PI * 2

KickSample::KickSample()
{
    AudioEngine *engine = new AudioEngine(&GenerateKickSample);
    mEngine = engine;
}

KickSample::~KickSample()
{
    mEngine = nullptr;
}

void KickSample::play()
{
    mEngine->play();
}

void KickSample::pause()
{
    mEngine->pause();
}

double KickSample::GenerateKickSample(double time)
{
    return sin(mFrequency * TAU * time);
}
