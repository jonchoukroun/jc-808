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
    mTempo = tempo;
    mTempoStep = MS_PER_MINUTE / (tempo * 4) / 1000.0;
}

void Sequencer::setNote(Instrument &inst, int pos)
{
    cout << "Before" << endl;
    for (auto &beat : mSeq) {
        for (auto i : beat) {
            cout << "inst at " << &i << endl;
        }
    }
    if (pos >= SUBDIVISION) {
        cout << "Invalid note position" << endl;
        return;
    }
    cout << "Will push back " << inst.getName() << endl;
    mSeq[pos].push_back(&inst);
    cout << "After" << endl;
    for (auto &beat : mSeq) {
        for (auto i : beat) {
            cout << "inst at " << &i << endl;
        }
    }
}

void Sequencer::start()
{
    // TODO: error handling UI
    if (mTempo == 0.0) return;

    vector<Instrument *> beat = mSeq.at(mPos);
    for (auto &i : beat) {
        if (i == nullptr) {
            cout << "Undefined instrument" << endl;
            continue;
        }
        i->trigger();
        mActiveSamples.push_back(i);
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

        vector<Instrument *> beat = mSeq.at(mPos);
        for (auto &i : beat) {
            cout << "Will trigger " << i->getName() << endl;
            i->trigger();
            mActiveSamples.push_back(i);
        }
    } else {
        for (auto s = mActiveSamples.begin(); s != mActiveSamples.end(); s++) {
            auto i = *s;
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

