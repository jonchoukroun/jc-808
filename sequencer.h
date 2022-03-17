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
    Sequencer() = default;
    ~Sequencer() = default;

    void init();

    void setTempo(double tempo);

    void setNote(Instrument &inst, int pos);

    void start();
    void stop();
    void updateBy(double time);

    vector<Instrument *> getActiveSamples();

    bool isPlaying();

private:
    array<vector<Instrument *>, SUBDIVISION> m_seq;

    vector<Instrument *> m_activeSamples;

    bool m_playing {false};

    double m_tempo {};
    double m_tempoStep {};
    double m_elapsed {};

    int m_pos {};
};

#endif
