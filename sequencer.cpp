#include <iostream>
#include <sstream>
#include "sequencer.h"
#include "timer.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::vector;

const double MS_PER_MINUTE = 60000.0;

Sequencer::Sequencer()
{
    vector<unsigned char> empty(mNotesPerBeat, '-');
    vector<vector<unsigned char>> seq(mBeatCount, empty);
    mSeq = seq;

    mCurrentBeat = 0;
    mIsPlaying = false;

    mTempo = 0;
    mBeatDuration = 0.0;
}

void Sequencer::setTempo(int tempo)
{
    mTempo = tempo;
    mBeatDuration = MS_PER_MINUTE / mTempo;
}

bool Sequencer::addNote(unsigned char note, int beat)
{
    if (beat > mSeq.size()) return false;

    vector<unsigned char> notes = mSeq.at(beat);
    switch (note) {
        case 'K':
            notes.at(0) = 'K';
            break;
        case 'S':
            notes.at(1) = 'S';
            break;
        case 'H':
            notes.at(2) = 'H';
            break;
    }
    mSeq.at(beat) = notes;

    return true;
}

void Sequencer::play()
{
    mIsPlaying = true;
    Timer timer;
    while (mCurrentBeat < mBeatCount) {
        timer.start();
        vector<unsigned char> notes = mSeq.at(mCurrentBeat);
        for (unsigned char n : notes) {
            cout << n << "\t";
        }
        cout << endl;
        if (timer.getTicks() < mBeatDuration) {
            SDL_Delay(mBeatDuration - timer.getTicks());
        }
        mCurrentBeat++;
    }
    if (timer.isRunning()) timer.stop();
}

void Sequencer::pause()
{
    cout << "Pausing" << endl;
    mIsPlaying = false;
}

void Sequencer::rewind()
{
    cout << "Rewinding" << endl;
    if (mIsPlaying) mIsPlaying = false;
    mCurrentBeat = 0;
}

bool Sequencer::isPlaying()
{
    return mIsPlaying;
}

// Debug Methods
void Sequencer::printNotes()
{
    for (vector<unsigned char> notes : mSeq) {
        for (unsigned char note : notes) {
            cout << note << "\t";
        }
        cout << endl;
    }
}

void Sequencer::printValues()
{
    cout << "mCurrentBeat = " << mCurrentBeat << endl;
    cout << "mIsPlaying = " << (mIsPlaying ? "true" : "false") << endl;
    cout << "mTempo = " << mTempo << endl;
    cout << "mBeatDuration = " << mBeatDuration << endl;
}
