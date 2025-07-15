#include "../Public/Game.h"

#include <iostream>
#include <__msvc_ostream.hpp>
#include <SDL3/SDL.h>

Game::Game()
{
    bIsRunning = false;
    
}

Game::~Game()
{
    clean();
}

bool Game::init(const char* title, int width, int height, bool fullscreen)
{
    
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }

    std::cout << "SDL initialized!" << '\n';

    SDL_WindowFlags WindowMode = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    main_window = SDL_CreateWindow(title, width, height, WindowMode);

    if (!main_window)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    main_renderer = SDL_CreateRenderer(main_window, nullptr);

    if (!main_renderer)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
    bIsRunning = true;

    SDL_Surface* tmp_Surface = IMG_Load("Assets/TestAsset/Text_1.png");
    PlayerTexture = SDL_CreateTextureFromSurface(main_renderer, tmp_Surface);
    SDL_DestroySurface(tmp_Surface);
  
    return true;
    
}

void Game::handle_events()
{
    SDL_Event event = {};

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            bIsRunning = false;
            std::cout << "Game QUIT" << '\n';
            break;
        case SDL_EVENT_KEY_DOWN:
            if (event.key.key == SDLK_ESCAPE)
            {
                std::cout << "Escape Key Press Edning Game " << '\n';
                bIsRunning = false;
            }
        default: ;
        }
    }


}

void Game::update()
{
    DestinationRect.h = 25;
    DestinationRect.w = 25;

    DestinationRect.x += 1;
    DestinationRect.y = 100;
}

void Game::render()
{
    if (!main_renderer)
    {
        return;
    }
    
    SDL_RenderClear(main_renderer);

    if (PlayerTexture)
    {
        SDL_RenderTexture(main_renderer,PlayerTexture,nullptr,&DestinationRect);
    }
   
    SDL_RenderPresent(main_renderer);
   // SDL_Delay(1000 / 60);
}

void Game::clean()
{
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
}

bool Game::running()
{
    return bIsRunning;
}
