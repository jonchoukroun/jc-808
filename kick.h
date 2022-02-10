#ifndef KICK_H
#define KICK_H

#include "instrument.h"

class Kick : public Instrument
{
public:
    Kick(int frequency = 47, double duration = 0.35);
};

#endif
