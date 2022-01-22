#include <iostream>
#include "kick_sample.h"
#include <SDL2/SDL.h>

using std::cout;
using std::endl;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;


SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

bool init();

void close();

int main(int argc, char *args[])
{
    if (!init()) return -1;

    std::string prompt = "Press SPACE to play sample.";

    bool quit = false;
    SDL_Event e;

    KickSample *kick = new KickSample();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;

                    case SDLK_1:
                        kick->trigger();
                        break;

                    // case SDLK_2:
                    //     square->play();
                    //     break;

                    // case SDLK_3:
                    //     triangle->play();
                    //     break;

                    // case SDLK_4:
                    //     saw->play();

                    default:
                        break;
                }
            }
        }
    }

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
