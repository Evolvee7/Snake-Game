#pragma once

#include "Pellet.hpp"
#include "Snake.hpp"
#include <SDL2/SDL.h>



class Game
{
public:
    Game(int screen_w, int screen_h, const char* title);
    ~Game();

    void Run();

    bool IsOccupied(const Vec2i& pos) const;

private:
    void Render();

private:
    bool quit = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Snake snake;
    Pellet pellet;
};