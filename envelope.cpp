#include <iostream>
#include "envelope.h"

using std::cout;
using std::endl;

Envelope::Envelope(EnvSettings &settings)
: m_settings(settings)
, m_duration(settings.attack + settings.decay) {};

void Envelope::setStartAmp(double amp)
{
    m_settings.startAmp = amp;
}

void Envelope::setPeakAmp(double amp)
{
    m_settings.peakAmp = amp;
}

void Envelope::setEndAmp(double amp)
{
    m_settings.endAmp = amp;
}

void Envelope::setAttack(double attack)
{
    m_settings.attack = attack;
}

void Envelope::setDecay(double decay)
{
    m_settings.decay = decay;
}

double Envelope::getAmplitude(double time)
{
    if (time > m_duration) return 0.0;

    if (time <= m_settings.attack) {
        return attackRamp(time);
    } else if (time <= m_settings.attack + m_settings.decay) {
        return decayRamp(time);
    } else {
        std::cout << "Invalid time " << time << " for envelope."  << std::endl;
        return 0.0;
    }
}

double Envelope::getDuration()
{
    return m_duration;
}

double Envelope::attackRamp(double time)
{
    return (m_settings.peakAmp - m_settings.startAmp) / m_settings.attack * time;
}

double Envelope::decayRamp(double time)
{
    return (m_settings.endAmp - m_settings.peakAmp) / m_settings.decay * (time - m_settings.attack) + m_settings.peakAmp;
}
