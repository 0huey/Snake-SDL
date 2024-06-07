#include "food.hpp"

Food::Food()
{}

void Food::Move(std::list<Coordinate> snake_pieces, Coordinate limits)
{
    std::vector<Coordinate> snake_coord(begin(snake_pieces), end(snake_pieces));
    std::vector<Coordinate> empty_coord;
    Coordinate coord;

    for (int x = 0; x < limits.x; x++)
    {
        for (int y = 0; y < limits.y; y++)
        {
            coord.x = x;
            coord.y = y;

            bool occupied = (std::find(snake_coord.begin(), snake_coord.end(), coord) != snake_coord.end());

            if (!occupied)
            {
                empty_coord.push_back(coord);
            }
        }
    }

    if (empty_coord.size() == 0)
    {
        return;
    }

    std::srand((unsigned int)std::time(nullptr));

    int random = std::rand() % empty_coord.size();

    m_location = empty_coord[random];

    DEBUG_PRINT("placed food at " << m_location.x << " " << m_location.y)
}

Coordinate Food::GetLocation()
{
    return m_location;
}
