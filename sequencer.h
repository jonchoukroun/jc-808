#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "instrument.h"

#define SUBDIVISION 16

using std::array;
using std::vector;

const int SAMPLE_RATE = 44100;

class Sequencer
{
public:
    Sequencer();
    ~Sequencer();

    void setTempo(double tempo);

    void setNote(Instrument *inst, int pos);

    void start();
    void stop();
    void updateBy(double time);

    vector<Instrument *> getActiveSamples();

    bool isPlaying();

private:
    array<vector<Instrument *>, SUBDIVISION> mSeq;

    vector<Instrument *> mActiveSamples;

    bool mPlaying;

    double mTempo;
    double mTempoStep;
    double mElapsed;

    int mPos;
};

#endif
