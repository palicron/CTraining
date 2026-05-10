#include <memory>
#include <SDL3/SDL.h>
#include "Source/Public/Game.h"

static std::unique_ptr<Game> GameInstance;
#include <rapidjson/document.h>

int main(int argc, char* args[])
{

    const int TargetFPS = 60;
    const int frameDelay = 1000 / TargetFPS;
    ///////////////////Load Data /////////////////////


    uint64_t frameStart = 0;
    uint64_t frameTime = 0;
    
    GameInstance = std::make_unique<Game>();

    
    rapidjson::Document;
    if (!GameInstance->init("Arcade C", 800, 640, false))
    {
        SDL_DestroyWindow(Game::GetWindow());
        SDL_Quit();
        return 1;
    }

    uint64_t freq = SDL_GetPerformanceFrequency();

    //Game Main loop
    while (GameInstance->running())
    {
        frameStart = SDL_GetPerformanceCounter();

        GameInstance->handle_events();
        GameInstance->update();
        GameInstance->PhysicsUpdate();
        GameInstance->UIUpdate();
        GameInstance->render();


        frameTime = ((SDL_GetPerformanceCounter() - frameStart) * 1000) / freq ;
        
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        
       // std::printf("Frame time: %.3f ms\n", static_cast<float>(SDL_GetPerformanceCounter() - frameStart));
    }


    //Ending the Game
    GameInstance = nullptr;
    SDL_Quit();


    return 0;
}
