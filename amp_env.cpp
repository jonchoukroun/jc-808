#include <iostream>
#include "amp_env.h"

AmpEnv::AmpEnv(AmpEnvSettings &settings)
: Envelope()
{
    m_attack = settings.attack;
    m_decay = settings.decay;
    m_duration = settings.attack + settings.decay;

    m_start = settings.startAmp;
    m_peak = settings.peakAmp;
    m_release = settings.releaseAmp;
}
