#include <iostream>
#include "closed_hat.h"

using std::cout;
using std::endl;

ClosedHat::ClosedHat(int frequency)
: Instrument(frequency, 0.27)
{
    mFreq = frequency;
    mHarmonics[0] = mFreq * 2.0;
    mHarmonics[1] = mFreq * 3.0;
    mHarmonics[2] = mFreq * 4.16;
    mHarmonics[3] = mFreq * 5.43;
    mHarmonics[4] = mFreq * 6.79;
    mHarmonics[5] = mFreq * 8.21;

    mBandPass = new Filter(BANDPASS);
    mBandPass->setFilter(10000.0, 5.0);
    mHighPass = new Filter(HIGHPASS);
    mHighPass->setFilter(7000.0, 1.0);
}

double ClosedHat::getSample()
{
    double amp = 0.0;
    for (auto f : mHarmonics) {
        double value = sin(f * TAU * mElapsed) > 0 ? 1.0 : 0.0;
        amp += value;
    }
    amp /= mHarmonics.size();
    double firstStep = mBandPass->filter(amp);
    double secondStep = mHighPass->filter(firstStep);
    return secondStep * getEnv();
}

std::string ClosedHat::getName()
{
    return mName;
}
