#include "Game.hpp"
#include "Pellet.hpp"
#include <random>



Pellet::Pellet(Game* game): game(game)
{
    Reposition();
}

void Pellet::Reposition()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_x(0, 15);
    std::uniform_int_distribution<std::mt19937::result_type> dist_y(0, 8);

    Vec2i rand_pos;
    rand_pos.x = dist_x(rng);
    rand_pos.y = dist_y(rng);
    while(game->IsOccupied(rand_pos))
    {
        rand_pos.x = dist_x(rng);
        rand_pos.y = dist_y(rng);
    }

    // TODO: Instead of infinitly randomizing pos and checking if is occupied
    //       gather all unoccupied positions and then get one (so we can see when we win :P)

    pos = rand_pos;
}

void Pellet::Draw(SDL_Renderer* renderer)
{
    SDL_Rect rect{pos.x*50, pos.y*50, 50, 50};

    SDL_SetRenderDrawColor(renderer, 180, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}