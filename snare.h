#ifndef SNARE_H
#define SNARE_H

#include "instrument.h"

class Snare : public Instrument
{
public:
    Snare(int frequency = 160, double duration = 0.4);

    double getSample() override;

    std::string getName() override;

private:
    const double mToneDecay = 0.25;

    const std::string mName = "Snare";
};

#endif

