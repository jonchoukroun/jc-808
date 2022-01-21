#ifndef KickSampleH
#define KickSampleH

#include <SDL2/SDL.h>
#include "audio_engine.h"

class KickSample
{
public:
    KickSample();
    ~KickSample();

    void play();
    // TODO: replace with ADSR
    void pause();

private:
    static const int mFrequency = 80;

    AudioEngine *mEngine;

    // Will not work as non-static member function pointer
    // when passed to AudioEngine.
    static double GenerateKickSample(double time);
};

#endif
