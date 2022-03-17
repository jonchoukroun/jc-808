#ifndef ENVELOPE_H
#define ENVELOPE_H

/**
 * This abstract class is the base for all ADSR implementations.
 *
 * For now it only supports attack and decay stages.
 **/
class Envelope
{
public:
    Envelope() = default;
    ~Envelope() = default;

    double getDuration();

    void setAttack(double attack);
    void setDecay(double decay);

    void setStart(double start);
    void setPeak(double peak);
    void setRelease(double release);

    double getEnvValue(double time);

protected:
    double m_attack;
    double m_decay;
    double m_duration;

    double m_start;
    double m_peak;
    double m_release;

private:
    double attackRamp(double time);

    double decayRamp(double time);

};

#endif
