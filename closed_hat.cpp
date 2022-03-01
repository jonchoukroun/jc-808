#include <iostream>
#include "closed_hat.h"

using std::cout;
using std::endl;

ClosedHat::ClosedHat() : Instrument(mBaseFreq, { 0.5, .02, 0.3 })
{
    mHarmonics[0] = mBaseFreq * 2.0;
    mHarmonics[1] = mBaseFreq * 3.0;
    mHarmonics[2] = mBaseFreq * 4.16;
    mHarmonics[3] = mBaseFreq * 5.43;
    mHarmonics[4] = mBaseFreq * 6.79;
    mHarmonics[5] = mBaseFreq * 8.21;

    mBandPass = new Filter(BANDPASS);
    mBandPass->setFilter(10000.0, 5.0);
    mHighPass = new Filter(HIGHPASS);
    mHighPass->setFilter(7000.0, 1.0);
}

double ClosedHat::getSample()
{
    static const int mFreq = 40;

    double amp = 0.0;
    for (auto f : mHarmonics) {
        double value = sin(f * TAU * mElapsed) > 0 ? 1.0 : 0.0;
        amp += value;
    }
    amp /= mHarmonics.size();
    double firstStep = mBandPass->filter(amp);
    double secondStep = mHighPass->filter(firstStep);
    return secondStep * mEnv.getAmplitude(mElapsed);
}

std::string ClosedHat::getName()
{
    return mName;
}
