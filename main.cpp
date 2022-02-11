#include <iostream>
#include <SDL2/SDL.h>
#include "audio_engine.h"
#include "kick.h"
#include "snare.h"
#include "timer.h"

using std::cout;
using std::endl;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

static const double TICKS_PER_FRAME = 1000 / 60;


SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

bool init();

void close();

void setSeq(Sequencer *);

int main(int argc, char *args[])
{
    if (!init()) return -1;

    bool quit = false;
    SDL_Event e;
    Timer fpsTimer;


    Sequencer seq {nullptr};
    setSeq(&seq);

    AudioEngine *engine = new AudioEngine(&seq);

    while (!quit) {
        fpsTimer.start();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;

                    case SDLK_SPACE:
                        if (engine->isPlaying()) {
                            engine->stop();
                        } else {
                            engine->start();
                        }
                        break;

                    case SDLK_d:
                        cout << "Debugging" << endl;
                        for (auto note : seq) {
                            cout << (note == nullptr ? "*" : note->getName()) << endl;
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        Uint32 ticks = fpsTimer.getTicks();
        if (ticks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - ticks);
        }
    }

    if (fpsTimer.isRunning()) fpsTimer.stop();

    engine->stop();

    close();

    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "Failed to initialize SDL! Error: " << SDL_GetError() << endl;
        return false;
    }

    gWindow = SDL_CreateWindow(
        "Audio Engine Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (gWindow == NULL)
    {
        cout << "Failed to create Window! Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void close()
{
    SDL_Quit();
}

void setSeq(Sequencer *seq)
{
    /**
     * 0 K
     * 1 K
     * 2 S
     * 3 -
     * 4 -
     * 5 K
     * 6 S
     * 7 -
     **/
    for (int i = 0; i < seq->size(); i++) {
        switch (i) {
            case 0:
            case 5:
                (*seq)[i] = new Kick();
                break;
            case 2:
            case 6:
                (*seq)[i] = new Snare();
                break;
            default: break;
        }
    }
}
