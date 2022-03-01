#include <cmath>
#include "kick.h"

Kick::Kick(double amp, double decay)
: Instrument(mDefaultFreq, { amp, 0.002, decay })
{
    mElapsed = 0.0;
    mTriggered = false;
}

std::string Kick::getName()
{
    return mName;
}
