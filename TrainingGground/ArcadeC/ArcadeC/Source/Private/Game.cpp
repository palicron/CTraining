#include "../Public/Game.h"

#include <iostream>
#include <SDL3/SDL.h>
#include "../../Source/Public/Actors/Actor.h"
#include "../Public/Maps/TileMap.h"
#include "../../Source/Public/Framework/EntityComponentSystem.h"
#include "../../Source/Public/Components/TransformComponent.h"
#include "../Public/Components/ColliderComponent.h"
#include "../Public/Components/MovementComponent.h"
#include "../Public/Components/SpriteComponent.h"
#include "../Public/Framework/PlayerController.h"
#include "../Public/Physics/NSquared.h"
#include "../Public/UI/UIManager.h"

static SDL_Window* main_window;
static SDL_Renderer* main_renderer;
bool Game::bIsRunning = false;

EntityManager manager;

auto& newPlayer(manager.CreateEntity());
auto& wall(manager.CreateEntity());
NSquared CurrentBradPase = NSquared();

SDL_Event Game::Event;

Game::Game()
{
    UIManagerPtr = std::make_unique<UIManager>();
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

    newPlayer.addComponent<TransformComponent>(Vector2D(10.f), Vector2D(32.f));
    newPlayer.addComponent<SpriteComponent>("Assets/TestAsset/Text_1.png");
    newPlayer.addComponent<MovementComponent>();
    newPlayer.addComponent<ColliderComponent>("Player");
   // newPlayer.GetComponent<ColliderComponent>().OnCollisionDelegate.Bind(std::bind(&Game::OnPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
    PlayerControllerPtr = std::make_unique<PlayerController>();
    PlayerControllerPtr->Init();
    PlayerControllerPtr->PossessPlayer(&newPlayer);

    wall.addComponent<TransformComponent>(Vector2D(300.f), Vector2D(100.f));
    wall.addComponent<SpriteComponent>("Assets/TestAsset/Text_1.png");
    wall.addComponent<ColliderComponent>("Wall");

    //@TODO ECAH COMPONENT SHOUDLR EGISTER On his own not here

    CurrentBradPase.Add(&wall.GetComponent<ColliderComponent>());
    CurrentBradPase.Add(&newPlayer.GetComponent<ColliderComponent>());

    return true;
}

void Game::handle_events()
{
    //TODO: i remove thje While(SDL_PollEvent(&Event)) chekc why AI recoment ti mabe it proses multiple inputs
    // NEED TO CAHNGE IT TO while becous this only pull one message this mean only one input per frame 
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
    manager.update();

    LastPlayerPos = newPlayer.GetComponent<TransformComponent>().GePosition();
    //@TODO : Chage of using a SDL Rect to a own Collision need for the momen im implementin the aabb tree
 /*  if (Collision::AABBCollision(newPlayer.GetComponent<ColliderComponent>().collider,
        wall.GetComponent<ColliderComponent>().collider))
    {
       
    }*/

}

void Game::PhysicsUpdate()
{
    CurrentBradPase.Update();
    ColliderPairList list = CurrentBradPase.ComputePairs();
    if (!list.empty())
    {
        for (auto value : list)
        {
            value.first->OnCollision(value.second);
            value.second->OnCollision(value.first);
        }
        
    }
}

void Game::UIUpdate() const
{
    if (UIManagerPtr)
    {
        UIManagerPtr->UpdateUI();
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
    wall.Draw();
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

void Game::OnPlayerCollision(ColliderComponent* PlayerCollision, ColliderComponent* OtherCollision)
{
    std::cout << "PlayerCollision" << '\n';

}
