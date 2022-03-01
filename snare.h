#ifndef SNARE_H
#define SNARE_H

#include "filter.h"
#include "instrument.h"

class Snare : public Instrument
{
public:
    Snare(double amp = 0.8, double decay = 0.25, double snappy = 0.1);

    double getSample() override;

    std::string getName() override;

private:
    static const int mDefaultFreq = 160;
    Envelope mNoiseEnv;

    Filter *mHighPass;
    Filter *mBandPass;

    const std::string mName = "Snare";
};

#endif

