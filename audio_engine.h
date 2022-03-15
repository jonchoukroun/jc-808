#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <array>
#include <SDL2/SDL.h>
#include <vector>
#include "sequencer.h"

using std::array;
using std::vector;

class AudioEngine
{
public:
    AudioEngine(Sequencer &);
    ~AudioEngine();

    Sequencer & getSequencer();

    void start();
    void stop();
    bool isPlaying();

    SDL_AudioDeviceID getAudioDevice();

private:
    static const int mSampleRate = 44100;
    static const int mSampleSize = 1024;
    static const int mChannels = 1;

    SDL_AudioDeviceID mDeviceId = 0;
    SDL_AudioSpec mReceivedSpec {};

    static constexpr double mTimeStep = 1.0 / (double)mSampleRate;
    bool mPlaying {false};

    Sequencer &mSeq;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);

};

#endif
