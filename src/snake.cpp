#include "snake.hpp"
#include "debug.hpp"

Snake::Snake()
{
    Coordinate head;
    head.x = 0;
    head.y = 0;
    m_pieces.push_front(head);
    head.x = 1;
    m_pieces.push_front(head);
    head.x = 2;
    m_pieces.push_front(head);

    m_direction = RIGHT;

    m_speed_ms = 150;

    m_last_move = std::chrono::system_clock::now();
}

void Snake::UpdateDirection(SDL_Keycode key)
{
    Direction new_dir;

    switch (key)
    {
        case SDLK_UP:
        case SDLK_w:
            new_dir = UP;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            new_dir = DOWN;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            new_dir = LEFT;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            new_dir = RIGHT;
            break;
        default:
            new_dir = UP;
    }

    Coordinate new_head = CalcNewHead(new_dir);

    std::list<Coordinate>::iterator iter = m_pieces.begin();
    std::advance(iter, 1);

    if (new_head != *iter)
    {
        m_direction = new_dir;
    }
}

bool Snake::Move()
{
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();
    int64_t since_move = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_move).count();

    if (since_move > m_speed_ms) {
        Coordinate new_head = CalcNewHead(m_direction);

        m_pieces.push_front(new_head);

        if (m_eat)
        {
            m_eat = false;
        }
        else
        {
            m_pieces.pop_back();
        }

        m_last_move = now;

        return true;
    }
    return false;
}

std::list<Coordinate> Snake::GetPieces()
{
    return m_pieces;
}

Coordinate Snake::GetHead()
{
    return m_pieces.front();
}

void Snake::Eat()
{
    m_eat = true;
}

Coordinate Snake::CalcNewHead(Direction dir)
{
    Coordinate new_head = GetHead();

    switch (dir)
    {
        case UP:
            new_head.y -= 1;
            break;
        case DOWN:
            new_head.y += 1;
            break;
        case LEFT:
            new_head.x -= 1;
            break;
        case RIGHT:
            new_head.x += 1;
            break;
    }

    return new_head;
}

void Snake::Die()
{
    m_alive = false;
}

bool Snake::IsAlive()
{
    return m_alive;
}
