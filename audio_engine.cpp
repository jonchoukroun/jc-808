#include <iostream>
#include "audio_engine.h"

using std::cout;
using std::endl;

const double gTempo = 80.0; // BPM = 2 beats per second
const double gTempoStep = 60000.0 / (gTempo * 2.0);
const double gTempoStepMs = gTempoStep / 1000.0;

const double GAIN = 30000.0;

AudioEngine::AudioEngine(Sequencer *seq)
{
    mSeq = seq;
    cout << "Seq len " << seq->size() << endl;
    mSeqPos = 0;
    mPlaying = false;

    mTime = 0.0;

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
}

AudioEngine::~AudioEngine()
{
    delete [] mSeq;
    mSeq = nullptr;
    SDL_CloseAudioDevice(mDeviceId);
}

void AudioEngine::start()
{
    mPlaying = true;
    mSeqPos = 0;
    mTime = 0.0;
    SDL_PauseAudioDevice(mDeviceId, SDL_FALSE);
}

void AudioEngine::stop()
{
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
        if (mSeqPos >= 8) mSeqPos = 0;

        Instrument *inst = (*mSeq)[mSeqPos];
        if (inst != nullptr && !inst->isTriggered()) {
            inst->trigger();
            mActiveSamples.push_back(inst);
        }

        double output = 0.0;
        for (auto sample : mActiveSamples) {
            if (sample->isPlaying()) {
                output += sample->getSample();
                sample->updateBy(mTimeStep);
            }
        }
        out[i] = GAIN * output;

        for (auto it = mActiveSamples.begin(); it != mActiveSamples.end(); it++) {
            Instrument *s = *it;
            if (!s->isPlaying()) {
                s->release();
                mActiveSamples.erase(it);
                it--;
            }
        }

        mTime += mTimeStep;
        if (mTime > gTempoStepMs) {
            mTime = 0.0;
            mSeqPos++;
        }
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
