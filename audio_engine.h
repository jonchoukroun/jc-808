#ifndef AudioEngineH
#define AudioEngineH

#include <SDL2/SDL.h>

class AudioEngine
{
public:
    enum WaveForm {
        SINE,
        SQUARE,
        TRIANGLE,
        SAW
    };

    AudioEngine(int frequency, int volume, WaveForm waveform);
    ~AudioEngine();

    void play();
    void pause();

private:
    static const int mSampleRate = 44100;
    static const int mSampleSize = 512;
    static const int mChannels = 1;
    static const int mSampleSeconds = 1;

    int mFrequency;
    int mVolume;

    double mTime;
    static constexpr double mTimeStep = 1.0 / (double)mSampleRate;

    SDL_AudioDeviceID mDeviceId = 0;
    SDL_AudioSpec mReceivedSpec;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);

    double (* generateWave)(int frequency, double time);

    static double generateSine(int frequency, double time);
    static double generateSquare(int frequency, double time);
    static double generateTriangle(int frequency, double time);
    static double generateSaw(int frequency, double time);
};

#endif
