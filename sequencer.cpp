#include <iostream>
#include "clap.h"
#include "closed_hat.h"
#include "envelope.h"
#include "filter.h"
#include "kick.h"
#include "pitch_env.h"
#include "sequencer.h"
#include "snare.h"

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
    Kick *kick1 = new Kick();
    kick1->setDefaults();
    setNote(*kick1, 0);

    Clap *clap1 = new Clap();
    clap1->setDefaults();
    setNote(*clap1, 4);

    Kick *kick2 = new Kick();
    kick2->setDefaults();
    kick2->setLevel(0.4);
    setNote(*kick2, 7);

    Kick *kick3 = new Kick();
    kick3->setDefaults();
    setNote(*kick3, 8);

    Clap *clap2 = new Clap();
    clap2->setDefaults();
    setNote(*clap2, 12);

    for (int i = 0; i < SUBDIVISION; ++i) {
        if (i % 2 == 0) {
            ClosedHat *hat = new ClosedHat();
            hat->setDefaults();
            setNote(*hat, i);

            if (i % 4 != 0) {
                hat->setLevel(0.4);
            }
        }
    }
}
void Sequencer::setTempo(double tempo)
{
    m_tempo = tempo;
    m_tempoStep = MS_PER_MINUTE / (tempo * 4) / 1000.0;
}

void Sequencer::setNote(Instrument &inst, int pos)
{
    for (auto &beat : m_seq) {
        for (auto i : beat) {
        }
    }
    if (pos >= SUBDIVISION) {
        cout << "Invalid note position" << endl;
        return;
    }
    m_seq[pos].push_back(&inst);
    for (auto &beat : m_seq) {
        for (auto i : beat) {
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

