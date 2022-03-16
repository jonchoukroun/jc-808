#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include "snare.h"

Snare::Snare() : Instrument()
{
    m_name = m_defaultName;
    m_pitch = m_defaultPitch;
}

void Snare::setNoiseEnv(Envelope *env)
{
    m_noiseEnv = env;
}

void Snare::setBandPassFilter(Filter *filter)
{
    m_bandPass = filter;
}

double Snare::getSample()
{
    double pitch = m_pitchEnv == nullptr ? m_pitch : m_pitchEnv->getPitch(m_elapsed);
    double tone = sin(pitch * TAU * m_elapsed);
    double toneAmp = m_env->getAmplitude(m_elapsed);

    double noise = m_bandPass->filter((double)rand() / RAND_MAX);
    double noiseAmp = m_noiseEnv->getAmplitude(m_elapsed);
    return (tone * toneAmp) + (noise * noiseAmp);
}
