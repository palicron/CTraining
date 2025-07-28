#include "../Public/Game.h"

#include <iostream>
#include <SDL3/SDL.h>
#include "../../Source/Public/Actors/Actor.h"
#include "../Public/Maps/TileMap.h"
#include "../../Source/Public/Framework/EntityComponentSystem.h"
#include "../../Source/Public/Components/TransformComponent.h"
#include "../Public/Components/MovementComponent.h"
#include "../Public/Components/SpriteComponent.h"
#include "../Public/Framework/PlayerController.h"

static SDL_Window* main_window;
static SDL_Renderer* main_renderer;
bool Game::bIsRunning = false;

EntityManager manager;

auto& newPlayer(manager.CreateEntity());
SDL_Event Game::Event;

Game::Game()
{
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
    newPlayer.addComponent<MovementComponent>();

    PlayerControllerPtr = std::make_unique<PlayerController>();
    PlayerControllerPtr->Init();
    PlayerControllerPtr->PossessPlayer(&newPlayer);
    return true;
    
}

void Game::handle_events()
{
    SDL_PollEvent(&Event);

    switch (Event.type)
    {
    case SDL_EVENT_QUIT:
        QuitGame();
        break;
    case SDL_EVENT_KEY_DOWN:
        if (Event.key.key == SDLK_ESCAPE)
        {
            QuitGame();
        }
        if (Event.key.key == SDLK_SPACE)
        {
            std::printf("SPACE");
        }
    default: ;
    }
 
}

void Game::update()
{
    PlayerControllerPtr->Update();
    newPlayer.update();
    manager.update();
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
    if (PlayerControllerPtr)
    {
        PlayerControllerPtr.reset();
    }
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

void Game::QuitGame()
{
    bIsRunning = false;
    std::cout << "Ending Game" << '\n';
}
