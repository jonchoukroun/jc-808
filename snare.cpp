#include <algorithm>
#include <cmath>
#include <ctime>
#include "snare.h"

Snare::Snare(double amp, double decay, double snappy)
: Instrument(mDefaultFreq, { amp, 0.001, decay }), mNoiseEnv({ snappy, 0.01, 0.4})
{
    mElapsed = 0.0;
    mTriggered = false;

    mHighPass = new Filter(HIGHPASS);
    mHighPass->setFilter(400, 5.0);
    mBandPass = new Filter(BANDPASS);
    mBandPass->setFilter(1000, 1.0);

    srand(time(0));
}

double Snare::getSample()
{
    double tone = sin(TAU * mFreq * mElapsed) * mEnv.getAmplitude(mElapsed);
    double filteredNoise = mBandPass->filter((double)rand() / RAND_MAX);
    filteredNoise *= mNoiseEnv.getAmplitude(mElapsed);

    double blend = 0.5 * (tone + filteredNoise);
    return mHighPass->filter(blend);
}

std::string Snare::getName()
{
    return mName;
}
