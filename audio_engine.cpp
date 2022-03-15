#include <iostream>
#include "audio_engine.h"

using std::cout;
using std::endl;

const double GAIN = 40000.0;

AudioEngine::AudioEngine(Sequencer &seq)
: m_seq(seq)
{
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = m_sampleRate;
    desiredSpec.format = AUDIO_S16;
    desiredSpec.channels = 1;
    desiredSpec.samples = m_sampleSize;
    desiredSpec.callback = &audioCallback;
    desiredSpec.userdata = this;

    m_deviceId = SDL_OpenAudioDevice(
        NULL,
        SDL_FALSE,
        &desiredSpec,
        &m_receivedSpec,
        0
    );
    if (m_deviceId == 0) {
        cout << "Failed to open audio device! Error: " << SDL_GetError() << endl;
    }

    m_playing = false;
}

AudioEngine::~AudioEngine()
{
    SDL_CloseAudioDevice(m_deviceId);
}

Sequencer & AudioEngine::getSequencer()
{
    return m_seq;
}

void AudioEngine::start()
{
    m_seq.start();
    m_playing = true;
    SDL_PauseAudioDevice(m_deviceId, SDL_FALSE);
}

void AudioEngine::stop()
{
    m_seq.stop();
    m_playing = false;
    SDL_PauseAudioDevice(m_deviceId, SDL_TRUE);

}

bool AudioEngine::isPlaying()
{
    return m_playing;
}

SDL_AudioDeviceID AudioEngine::getAudioDevice()
{
    return m_deviceId;
}

void AudioEngine::audioCallback(void *userdata, Uint8 *stream, int len)
{
    const auto engine = reinterpret_cast<AudioEngine *>(userdata);
    engine->fillBuffer(stream, len);
}

void AudioEngine::fillBuffer(const Uint8* const stream, int len)
{
    short *out = (short *)stream;
    for (int i = 0; i < (len / sizeof(short)); i++) {
        double output = 0.0;

        vector<Instrument *> beat = m_seq.getActiveSamples();
        for (auto &i : beat) {
            if (i->isPlaying()) {
                output += i->getSample();
            }
        }
        out[i] = 0.8 * GAIN * output;

        m_seq.updateBy(m_timeStep);
    }
}

// double generateTriangle(int frequency, double time)
// {
//     return asin(sin(frequency * TAU * time)) * (2.0 / M_PI);
// }

// double generateSquare(int frequency, double time)
// {
//     return sin(frequency * TAU * time) > 0 ? 1.0 : -1.0;
// }

// // double generateSaw(int frequency, double time)
// // {
// //     double output = 0.0;
// //     for (double f = 1.0; f < 40.0; f++) {
// //         output += (pow(-1.0, f) / f) * sin(TAU * f * time) / f;
// //     }
// //     return output * (-2.0 / M_PI);
// // }
// double generateSaw(int frequency, double time)
// {
//     return (2.0 / M_PI) * frequency * M_PI * fmod(time, 1.0 / frequency) - (M_PI / 2.0);
// }

// double getRandNoise(double time)
// {
//     if (time > 0.2) return 0.0;
//     double env = (0 - 1) / 0.2 * time + 1.0;
//     double n = rand() % 2;
//     return env * n;
// }
