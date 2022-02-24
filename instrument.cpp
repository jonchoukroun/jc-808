#include <cmath>
#include <iostream>
#include "instrument.h"

Instrument::Instrument(Envelope env)
{
    mEnv = env;
    mDuration = env.attack + env.release;
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

double Instrument::getEnv()
{
    if (mElapsed <= mEnv.attack) {
        return mEnv.volume / mEnv.attack * mElapsed;
    } else if (mElapsed < mEnv.attack + mEnv.release) {
        return -mEnv.volume / mEnv.release * (mElapsed - mEnv.attack) + mEnv.volume;
    } else {
        return 0.0;
    }
}

double Instrument::getSample()
{
    double amp = sin(mEnv.frequency * TAU * mElapsed);
    double env = getEnv();
    return amp * env;
}

std::string Instrument::getName()
{
    return "-";
}
