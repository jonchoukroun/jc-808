#ifndef SNARE_H
#define SNARE_H

#include "filter.h"
#include "instrument.h"

class Snare : public Instrument
{
public:
    Snare(
        Envelope env = {
            .frequency = 180,
            .volume = 0.8,
            .attack = 0.001,
            .release = 0.25,
        },
        double snappy = 0.1
    );

    double getSample() override;

    std::string getName() override;

private:
    double mSnappy;

    Filter *mHighPass;
    Filter *mBandPass;

    const std::string mName = "Snare";
};

#endif

