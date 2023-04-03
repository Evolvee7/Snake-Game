#include "Direction.hpp"



bool are_opposite(Direction dir1, Direction dir2)
{
    if(dir1 == Direction::DOWN && dir2 == Direction::UP)
        return true;
    if(dir1 == Direction::UP && dir2 == Direction::DOWN)
        return true;
    if(dir1 == Direction::LEFT && dir2 == Direction::RIGHT)
        return true;
    if(dir1 == Direction::RIGHT && dir2 == Direction::LEFT)
        return true;

    return false;
}