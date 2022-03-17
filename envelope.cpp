#include <iostream>
#include "envelope.h"

double Envelope::getDuration()
{
    return m_duration;
}

void Envelope::setAttack(double attack)
{
    m_attack = attack;
}

void Envelope::setDecay(double decay)
{
    m_decay = decay;
}

void Envelope::setStart(double start)
{
    m_start = start;
}

void Envelope::setPeak(double peak)
{
    m_peak = peak;
}

void Envelope::setRelease(double release)
{
    m_release = release;
}

double Envelope::getEnvValue(double time)
{
    if (time > m_duration) return m_release;

    if (time <= m_attack) {
        return attackRamp(time);
    } else if (time <= (m_attack + m_decay)) {
        return decayRamp(time);
    } else {
        std::cout << "ERROR: Invalid time for envelope" << std::endl;
        return m_release;
    }
}

double Envelope::attackRamp(double time)
{
    return (m_peak - m_start) / m_attack * time + m_start;
}

double Envelope::decayRamp(double time)
{
    return (m_release - m_peak) / m_decay * (time - m_attack) + m_peak;
}
