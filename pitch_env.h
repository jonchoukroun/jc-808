#ifndef PITCH_ENV_H
#define PITCH_ENV_H

#include "envelope.h"

class PitchEnv : public Envelope
{
public:
    struct EnvSettings {
        double startPitch;
        double peakPitch;
        double releasePitch;

        double attack;
        double decay;
    };

    PitchEnv(EnvSettings &);
    ~PitchEnv() = default;
};

#endif
