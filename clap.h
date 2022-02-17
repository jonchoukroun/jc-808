#ifndef CLAP_H
#define CLAP_H

#include "filter.h"
#include "instrument.h"

class Clap : public Instrument
{
public:
    Clap(int frequency = 180, double duration = 0.2);

    double getSample() override;

    std::string getName() override;

private:
    const std::string mName = "Clap";

    // 10 ms between claps
    static constexpr double mInterval = 0.01;

    double mSingleDuration;

    Filter *mHighPass;
    Filter *mBandPass;
};

#endif
