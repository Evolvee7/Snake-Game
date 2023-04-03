#pragma once

#include "Direction.hpp"
#include "Vec2i.hpp"
#include <SDL2/SDL_render.h>



class Game;

class Snake
{
public:
    Snake(const Vec2i& pos, Game* game);

    void Move(Direction dir);
    void Draw(SDL_Renderer* renderer);

    const Vec2i& GetPos() const { return pos; }
    Direction GetMoveDir() const { return move_dir; }

private:
    Vec2i pos;
    Direction move_dir;

    Game* game;
};