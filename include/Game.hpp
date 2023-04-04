#pragma once

#include "Pellet.hpp"
#include "Snake.hpp"
#include <memory>
#include <SDL2/SDL.h>



class Game
{
public:
    Game(int screen_w, int screen_h, const char* title);
    ~Game();

    void Run();
    void GameOver();

    const std::unique_ptr<Vec2i[]> GetUnoccupiedPositions(int& count) const;
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