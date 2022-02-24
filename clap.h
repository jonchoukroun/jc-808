#ifndef CLAP_H
#define CLAP_H

#include "filter.h"
#include "instrument.h"

class Clap : public Instrument
{
public:
    Clap(Envelope env = {
        .frequency = 200,
        .volume = 0.8,
        .attack = 0.01,
        .release = 0.25
    });

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
