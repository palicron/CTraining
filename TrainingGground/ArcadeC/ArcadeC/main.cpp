#include <memory>
#include <SDL3/SDL.h>
#include "Source/Public/Game.h"

static std::unique_ptr<Game> game;

int main(int argc, char* args[])
{
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
        uint64_t startTick = SDL_GetPerformanceCounter();
        game->handle_events();
        game->update();
        game->render();

        uint64_t EndTick = SDL_GetPerformanceCounter();
        double deltaMS = ((EndTick - startTick) *  1000.f) / freq;
        std::printf("Frame time: %.3f ms\n", deltaMS);

    }


    //Ending the Game
    game = nullptr;
    SDL_Quit();


    return 0;
}
