#ifndef SNARE_H
#define SNARE_H

#include "filter.h"
#include "instrument.h"

class Snare : public Instrument
{
public:
    Snare();
    ~Snare() = default;

    void setDefaults() override;

    void setLevel(double level);
    void setSnappy(double snappy);

    void setNoiseEnv(Envelope *);

    void setBandPassFilter(Filter *);
    void setHighPassFilter(Filter *);

    double getSample() override;

private:
    Envelope *m_noiseEnv = nullptr;

    const std::string m_defaultName = "Snare";
    const int m_defaultPitch = 160;

    Filter *m_bandPass;
    Filter *m_highPass;

};

#endif

