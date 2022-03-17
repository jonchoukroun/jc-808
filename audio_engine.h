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
    static const int m_sampleRate = 44100;
    static const int m_sampleSize = 1024;
    static const int m_channels = 1;

    SDL_AudioDeviceID m_deviceId = 0;
    SDL_AudioSpec m_receivedSpec {};

    static constexpr double m_timeStep = 1.0 / (double)m_sampleRate;
    bool m_playing {false};

    Sequencer &m_seq;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);

};

#endif
