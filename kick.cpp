#include <cmath>
#include "kick.h"

Kick::Kick(int frequency, double duration)
: Instrument(frequency, duration)
{
    mFreq = frequency;
    mDuration = duration;
    mElapsed = 0.0;
    mTriggered = false;
}
