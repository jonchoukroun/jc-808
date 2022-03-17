#include <iostream>
#include <cmath>
#include "clap.h"

Clap::Clap() : Instrument()
{
    m_name = m_defaultName;
    m_pitch = m_defaultPitch;

    srand(time(0));
}

void Clap::setDefaults()
{
    Envelope::EnvSettings envSettings = {
        .peakAmp = 0.8,
        .decay = 0.3
    };
    Envelope *ampEnv = new Envelope(envSettings);
    setEnvelope(ampEnv);

    Filter *bandPass = new Filter(BANDPASS);
    bandPass->setFilter(1500.0, 1.5);
    setBandPassFilter(bandPass);

    Filter *highPass = new Filter(HIGHPASS);
    highPass->setFilter(800.0, 5.0);
    setHighPassFilter(highPass);
}

void Clap::setBandPassFilter(Filter *filter)
{
    m_bandPass = filter;
}

void Clap::setHighPassFilter(Filter *filter)
{
    m_highPass = filter;
}

double Clap::getSample()
{
    double sample = 0.0;
    if (m_elapsed > m_duration) return sample;

    double amp = 0.5;
    double noise = amp * (double)rand() / RAND_MAX;
    if (m_elapsed < m_interval * 2) {
        for (double n = 1.0; n <= 40; n++) {
            sample += sin(n * TAU * 100 * m_elapsed) / n;
        }
        sample *= noise * (2.0 / M_PI);
    } else {
        // TODO: replace with exponential Envelope decay
        double decay = amp * pow(m_duration * 0.001, m_elapsed);
        sample = noise * decay;
    }

    return m_highPass->filter(m_bandPass->filter(sample));
}
