#ifndef KICK_H
#define KICK_H

#include "instrument.h"

class Kick : public Instrument
{
public:
    Kick(double amp = 0.8, double decay = 0.2);

    std::string getName() override;

private:
    const std::string mName = "Kick";

    static const int mDefaultFreq = 47;
};

#endif
