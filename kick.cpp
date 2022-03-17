#include <cmath>
#include <iostream>
#include "kick.h"

Kick::Kick() : Instrument()
{
    m_name = m_defaultName;
    m_pitch = m_defaultPitch;
}

void Kick::setDefaults()
{
    AmpEnv::AmpEnvSettings envSettings = {
        .peakAmp = 0.8,
        .decay = 0.25,
    };
    AmpEnv *ampEnv = new AmpEnv(envSettings);
    setAmpEnv(ampEnv);

    PitchEnv::EnvSettings pitchEnvSettings = {
        .startPitch = (double)getPitch(),
        .peakPitch = getPitch() + SEMITONE_HZ * 48.0,
        .releasePitch = (double)getPitch(),
        .decay = 0.02,
    };
    PitchEnv *pitchEnv = new PitchEnv(pitchEnvSettings);
    setPitchEnv(pitchEnv);
}
