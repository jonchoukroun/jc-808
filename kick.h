#ifndef KICK_H
#define KICK_H

#include "instrument.h"

class Kick : public Instrument
{
public:
    Kick();
    ~Kick() = default;

private:
    const std::string m_defaultName = "Kick";
    const int m_defaultFreq = 247;
};

#endif
