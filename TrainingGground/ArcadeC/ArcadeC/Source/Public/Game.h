#pragma once

#include <memory>
#include <SDL3_image/SDL_image.h>

#include "Math/Vector2D.h"

class Vector2D;
class PlayerController;
struct SDL_Window;
struct SDL_Renderer;
class Actor;
class TileMap;

class Game
{

public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height, bool fullscreen);
    //Handle All Games States
    void handle_events();
    void update();
    void PhysicsUpdate();
    void render();
    void clean();

    bool running();

    static SDL_Window* GetWindow();
    static SDL_Renderer* GetRenderer();

    static SDL_Event Event;

    std::unique_ptr<PlayerController> PlayerControllerPtr;

    
    void QuitGame();
private:

    static bool bIsRunning;
    
    // TODO: this shoudl not be resposability of the Game , this shoudl be create in somethin like a Game Mode 
    std::unique_ptr<TileMap> Map;


    //@TODO this is just for collsion test purpose shoudl be remove
    Vector2D LastPlayerPos;

};
