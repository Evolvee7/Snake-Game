#include "Game.hpp"
#include "Pellet.hpp"
#include <random>



Pellet::Pellet(Game* game): game(game)
{
}

void Pellet::Reposition()
{
    std::random_device dev;
    std::mt19937 rng(dev());

    int unoccupied_count;
    const std::unique_ptr<Vec2i[]>& unoccupied = game->GetUnoccupiedPositions(unoccupied_count);

    std::uniform_int_distribution<std::mt19937::result_type> dist(0, unoccupied_count-1);

    int index = dist(rng);
    pos = unoccupied[index];
}

void Pellet::Draw(SDL_Renderer* renderer)
{
    SDL_Rect rect{pos.x*50, pos.y*50, 50, 50};

    SDL_SetRenderDrawColor(renderer, 180, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}