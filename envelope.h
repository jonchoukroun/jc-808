#ifndef EnvelopeH
#define EnvelopeH

class Envelope
{
public:
    Envelope(double amp, double attack, double decay, bool isExp = false);

    double getAmplitude(double time);
    double getDuration();

private:
    static constexpr double mStartAmp = 0.0;
    static constexpr double mEndAmp = 0.0;
    double mPeakAmp;

    double mAttack;
    double mDecay;
    double mDuration;

    bool mIsExp;

    double attackRamp(double time);
    double decayRamp(double time);
    double releaseRamp(double time);
};

#endif
