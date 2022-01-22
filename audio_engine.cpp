#include <iostream>
#include "audio_engine.h"

#define TAU M_PI * 2

using std::cout;
using std::endl;

const double GAIN = 30000.0;

AudioEngine::AudioEngine(Envelope *envelope, double (* generatorFn)(double time))
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

    mEnvelope = envelope;
    mGeneratorFn = generatorFn;

    mDuration = envelope->getDuration();

    mTime = 0.0;
}

AudioEngine::~AudioEngine()
{
    SDL_CloseAudioDevice(mDeviceId);
}

void AudioEngine::play()
{
    SDL_PauseAudioDevice(mDeviceId, SDL_FALSE);
}

void AudioEngine::pause()
{
    mTime = 0.0;
    SDL_PauseAudioDevice(mDeviceId, SDL_TRUE);

}

SDL_AudioDeviceID AudioEngine::getAudioDevice()
{
    return mDeviceId;
}

void AudioEngine::audioCallback(void *userdata, Uint8 *stream, int len)
{
    const auto engine = reinterpret_cast<AudioEngine *>(userdata);
    engine->fillBuffer(stream, len);
    if (engine->mTime >= engine->mDuration) {
        engine->pause();
    }
}

void AudioEngine::fillBuffer(const Uint8* const stream, int len)
{
    short *out = (short *)stream;
    for (int i = 0; i < (len / sizeof(short)); i++) {
        double amplitude = mEnvelope->getAmplitude(mTime);
        double value = mGeneratorFn(mTime);
        out[i] = GAIN * amplitude * value;
        mTime += mTimeStep;
    }
}

double generateTriangle(int frequency, double time)
{
    return asin(sin(frequency * TAU * time)) * (2.0 / M_PI);
}

double generateSquare(int frequency, double time)
{
    return sin(frequency * TAU * time) > 0 ? 1.0 : -1.0;
}

// double generateSaw(int frequency, double time)
// {
//     double output = 0.0;
//     for (double f = 1.0; f < 40.0; f++) {
//         output += (pow(-1.0, f) / f) * sin(TAU * f * time) / f;
//     }
//     return output * (-2.0 / M_PI);
// }
double generateSaw(int frequency, double time)
{
    return (2.0 / M_PI) * frequency * M_PI * fmod(time, 1.0 / frequency) - (M_PI / 2.0);
}
