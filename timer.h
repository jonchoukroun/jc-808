#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();

    void start();
    void stop();

    Uint32 getTicks();

    bool isRunning();

private:
    Uint32 mStartTicks;
    bool mRunning;
};

#endif
