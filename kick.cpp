#include <cmath>
#include "kick.h"

Kick::Kick(Envelope env) : Instrument(env)
{
    mElapsed = 0.0;
    mTriggered = false;
}

std::string Kick::getName()
{
    return mName;
}
