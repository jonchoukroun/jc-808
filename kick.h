#ifndef KICK_H
#define KICK_H

#include "instrument.h"

class Kick : public Instrument
{
public:
    Kick(double amp = 0.8, double decay = 0.2);

    std::string getName() override;

private:
    const std::string m_defaultName = "Kick";
    const int m_defaultFreq = 247;
};

#endif
