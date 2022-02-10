#include <iostream>
#include "envelope.h"

using std::cout;
using std::endl;

Envelope::Envelope(Settings *settings)
{
    mAttack = settings->attack;
    mDecay = settings->decay;
    mSustain = settings->sustain;
    mRelease = settings->release;
    mDuration = mAttack + mDecay + mSustain + mRelease;

    mSustainAmp = settings->sustainAmp;
}

double Envelope::getAmplitude(double time)
{
    if (time > mDuration) return 0.0;

    double amp = 0.0;
    if (time <= mAttack) {
        amp = (mPeakAmp / mAttack) * time;
    } else if (time > mAttack && time <= mAttack + mDecay) {
        amp = ((mSustainAmp - mPeakAmp) / mDecay) * (time - mAttack) + mPeakAmp;
    } else if (time > mAttack + mDecay && time <= mDuration - mRelease) {
        amp = mSustainAmp;
    } else {
        amp = -(mSustainAmp / mRelease) * (time - (mAttack + mDecay + mSustain)) + mSustainAmp;
    }

    if (amp <= 0.001) amp = 0.0;

    return amp;
}

double Envelope::getDuration()
{
    return mDuration;
}
