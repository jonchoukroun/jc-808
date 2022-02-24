#ifndef KICK_H
#define KICK_H

#include "instrument.h"

class Kick : public Instrument
{
public:
    Kick(Envelope env = {
        .frequency = 47,
        .volume = 0.8,
        .attack = 0.002,
        .release = 0.25,
    });

    std::string getName() override;

private:
    const std::string mName = "Kick";
};

#endif
