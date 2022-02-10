#ifndef EnvelopeH
#define EnvelopeH

class Envelope
{
public:
    struct Settings {
        double attack;
        double decay;
        double sustain;
        double release;

        double peakAmp;
        double sustainAmp;
    };

    Envelope(Settings *settings);

    double getAmplitude(double time);
    double getDuration();

private:
    double mDuration;
    double mAttack;
    double mDecay;
    double mSustain;
    double mRelease;

    const double mStartAmp = 0.0;
    double mPeakAmp;
    double mSustainAmp;
    const double mEndAmp = 0.0;
};

#endif
