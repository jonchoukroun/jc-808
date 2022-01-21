#ifndef AudioEngineH
#define AudioEngineH

#include <SDL2/SDL.h>

class AudioEngine
{
public:
    AudioEngine(double (* generatorFn)(double time));
    ~AudioEngine();

    void play();
    void pause();

    SDL_AudioDeviceID getAudioDevice();

private:
    static const int mSampleRate = 44100;
    static const int mSampleSize = 512;
    static const int mChannels = 1;
    static const int mSampleSeconds = 1;

    double mTime;
    static constexpr double mTimeStep = 1.0 / (double)mSampleRate;

    SDL_AudioDeviceID mDeviceId = 0;
    SDL_AudioSpec mReceivedSpec;

    double (* mGeneratorFn)(double time);

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);
};

#endif
