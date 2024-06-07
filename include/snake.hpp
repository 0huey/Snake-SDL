#pragma once

#include <list>
#include <SDL.h>
#include <chrono>
#include "coordinate.hpp"

class Snake
{
private:
    typedef enum
    {
        UP,
        DOWN,
        RIGHT,
        LEFT
    } Direction;

private:
    std::list<Coordinate> m_pieces;
    Direction m_direction;
    int64_t m_speed_ms;
    std::chrono::time_point<std::chrono::system_clock> m_last_move;
    bool m_eat = false;
    bool m_alive = true;

public:
    Snake();
    void UpdateDirection(SDL_Keycode key);
    bool Move();
    std::list<Coordinate> GetPieces();
    Coordinate GetHead();
    void Eat();
    void Die();
    bool IsAlive();

private:
    Coordinate CalcNewHead(Direction dir);
};
