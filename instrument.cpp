#include <cmath>
#include "instrument.h"

Instrument::Instrument(int frequency, double duration)
{
    mFreq = frequency;
    mDuration = duration;
    mElapsed = 0.0;
    mTriggered = false;
}

Instrument::~Instrument() {}

void Instrument::trigger()
{
    mTriggered = true;
    mElapsed = 0.0;
}

bool Instrument::isTriggered()
{
    return mTriggered;
}

void Instrument::updateBy(double time)
{
    if (!mTriggered) return;

    mElapsed += time;
    if (mElapsed > mDuration) {
        mTriggered = false;
        mElapsed = 0.0;
    }
}

double Instrument::getSample()
{
    double env = -1 / mDuration * mElapsed + 1.0;
    double amp = sin(mFreq * TAU * mElapsed);
    return env * amp;
}
