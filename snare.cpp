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
    AmpEnv::AmpEnvSettings toneAmpEnvSettings = {
        .peakAmp = 0.1,
        .attack = 0.01,
        .decay = 0.25,
    };
    AmpEnv *toneEnv = new AmpEnv(toneAmpEnvSettings);
    setAmpEnv(toneEnv);

    PitchEnv::EnvSettings pitchEnvSettings = {
        .startPitch = (double)getPitch(),
        .peakPitch = getPitch() + SEMITONE_HZ * 24.0,
        .releasePitch = (double)getPitch(),
        .decay = 0.04,
    };
    PitchEnv *pitchEnv = new PitchEnv(pitchEnvSettings);
    setPitchEnv(pitchEnv);

    AmpEnv::AmpEnvSettings noiseAmpEnvSettings = {
        .peakAmp = 0.6,
        .decay = 0.25,
    };
    AmpEnv *noiseEnv = new AmpEnv(noiseAmpEnvSettings);
    setNoiseEnv(noiseEnv);

    m_duration = std::max(
        (toneAmpEnvSettings.attack + toneAmpEnvSettings.decay),
        (noiseAmpEnvSettings.attack + noiseAmpEnvSettings.decay)
    );

    Filter *bandPass = new Filter(BANDPASS);
    bandPass->setFilter(2000.0, 2.0);
    setBandPassFilter(bandPass);

    // FIXME: adding this filter results in no audio
    // Filter *highPass = new Filter(HIGHPASS);
    // highPass->setFilter(200, 2.0),
    // setHighPassFilter(highPass);
}

void Snare::setSnappy(double snappy)
{
    m_noiseEnv->setPeak(snappy);
}

void Snare::setNoiseEnv(AmpEnv *env)
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
    double pitch = m_pitchEnv == nullptr ? m_pitch : m_pitchEnv->getEnvValue(m_elapsed);
    double tone = sin(pitch * TAU * m_elapsed);
    double toneAmp = m_ampEnv->getEnvValue(m_elapsed);

    double noise = m_bandPass->filter((double)rand() / RAND_MAX);
    double noiseAmp = m_noiseEnv->getEnvValue(m_elapsed);
    return (tone * toneAmp) + (noise * noiseAmp);
}
