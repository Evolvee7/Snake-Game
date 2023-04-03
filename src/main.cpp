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

    render_screen(grid, renderer);

    // Infinite loop
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
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
                        if(move_snake(grid, snake_x, snake_y, Direction::UP))
                            render_screen(grid, renderer);
                        break;
                    case SDLK_DOWN:
                        if(move_snake(grid, snake_x, snake_y, Direction::DOWN))
                            render_screen(grid, renderer);
                        break;
                    case SDLK_LEFT:
                        if(move_snake(grid, snake_x, snake_y, Direction::LEFT))
                            render_screen(grid, renderer);
                        break;
                    case SDLK_RIGHT:
                        if(move_snake(grid, snake_x, snake_y, Direction::RIGHT))
                            render_screen(grid, renderer);
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
    }
    if(target_x < 0 || target_x > 15 || target_y < 0 || target_y > 8)
        return false;
    
    grid[snake_y][snake_x] = Field::EMPTY;
    grid[target_y][target_x] = Field::SNAKE;

    snake_x = target_x;
    snake_y = target_y;

    return true;
}