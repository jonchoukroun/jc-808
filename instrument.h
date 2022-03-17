#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <cmath>
#include <optional>
#include <string>
#include "envelope.h"
#include "pitch_env.h"

#define SEMITONE_HZ 1.06

class Instrument
{
public:
    Instrument() = default;
    ~Instrument() = default;

    int getPitch();
    void setPitch(int pitch);

    virtual void setDefaults() = 0;

    void setEnvelope(Envelope *);

    void setPitchEnv(PitchEnv *);

    void trigger();
    void release();
    bool isTriggered();
    bool isPlaying();

    void updateBy(double time);

    virtual double getSample();

    std::string getName();

    static constexpr double TAU = M_PI * 2.0;

protected:
    Envelope *m_env = nullptr;
    PitchEnv *m_pitchEnv = nullptr;

    double m_duration;
    double m_elapsed;

    int m_pitch;

    bool m_triggered;
    bool m_playing;

    std::string m_name;
};

#endif
