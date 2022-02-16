#include <cmath>
#include "filter.h"

Filter::Filter(int type)
{
    mType = type;
}

Filter::~Filter() {}

void Filter::setFilter(double freq, double q)
{
    mFreq = freq / (double)mSampleRate;
    mQ = q;
    calcFilter();
}

double Filter::filter(double input)
{
    double output = input * a0 + z1;
    z1 = input * a1 + z2 - b1 * output;
    z2 = input * a2 - b2 * output;
    return output;
}

void Filter::calcFilter()
{
    double norm;
    double K = std::tan(M_PI * mFreq);
    switch (mType)
    {
    case BANDPASS:
        norm = 1 / (1 + K / mQ + K * K);
        a0 = K / mQ * norm;
        a1 = 0;
        a2 = -a0;
        b1 = 2 * (K * K - 1) * norm;
        b2 = (1 - K / mQ + K * K) * norm;
        break;

    case HIGHPASS:
        norm = 1 / (1 + K / mQ + K * K);
        a0 = 1 * norm;
        a1 = -2 * a0;
        a2 = a0;
        b1 = 2 * (K * K - 1) *norm;
        b2 = (1 - K / mQ + K * K) * norm;
        break;

    default:
        break;
    }
}
