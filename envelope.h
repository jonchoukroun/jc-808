#ifndef EnvelopeH
#define EnvelopeH

class Envelope
{
public:
    struct EnvSettings {
        double startAmp;
        double peakAmp;
        double endAmp;

        double attack;
        double decay;
    };

    Envelope(EnvSettings &);

    void setStartAmp(double amp);
    void setPeakAmp(double amp);
    void setEndAmp(double amp);
    void setAttack(double attack);
    void setDecay(double decay);
    double getDuration();

    double getAmplitude(double time);

private:
    EnvSettings m_settings;
    double m_duration;

    double attackRamp(double time);
    double decayRamp(double time);
    double releaseRamp(double time);
};

#endif
