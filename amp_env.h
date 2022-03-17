#ifndef AMP_ENV_H
#define AMP_ENV_H

#include "envelope.h"

class AmpEnv : public Envelope
{
public:
    struct AmpEnvSettings {
        double startAmp;
        double peakAmp;
        double releaseAmp;

        double attack;
        double decay;
    };

    AmpEnv(AmpEnvSettings &);
    ~AmpEnv() = default;
};

#endif
