#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <array>
#include <SDL2/SDL.h>
#include <vector>
#include "kick.h"
#include "snare.h"

using std::array;
using std::vector;
using Sequencer = array<Instrument *, 8>;

class AudioEngine
{
public:
    AudioEngine(Sequencer *seq);
    ~AudioEngine();

    void start();
    void stop();
    bool isPlaying();

    SDL_AudioDeviceID getAudioDevice();

private:
    Sequencer *mSeq;
    int mSeqPos;
    bool mPlaying;

    vector<Instrument *> mActiveSamples;

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
