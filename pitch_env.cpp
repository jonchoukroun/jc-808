#include <iostream>
#include "pitch_env.h"

PitchEnv::PitchEnv(EnvSettings &settings)
: m_settings(settings)
, m_duration(m_settings.attack + m_settings.decay) {}

void PitchEnv::setStartPitch(double pitch)
{
    m_settings.startPitch = pitch;
}

void PitchEnv::setAttackPitch(double pitch)
{
    m_settings.attackPitch = pitch;
}

void PitchEnv::setReleasePitch(double pitch)
{
    m_settings.releasePitch = pitch;
}

void PitchEnv::setAttack(double attack)
{
    m_settings.attack = attack;
}

void PitchEnv::setDecay(double decay)
{
    m_settings.decay = decay;
}

double PitchEnv::getPitch(double time)
{
    if (time >= m_duration) return m_settings.releasePitch;

    if (time >= 0 && time < m_settings.attack) {
        return (m_settings.attackPitch - m_settings.startPitch) / m_settings.attack * time + m_settings.startPitch;
    } else if (time >= m_settings.attack && time < (m_settings.attack + m_settings.decay)) {
        return (m_settings.releasePitch - m_settings.attackPitch) / m_settings.decay * (time - m_settings.attack) + m_settings.attackPitch;
    } else {
        std::cout << "Invalid time" << std::endl;
        return m_settings.releasePitch;
    }
}
