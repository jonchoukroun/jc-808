#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "audio_engine.h"
#include "kick.h"
#include "snare.h"
#include "timer.h"

using std::cout;
using std::endl;
using std::vector;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

static const double TICKS_PER_FRAME = 1000 / 60;


SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

bool init();

void close();

int main(int argc, char *args[])
{
    if (!init()) return -1;

    bool quit = false;
    SDL_Event e;
    Timer fpsTimer;

    AudioEngine *engine = new AudioEngine();
    Kick *kick = new Kick();
    Snare *snare = new Snare();

    while (!quit) {
        fpsTimer.start();
        engine->start();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;

                    case SDLK_1:
                        kick->trigger();
                        engine->playKick(kick);
                        break;

                    case SDLK_2:
                        snare->trigger();
                        engine->playSnare(snare);
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
