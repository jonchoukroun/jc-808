#ifndef KickSampleH
#define KickSampleH

#include <SDL2/SDL.h>
#include "audio_engine.h"
#include "envelope.h"

class KickSample
{
public:
    KickSample();
    ~KickSample();

    void trigger();

private:
    static const int mFrequency = 80;

    AudioEngine *mEngine = nullptr;

    // Will not work as non-static member function pointer
    // when passed to AudioEngine.
    static double GenerateKickSample(double time);
};

#endif
