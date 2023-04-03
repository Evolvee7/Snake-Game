#include <random>
#include <SDL2/SDL.h>



enum Field
{
    EMPTY,
    SNAKE,
    PELLET
};

enum Direction
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void render_screen(Field grid[9][16], SDL_Renderer* renderer);

bool move_snake(Field grid[9][16], int& snake_x, int& snake_y, Direction dir);

void reposition_pellet(Field grid[9][16], int& pellet_x, int& pellet_y);

int main()
{
    // Initalize SDL2
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(800, 450, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Snake");

    Field grid[9][16];

    // Set snake position
    int snake_x = 0;
    int snake_y = 0;
    grid[snake_y][snake_x] = Field::SNAKE;

    int pellet_x = -1;
    int pellet_y = -1;
    reposition_pellet(grid, pellet_x, pellet_y);

    render_screen(grid, renderer);

    // Loop variables
    uint32_t move_delay_ms = 500;
    uint32_t start_ms = SDL_GetTicks();
    Direction move_dir = Direction::NONE;
    bool quit = false;
    SDL_Event e;

    // Infinite loop
    while(!quit)
    {
        if(SDL_TICKS_PASSED(SDL_GetTicks() - move_delay_ms, start_ms))
        {
            if(move_snake(grid, snake_x, snake_y, move_dir))
            {
                if(snake_x == pellet_x && snake_y == pellet_y)
                    reposition_pellet(grid, pellet_x, pellet_y);
                render_screen(grid, renderer);
            }
            else
            {
                if(move_dir != Direction::NONE)
                    quit = true;
            }

            start_ms = SDL_GetTicks();
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
                        move_dir = Direction::UP;
                        break;
                    case SDLK_DOWN:
                        move_dir = Direction::DOWN;
                        break;
                    case SDLK_LEFT:
                        move_dir = Direction::LEFT;
                        break;
                    case SDLK_RIGHT:
                        move_dir = Direction::RIGHT;
                        break;
                }
            }
        }
    }

    // Deinitalize SDL2
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}








void render_screen(Field grid[9][16], SDL_Renderer* renderer)
{
    SDL_Rect rect{0, 0, 50, 50};

    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 16; x++)
        {
            rect.x = x * 50;
            rect.y = y * 50;

            switch(grid[y][x])
            {
                case Field::EMPTY:
                    SDL_SetRenderDrawColor(renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);
                    break;
                case Field::SNAKE:
                    SDL_SetRenderDrawColor(renderer, 0, 180, 0, SDL_ALPHA_OPAQUE);
                    break;
                case Field::PELLET:
                    SDL_SetRenderDrawColor(renderer, 180, 0, 0, SDL_ALPHA_OPAQUE);
                    break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 16; x++)
        {
            rect.x = x * 50;
            rect.y = y * 50;
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}

bool move_snake(Field grid[9][16], int& snake_x, int& snake_y, Direction dir)
{
    int target_x = snake_x;
    int target_y = snake_y;

    switch(dir)
    {
        case Direction::UP:
            target_y--;
            break;
        case Direction::DOWN:
            target_y++;
            break;
        case Direction::LEFT:
            target_x--;
            break;
        case Direction::RIGHT:
            target_x++;
            break;
        case Direction::NONE:
            return false;
    }
    if(target_x < 0 || target_x > 15 || target_y < 0 || target_y > 8)
        return false;
    
    grid[snake_y][snake_x] = Field::EMPTY;
    grid[target_y][target_x] = Field::SNAKE;

    snake_x = target_x;
    snake_y = target_y;

    return true;
}

void reposition_pellet(Field grid[9][16], int& pellet_x, int& pellet_y)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_x(0, 15);
    std::uniform_int_distribution<std::mt19937::result_type> dist_y(0, 8);

    int rand_x = dist_x(rng);
    int rand_y = dist_y(rng);
    while(grid[rand_y][rand_x] != Field::EMPTY)
    {
        int rand_x = dist_x(rng);
        int rand_y = dist_y(rng);
    }

    grid[rand_y][rand_x] = Field::PELLET;

    pellet_x = rand_x;
    pellet_y = rand_y;
}