#include "Game.hpp"
#include "Snake.hpp"



Snake::Snake(const Vec2i& pos, Game* game): pos(pos), game(game)
{
    move_dir = Direction::NONE;
}

void Snake::Move(Direction dir)
{
    switch(dir)
    {
        case Direction::UP:
            pos.y--;
            break;
        case Direction::DOWN:
            pos.y++;
            break;
        case Direction::LEFT:
            pos.x--;
            break;
        case Direction::RIGHT:
            pos.x++;
            break;
    }

    if(pos.x < 0)
        pos.x = 15;
    else if(pos.x > 15)
        pos.x = 0;
    if(pos.y < 0)
        pos.y = 8;
    else if(pos.y > 8)
        pos.y = 0;

    move_dir = dir;
}

void Snake::Draw(SDL_Renderer* renderer)
{
    SDL_Rect rect{pos.x*50, pos.y*50, 50, 50};

    SDL_SetRenderDrawColor(renderer, 0, 180, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}