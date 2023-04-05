#include "Snake.hpp"



Snake::Snake(const Vec2i& pos)
{
    body[0] = pos;
    move_dir = Direction::NONE;
}

void Snake::Move(Direction dir)
{
    for(int i = length-1; i > 0; i--)
    {
        body[i] = body[i-1];
    }

    switch(dir)
    {
        case Direction::UP:
            body[0].y--;
            break;
        case Direction::DOWN:
            body[0].y++;
            break;
        case Direction::LEFT:
            body[0].x--;
            break;
        case Direction::RIGHT:
            body[0].x++;
            break;
    }

    if(body[0].x < 0)
        body[0].x = 15;
    else if(body[0].x > 15)
        body[0].x = 0;
    if(body[0].y < 0)
        body[0].y = 8;
    else if(body[0].y > 8)
        body[0].y = 0;

    move_dir = dir;
}

void Snake::Grow()
{
    body[length] = body[length-1];
    length++;
}

void Snake::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 180, 0, SDL_ALPHA_OPAQUE);

    SDL_Rect rect{0, 0, 50, 50};
    for(int i = 0; i < length; i++)
    {
        rect.x = body[i].x*50;
        rect.y = body[i].y*50;
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool Snake::IsCollision(const Vec2i& pos) const
{
    for(int i = 0; i < length; i++)
    {
        if(pos == body[i])
            return true;
    }
    return false;
}

bool Snake::IsSelfCollision() const
{
    for(int i = 1; i < length; i++)
    {
        if(body[0] == body[i])
            return true;
    }
    return false;
}