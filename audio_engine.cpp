#include <iostream>
#include "audio_engine.h"

using std::cout;
using std::endl;

const double GAIN = 30000.0;

AudioEngine::AudioEngine(Sequencer *seq)
{
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = mSampleRate;
    desiredSpec.format = AUDIO_S16;
    desiredSpec.channels = 1;
    desiredSpec.samples = mSampleSize;
    desiredSpec.callback = &audioCallback;
    desiredSpec.userdata = this;

    mDeviceId = SDL_OpenAudioDevice(
        NULL,
        SDL_FALSE,
        &desiredSpec,
        &mReceivedSpec,
        0
    );
    if (mDeviceId == 0) {
        cout << "Failed to open audio device! Error: " << SDL_GetError() << endl;
    }

    mPlaying = false;

    mSeq = seq;
}

AudioEngine::~AudioEngine()
{
    delete [] mSeq;
    mSeq = nullptr;
    SDL_CloseAudioDevice(mDeviceId);
}

void AudioEngine::start()
{
    if (mSeq == nullptr) return;

    mSeq->start();
    mPlaying = true;
    SDL_PauseAudioDevice(mDeviceId, SDL_FALSE);
}

void AudioEngine::stop()
{
    mSeq->stop();
    mPlaying = false;
    SDL_PauseAudioDevice(mDeviceId, SDL_TRUE);

}

bool AudioEngine::isPlaying()
{
    return mPlaying;
}

SDL_AudioDeviceID AudioEngine::getAudioDevice()
{
    return mDeviceId;
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

        vector<Instrument *> notes = mSeq->getActiveSamples();
        for (auto n : notes) {
            if (n->isPlaying()) {
                output += n->getSample();
            }
        }
        out[i] = GAIN * output;

        mSeq->updateBy(mTimeStep);
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
