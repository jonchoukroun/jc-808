#include <iostream>
#include "clap.h"
#include "closed_hat.h"
#include "kick.h"
#include "sequencer.h"
#include "snare.h"

#define MS_PER_MINUTE 60000.0

using std::cout;
using std::endl;

void setSeq(Sequencer *seq);

Sequencer::Sequencer()
{
    array<vector<Instrument *>, SUBDIVISION> seq;
    for (int i = 0; i < SUBDIVISION; i++) {
        vector<Instrument *> v;
        seq[i] = v;
    }
    mSeq = seq;

    vector<Instrument *> samples;
    mActiveSamples = samples;

    mPlaying = false;

    mTempo = 0.0;
    mTempoStep = 0.0;
    mElapsed = 0.0;

    mPos = 0;

    setSeq(this);
}

Sequencer::~Sequencer() {}

void Sequencer::setTempo(double tempo)
{
    mTempo = tempo;
    mTempoStep = MS_PER_MINUTE / (tempo * 4) / 1000.0;
}

void Sequencer::setNote(Instrument *inst, int pos)
{
    if (pos >= SUBDIVISION) {
        cout << "Invalid note position" << endl;
        return;
    }
    mSeq[pos].push_back(inst);
}

void Sequencer::start()
{
    // TODO: error handling UI
    if (mTempo == 0.0) return;

    vector<Instrument *> notes = mSeq[mPos];
    for (auto n : notes) {
        if (n == nullptr) {
            cout << "Undefined instrument" << endl;
            continue;
        }
        n->trigger();
        mActiveSamples.push_back(n);
    }

    mPlaying = true;
}

void Sequencer::stop()
{
    mPlaying = false;
    mElapsed = 0.0;
    mPos = 0;
    mActiveSamples.clear();
}

void Sequencer::updateBy(double time)
{
    if (mElapsed > mTempoStep) {
        mElapsed = 0.0;

        mPos++;
        if (mPos >= SUBDIVISION) mPos = 0;

        vector<Instrument *> notes = mSeq[mPos];
        for (auto i : notes) {
            i->trigger();
            mActiveSamples.push_back(i);
        }
    } else {
        for (auto s = mActiveSamples.begin(); s != mActiveSamples.end(); s++) {
            Instrument *i = *s;
            i->updateBy(time);
            if (!i->isPlaying()){
                i->release();
                mActiveSamples.erase(s);
                s--;
            }
        }
    }

    mElapsed += time;
}

vector<Instrument *> Sequencer::getActiveSamples()
{
    return mActiveSamples;
}

void setSeq(Sequencer *seq)
{
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
    for (int i = 0; i < 16; i++) {
        seq->setNote(new ClosedHat(), i);
    }
    seq->setNote(new Kick(), 0);
    seq->setNote(new Clap(), 4);
    seq->setNote(new Kick(), 7);
    seq->setNote(new Kick(), 8);
    seq->setNote(new Clap(), 12);
}
