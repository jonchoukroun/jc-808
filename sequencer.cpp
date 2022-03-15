#include <iostream>
// #include "clap.h"
// #include "closed_hat.h"
#include "kick.h"
#include "sequencer.h"
// #include "snare.h"

#define MS_PER_MINUTE 60000.0

using std::cout;
using std::endl;

/**
 *  0 1
 *  1 e
 *  2 +
 *  3 a
 *  4 2
 *  5 e
 *  6 +
 *  7 a
 *  8 3
 *  9 e
 * 10 +
 * 11 a
 * 12 4
 * 13 e
 * 14 +
 * 15 a
 **/
void Sequencer::init()
{
    Kick *kick = new Kick(0.8, 0.5);
    setNote(*kick, 0);
}
void Sequencer::setTempo(double tempo)
{
    m_tempo = tempo;
    m_tempoStep = MS_PER_MINUTE / (tempo * 4) / 1000.0;
}

void Sequencer::setNote(Instrument &inst, int pos)
{
    cout << "Before" << endl;
    for (auto &beat : m_seq) {
        for (auto i : beat) {
            cout << "inst at " << &i << endl;
        }
    }
    if (pos >= SUBDIVISION) {
        cout << "Invalid note position" << endl;
        return;
    }
    cout << "Will push back " << inst.getName() << endl;
    m_seq[pos].push_back(&inst);
    cout << "After" << endl;
    for (auto &beat : m_seq) {
        for (auto i : beat) {
            cout << "inst at " << &i << endl;
        }
    }
}

void Sequencer::start()
{
    // TODO: error handling UI
    if (m_tempo == 0.0) return;

    vector<Instrument *> beat = m_seq.at(m_pos);
    for (auto &i : beat) {
        if (i == nullptr) {
            cout << "Undefined instrument" << endl;
            continue;
        }
        cout << "start | will trigger " << i->getName() << endl;
        i->trigger();
        m_activeSamples.push_back(i);
    }

    m_playing = true;
}

void Sequencer::stop()
{
    m_playing = false;
    m_elapsed = 0.0;
    m_pos = 0;
    m_activeSamples.clear();
}

void Sequencer::updateBy(double time)
{
    if (m_elapsed > m_tempoStep) {
        m_elapsed = 0.0;

        m_pos++;
        if (m_pos >= SUBDIVISION) m_pos = 0;

        vector<Instrument *> beat = m_seq.at(m_pos);
        for (auto &i : beat) {
            cout << "Will trigger " << i->getName() << endl;
            i->trigger();
            m_activeSamples.push_back(i);
        }
    } else {
        for (auto s = m_activeSamples.begin(); s != m_activeSamples.end(); s++) {
            auto i = *s;
            i->updateBy(time);
            if (!i->isPlaying()){
                i->release();
                m_activeSamples.erase(s);
                s--;
            }
        }
    }

    m_elapsed += time;
}

vector<Instrument *> Sequencer::getActiveSamples()
{
    return m_activeSamples;
}

