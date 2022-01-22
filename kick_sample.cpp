#include <iostream>
#include "kick_sample.h"

#define TAU M_PI * 2

KickSample::KickSample()
{
    Envelope::Settings settings = {
        .attackDuration =  0.05,
        .decayDuration =  0.1,
        .releaseDuration =  0.05,
        .sustainDuration =  0.1,
        .sustainAmplitude =  0.5,
    };
    Envelope *envelope = new Envelope(&settings);

    AudioEngine *engine = new AudioEngine(envelope, &GenerateKickSample);
    mEngine = engine;
}

KickSample::~KickSample()
{
    mEngine = nullptr;
}

void KickSample::trigger()
{
    mEngine->play();
}

double KickSample::GenerateKickSample(double time)
{
    return sin(mFrequency * TAU * time);
}
