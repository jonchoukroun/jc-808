#ifndef CLAP_H
#define CLAP_H

#include "filter.h"
#include "instrument.h"

class Clap : public Instrument
{
public:
    Clap(double decay = 0.25);

    double getSample() override;

    std::string getName() override;

private:
    const std::string mName = "Clap";

    static const int mDefaultFreq = 200;

    // 10 ms between claps
    static constexpr double mInterval = 0.01;

    Filter *mHighPass;
    Filter *mBandPass;
};

#endif
