#include <iostream>
#include <cmath>
#include "clap.h"

Clap::Clap(Envelope env) : Instrument(env)
{
    mElapsed = 0.0;
    mTriggered = false;

    mHighPass = new Filter(HIGHPASS);
    mHighPass->setFilter(800.0, 5.0);
    mBandPass = new Filter(BANDPASS);
    mBandPass->setFilter(1500.0, 1.5);

    srand(time(0));
}

double Clap::getSample()
{
    double sample = 0.0;
    if (mElapsed > mDuration) return sample;

    double amp = 0.5;
    double noise = amp * (double)rand() / RAND_MAX;
    if (mElapsed < mInterval * 2) {
        for (double n = 1.0; n <= 40; n++) {
            sample += sin(n * TAU * 100 * mElapsed) / n;
        }
        sample *= noise * (2.0 / M_PI);
    } else {
        double decay = amp * pow(mDuration * 0.001, mElapsed);
        sample = noise * decay;
    }

    return mHighPass->filter(mBandPass->filter(sample));
}


std::string Clap::getName()
{
    return mName;
}
