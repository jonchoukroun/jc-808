#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <SDL2/SDL.h>
#include "kick.h"
#include "snare.h"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    void start();
    void stop();

    void playKick(Kick *kick);
    void playSnare(Snare *snare);

    SDL_AudioDeviceID getAudioDevice();

private:
    Kick *mKick;
    Snare *mSnare;

    static const int mSampleRate = 44100;
    static const int mSampleSize = 512;
    static const int mChannels = 1;

    double mTime;
    static constexpr double mTimeStep = 1.0 / (double)mSampleRate;

    SDL_AudioDeviceID mDeviceId = 0;
    SDL_AudioSpec mReceivedSpec;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);
};

#endif
