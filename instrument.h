#ifndef INSTRUMENT_H
#define INSTRUMENT_H

class Instrument
{
public:
    Instrument(int frequency, double duration);
    ~Instrument();

    void trigger();
    bool isTriggered();

    void updateBy(double time);

    virtual double getSample();

    static constexpr double TAU = M_PI * 2.0;

protected:
    int mFreq;
    double mDuration;
    double mElapsed;
    bool mTriggered;
};

#endif
