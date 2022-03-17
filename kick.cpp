#include <cmath>
#include "kick.h"

Kick::Kick() : Instrument()
{
    m_name = m_defaultName;
    m_pitch = m_defaultPitch;
}

void Kick::setDefaults()
{
    Envelope::EnvSettings envSettings = {
        .peakAmp = 0.8,
        .decay = 0.25,
    };
    Envelope *ampEnv = new Envelope(envSettings);
    setEnvelope(ampEnv);

    PitchEnv::EnvSettings pitchEnvSettings = {
        .startPitch = (double)getPitch(),
        .attackPitch = getPitch() + SEMITONE_HZ * 24.0,
        .releasePitch = (double)getPitch(),
        .decay = 0.02,
    };
    PitchEnv *pitchEnv = new PitchEnv(pitchEnvSettings);
    setPitchEnv(pitchEnv);
}
