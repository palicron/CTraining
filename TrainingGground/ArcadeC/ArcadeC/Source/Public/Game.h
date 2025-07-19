#pragma once

#include <memory>
#include <SDL3_image/SDL_image.h>

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
    void render();
    void clean();

    bool running();

    static SDL_Window* GetWindow();
    static SDL_Renderer* GetRenderer();

private:

    bool bIsRunning;
    
    // TODO: this shoudl not be resposability of the Game , this shoudl be create in somethin like a Game Mode 
    std::unique_ptr<Actor> Player;
    std::unique_ptr<Actor> Player2;
    std::unique_ptr<TileMap> Map;

};
