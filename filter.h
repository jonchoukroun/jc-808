#ifndef FILTER_H
#define FILTER_H

enum {
    BANDPASS = 0,
    HIGHPASS,
};

class Filter
{
public:
    Filter(int type);
    ~Filter() = default;

    void setFilter(double freq, double q);

    double filter(double input);

private:
    static const int m_sampleRate = 44100;

    int m_type;
    double m_freq;
    double m_q;

    double a0, a1, a2, b1, b2;
    double z1, z2;

    void calcFilter();
};

#endif
