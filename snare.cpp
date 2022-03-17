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

void Snare::setDefaults()
{
    Envelope::EnvSettings toneEnvSettings = {
        .peakAmp = 0.1,
        .attack = 0.01,
        .decay = 0.25,
    };
    Envelope *toneEnv = new Envelope(toneEnvSettings);
    setEnvelope(toneEnv);

    PitchEnv::EnvSettings pitchEnvSettings = {
        .startPitch = (double)getPitch(),
        .attackPitch = getPitch() + SEMITONE_HZ * 24.0,
        .releasePitch = (double)getPitch(),
        .decay = 0.04,
    };
    PitchEnv *pitchEnv = new PitchEnv(pitchEnvSettings);
    setPitchEnv(pitchEnv);

    Envelope::EnvSettings noiseEnvSettings = {
        .peakAmp = 0.6,
        .decay = 0.25,
    };
    Envelope *noiseEnv = new Envelope(noiseEnvSettings);
    setNoiseEnv(noiseEnv);

    m_duration = std::max(
        (toneEnvSettings.attack + toneEnvSettings.decay),
        (noiseEnvSettings.attack + noiseEnvSettings.decay)
    );

    Filter *bandPass = new Filter(BANDPASS);
    bandPass->setFilter(2000.0, 2.0);
    setBandPassFilter(bandPass);

    // Filter *highPass = new Filter(HIGHPASS);
    // highPass->setFilter(200, 2.0),
    // setHighPassFilter(highPass);
}

void Snare::setLevel(double level)
{
    m_env->setPeakAmp(level);
}

void Snare::setSnappy(double snappy)
{
    m_noiseEnv->setPeakAmp(snappy);
}

void Snare::setNoiseEnv(Envelope *env)
{
    m_noiseEnv = env;
}

void Snare::setBandPassFilter(Filter *filter)
{
    m_bandPass = filter;
}

void Snare::setHighPassFilter(Filter *filter)
{
    m_highPass = filter;
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
