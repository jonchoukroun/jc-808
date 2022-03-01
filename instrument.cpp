#include <cmath>
#include <iostream>
#include "instrument.h"

Instrument::Instrument(int freq, Envelope env)
: mFreq(freq), mEnv(env)
{
    mDuration = mEnv.getDuration();
    mElapsed = 0.0;
    mTriggered = false;
    mPlaying = false;
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
    return sin(mFreq * TAU * mElapsed) * mEnv.getAmplitude(mElapsed);
}

std::string Instrument::getName()
{
    return "-";
}
