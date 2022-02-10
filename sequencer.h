#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <SDL2/SDL.h>
#include <vector>

const int SAMPLE_RATE = 44100;

class Sequencer
{
public:
    Sequencer();

    void setTempo(int tempo);

    bool addNote(unsigned char note, int beat);

    void play();
    void pause();
    void rewind();

    bool isPlaying();

    // Debug methods
    void printNotes();
    void printValues();

private:
    static const int mBeatCount = 8;
    static const int mNotesPerBeat = 3;

    int mCurrentBeat;
    bool mIsPlaying;

    // beats per minute
    int mTempo;
    double mBeatDuration;

    std::vector<std::vector<unsigned char>> mSeq;
};

#endif
