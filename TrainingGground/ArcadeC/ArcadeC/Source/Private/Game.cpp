#include "../Public/Game.h"

#include <iostream>
#include <SDL3/SDL.h>
#include "../../Source/Public/Actors/Actor.h"
#include "../Public/Maps/TileMap.h"
#include "../../Source/Public/Framework/EntityComponentSystem.h"
#include "../../Source/Public/Components/TransformComponent.h"
#include "../Public/Components/SpriteComponent.h"

static SDL_Window* main_window;
static SDL_Renderer* main_renderer;

EntityManager manager;

auto& newPlayer(manager.CreateEntity());
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

   // SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
    bIsRunning = true;
    Map = std::make_unique<TileMap>();

    newPlayer.addComponent<TransformComponent>(10.f,10.f);
    newPlayer.addComponent<SpriteComponent>("Assets/TestAsset/Text_1.png");
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
    newPlayer.update();
    manager.update();
    std::cout << newPlayer.GetComponent<TransformComponent>().GetX() << '\n';

    if (newPlayer.GetComponent<TransformComponent>().GetX() > 100)
    {
        
    }
}

void Game::render()
{
    if (!main_renderer)
    {
        return;
    }
    
    SDL_RenderClear(main_renderer);
    if (Map)
    {
        Map->DrawMap();
    }
    newPlayer.Draw();

    SDL_RenderPresent(main_renderer);
   // SDL_Delay(1000 / 60);
}

void Game::clean()
{
    newPlayer.Destroy();
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
}

bool Game::running()
{
    return bIsRunning;
}

SDL_Window* Game::GetWindow()
{
    return main_window; 
}

SDL_Renderer* Game::GetRenderer()
{
     return main_renderer; 
}
