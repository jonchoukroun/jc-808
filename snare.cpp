#include <algorithm>
#include <cmath>
#include <ctime>
#include "snare.h"

Snare::Snare(int frequency, double duration)
: Instrument(frequency, duration)
{
    mFreq = frequency;
    mDuration = std::max(duration, mToneDecay);
    mElapsed = 0.0;
    mTriggered = false;

    srand(time(0));
}

double Snare::getSample()
{
    double tone = 0.0;
    if (mElapsed <= mToneDecay) {
        double toneEnv = (0 - 1) / mToneDecay * mElapsed + 1.0;
        tone = toneEnv * sin(mFreq * TAU * mElapsed);
    }
    double noiseEnv = -1 / mDuration * mElapsed + 1.0;
    double noise = noiseEnv * (double)rand() / RAND_MAX;
    return 0.25 * tone +  0.4 * noise;
}