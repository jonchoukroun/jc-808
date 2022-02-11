#include <cmath>
#include <iostream>
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
    mPlaying = true;
    mElapsed = 0.0;
}

void Instrument::release()
{
    mTriggered = false;
}

bool Instrument::isTriggered()
{
    return mTriggered;
}

bool Instrument::isPlaying()
{
    return mPlaying;
}

void Instrument::updateBy(double time)
{
    if (!mTriggered) return;

    mElapsed += time;
    if (mElapsed > mDuration) {
        mPlaying = false;
        mElapsed = 0.0;
    }
}

double Instrument::getSample()
{
    double env = -1 / mDuration * mElapsed + 1.0;
    double amp = sin(mFreq * TAU * mElapsed);
    return env * amp;
}

std::string Instrument::getName()
{
    return "";
}
