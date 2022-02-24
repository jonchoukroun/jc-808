#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <cmath>
#include <optional>
#include <string>

class Instrument
{
public:
    struct Envelope {
        int frequency;
        double volume;
        double attack;
        double release;
    };

    Instrument(Envelope env);
    ~Instrument();

    virtual std::string getName();

    void trigger();
    void release();
    bool isTriggered();
    bool isPlaying();

    void updateBy(double time);

    double getEnv();

    virtual double getSample();

    static constexpr double TAU = M_PI * 2.0;

protected:
    Envelope mEnv;
    double mDuration;
    double mElapsed;

    bool mTriggered;
    bool mPlaying;
};

#endif
