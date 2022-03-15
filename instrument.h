#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <cmath>
#include <optional>
#include <string>
#include "envelope.h"

class Instrument
{
public:
    Instrument() = default;
    ~Instrument() = default;

    void setEnvelope(Envelope *);

    std::string getName();

    void trigger();
    void release();
    bool isTriggered();
    bool isPlaying();

    void updateBy(double time);

    virtual double getSample();

    static constexpr double TAU = M_PI * 2.0;

protected:
    int m_freq;
    Envelope *m_env;

    double m_duration;
    double m_elapsed;

    bool m_triggered;
    bool m_playing;

    std::string m_name;
};

#endif
