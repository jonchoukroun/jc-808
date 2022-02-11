#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>

class Instrument
{
public:
    Instrument(int frequency, double duration);
    ~Instrument();

    virtual std::string getName();

    void trigger();
    void release();
    bool isTriggered();
    bool isPlaying();

    void updateBy(double time);

    virtual double getSample();

    static constexpr double TAU = M_PI * 2.0;

protected:
    int mFreq;
    double mDuration;
    double mElapsed;

    bool mTriggered;
    bool mPlaying;
};

#endif
