#include "Game.hpp"
#include "Utilities.cpp"



Game::Game(int screen_w, int screen_h, const char* title):
snake(Vec2i{4,4}, this), pellet(this)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(screen_w, screen_h, 0, &window, &renderer);
    SDL_SetWindowTitle(window, title);
}

Game::~Game()
{
    if(renderer)
        SDL_DestroyRenderer(renderer);
    if(window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Run()
{
    uint32_t move_delay_ms = 150;
    uint32_t start_ms = SDL_GetTicks();
    Direction next_move_dir = Direction::NONE;
    SDL_Event e;

    while(!quit)
    {
        if(SDL_TICKS_PASSED(SDL_GetTicks() - move_delay_ms, start_ms))
        {
            start_ms = SDL_GetTicks();

            if(are_opposite(snake.GetMoveDir(), next_move_dir))
                next_move_dir = snake.GetMoveDir();
            
            snake.Move(next_move_dir);

            if(snake.IsSelfCollision())
            {
                quit = true;
                // TODO: Make die animation
            }
            else if(snake.GetHeadPos() == pellet.GetPos())
            {
                snake.Grow();
                if(snake.GetLength() == 16*9)
                {
                    // TODO: Make win animation
                }
                else
                    pellet.Reposition();
            }
            Render();
        }

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_UP:
                        next_move_dir = Direction::UP;
                        break;
                    case SDLK_DOWN:
                        next_move_dir = Direction::DOWN;
                        break;
                    case SDLK_LEFT:
                        next_move_dir = Direction::LEFT;
                        break;
                    case SDLK_RIGHT:
                        next_move_dir = Direction::RIGHT;
                        break;
                }
            }
        }
    }
}

bool Game::IsOccupied(const Vec2i& pos) const
{
    for(int i = 0; i < snake.GetLength(); i++)
        if(snake.GetPositions()[i] == pos)
            return true;
    if(pellet.GetPos() == pos)
        return true;
    return false;
}

void Game::Render()
{
    // Draw background
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Make mesh-like structure
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{0, 0, 50, 50};
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 16; x++)
        {
            rect.x = x * 50;
            rect.y = y * 50;
            SDL_RenderDrawRect(renderer, &rect);
        }
    }

    // Render all actors
    pellet.Draw(renderer);
    snake.Draw(renderer);

    // Display
    SDL_RenderPresent(renderer);
}