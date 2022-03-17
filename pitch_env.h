#ifndef PITCH_ENV_H
#define PITCH_ENV_H

class PitchEnv
{
public:
    struct EnvSettings {
        double startPitch;
        double attackPitch;
        double releasePitch;

        double attack;
        double decay;
    };

    PitchEnv(EnvSettings &);
    ~PitchEnv() = default;

    void setStartPitch(double pitch);
    void setAttackPitch(double pitch);
    void setReleasePitch(double pitch);

    void setAttack(double attack);
    void setDecay(double decay);

    double getPitch(double time);

private:
    EnvSettings m_settings;
    double m_duration;

    double attackRamp(double time);
    double decayRamp(double time);
};

#endif
