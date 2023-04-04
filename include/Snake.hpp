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
    void Grow();
    void Draw(SDL_Renderer* renderer);

    bool IsSelfCollision() const;
    int GetLength() const { return length; }
    Direction GetMoveDir() const { return move_dir; }
    const Vec2i& GetHeadPos() const { return body[0]; }
    const Vec2i* GetPositions() const { return body; }

private:
    Vec2i body[16*9];
    int length = 1;
    Direction move_dir;

    Game* game;
};