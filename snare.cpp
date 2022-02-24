#include <algorithm>
#include <cmath>
#include <ctime>
#include "snare.h"

Snare::Snare(Envelope env, double snappy)
: Instrument(env)
{
    mSnappy = snappy;
    mElapsed = 0.0;
    mTriggered = false;

    mHighPass = new Filter(HIGHPASS);
    mHighPass->setFilter(600, 5.0);
    mBandPass = new Filter(BANDPASS);
    mBandPass->setFilter(2000, 3.0);

    srand(time(0));
}

double Snare::getSample()
{
    double tone = sin(TAU * mEnv.frequency * mElapsed);
    double noise = (double)rand() / RAND_MAX;
    if (mElapsed <= mEnv.attack) {
        tone *= mEnv.volume / mEnv.attack * mElapsed;
        noise *= mSnappy / mEnv.attack * mElapsed;
    } else if (mElapsed <= mEnv.attack + mEnv.release) {
        tone *= -mEnv.volume / mEnv.release * (mElapsed - mEnv.attack) + mEnv.volume;
        noise *= -mSnappy / mEnv.release * (mElapsed - mEnv.attack) + mSnappy;
    } else {
        tone *= 0.0;
        noise *= 0.0;
    }

    double blend = 0.5 * (tone  + noise);
    double filtered = mBandPass->filter(blend);
    return mHighPass->filter(filtered);
}

std::string Snare::getName()
{
    return mName;
}
