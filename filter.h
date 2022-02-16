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
    ~Filter();

    void setFilter(double freq, double q);

    double filter(double input);

private:
    static const int mSampleRate = 44100;

    int mType;
    double mFreq;
    double mQ;

    double a0, a1, a2, b1, b2;
    double z1, z2;

    void calcFilter();
};

#endif
