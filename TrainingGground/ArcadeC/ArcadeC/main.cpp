#include <memory>
#include <SDL3/SDL.h>
#include "Source/Public/Game.h"

static std::unique_ptr<Game> game;

int main(int argc, char* args[])
{
    const int TargetFPS = 60;
    const int frameDelay = 1000 / TargetFPS;

    uint64_t frameStart = 0;
    uint64_t frameTime = 0;
    game = std::make_unique<Game>();

    

    if (!game->init("Arcade C", 1280, 720, false))
    {
        SDL_DestroyWindow(Game::GetWindow());
        SDL_Quit();
        return 1;
    }

    uint64_t freq = SDL_GetPerformanceFrequency();

    //Game Main loop
    while (game->running())
    {
        frameStart = SDL_GetPerformanceCounter();

        game->handle_events();
        game->update();
        game->render();


        frameTime = ((SDL_GetPerformanceCounter() - frameStart) * 1000) / freq;
        
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        
        std::printf("Frame time: %.3f ms\n", static_cast<float>(SDL_GetPerformanceCounter() - frameStart));
    }


    //Ending the Game
    game = nullptr;
    SDL_Quit();


    return 0;
}
