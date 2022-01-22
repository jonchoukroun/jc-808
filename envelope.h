#ifndef EnvelopeH
#define EnvelopeH

class Envelope
{
public:
    struct Settings {
        double attackDuration;
        double decayDuration;
        double releaseDuration;
        double sustainDuration;
        double sustainAmplitude;
    };

    Envelope(Settings *settings);

    double getAmplitude(double time);
    double getDuration();

private:
    double mAttackDuration;
    double mDecayDuration;
    double mReleaseDuration;
    double mSustainDuration;

    double mSustainAmplitude;
    double mTriggerAmplitude;
};

#endif
