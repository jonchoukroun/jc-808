#include <iostream>
#include "envelope.h"

using std::cout;
using std::endl;

Envelope::Envelope(double amp, double attack, double decay, bool isExp)
: mPeakAmp(amp), mAttack(attack), mDecay(decay), mIsExp(isExp) {
    mDuration = mAttack + mDecay;
}

double Envelope::getAmplitude(double time)
{
    if (time > mDuration) return 0.0;

    if (time <= mAttack) {
        return attackRamp(time);
    } else if (time <= mAttack + mDecay) {
        return decayRamp(time);
    } else {
        std::cout << "Invalid time " << time << " for envelope."  << std::endl;
        return 0.0;
    }
}

double Envelope::getDuration()
{
    return mDuration;
}

double Envelope::attackRamp(double time)
{
    return (mPeakAmp - mStartAmp) / mAttack * time;
}

double Envelope::decayRamp(double time)
{
    return (mEndAmp - mPeakAmp) / mDecay * (time - mAttack) + mPeakAmp;
}
