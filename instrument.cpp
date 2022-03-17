#include <cmath>
#include <iostream>
#include "instrument.h"

using std::cout;
using std::endl;

int Instrument::getPitch()
{
    return m_pitch;
}

void Instrument::setPitch(int pitch)
{
    m_pitch = pitch;
}

void Instrument::setLevel(double level)
{
    m_ampEnv->setPeak(level);
}

void Instrument::setAmpEnv(AmpEnv *env)
{
    m_ampEnv = env;
    m_duration = env->getDuration();
}

void Instrument::setPitchEnv(PitchEnv *env)
{
    m_pitchEnv = env;
}

void Instrument::trigger()
{
    m_triggered = true;
    m_playing = true;
    m_elapsed = 0.0;
}

void Instrument::release()
{
    m_triggered = false;
}

bool Instrument::isTriggered()
{
    return m_triggered;
}

bool Instrument::isPlaying()
{
    return m_playing;
}

void Instrument::updateBy(double time)
{
    if (!m_triggered) return;

    m_elapsed += time;
    if (m_elapsed > m_duration) {
        m_playing = false;
        m_elapsed = 0.0;
    }
}

double Instrument::getSample()
{
    double value;
    if (m_pitchEnv == nullptr) {
        value = sin(m_pitch * TAU * m_elapsed);
    } else {
        double pitch = m_pitchEnv->getEnvValue(m_elapsed);
        value = sin(pitch * TAU * m_elapsed);
    }

    if (m_ampEnv != nullptr) {
        value *= m_ampEnv->getEnvValue(m_elapsed);
    }

    return value;
}

std::string Instrument::getName()
{
    return m_name;
}
