#include <iostream>
#include "envelope.h"

using std::cout;
using std::endl;

Envelope::Envelope(Settings *settings)
{
    mAttackDuration = settings->attackDuration;
    mDecayDuration = settings->decayDuration;
    mReleaseDuration = settings->releaseDuration;
    mSustainDuration = settings->sustainDuration;
    mSustainAmplitude = settings->sustainAmplitude;

    mTriggerAmplitude = 1.0;
}

double Envelope::getAmplitude(double elapsed)
{
    if (elapsed < 0.001) return 0.0;

    double amplitude = 0.0;

    if (elapsed <= mAttackDuration) {
        amplitude = mTriggerAmplitude / mAttackDuration * elapsed;
    }

    if (elapsed > mAttackDuration && elapsed <= mDecayDuration) {
        amplitude =
            (mSustainAmplitude - mTriggerAmplitude) /
            (mDecayDuration) * (elapsed - mAttackDuration);
    }

    if (
        elapsed > (mDecayDuration + mAttackDuration) &&
        elapsed <= mSustainDuration
    ) {
        amplitude = mSustainAmplitude;
    }

    if (elapsed > mSustainDuration) {
        amplitude =
            (0 - mSustainAmplitude) / mReleaseDuration * elapsed + mSustainAmplitude;
    }

    if (amplitude <= 0.0001) amplitude = 0.0;

    return amplitude;
}

double Envelope::getDuration()
{
    return mAttackDuration + mDecayDuration + mSustainDuration + mReleaseDuration;
}
