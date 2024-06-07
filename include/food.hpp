#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "coordinate.hpp"
#include "debug.hpp"

class Food
{
private:
    Coordinate m_location;

public:
    Food();
    Coordinate GetLocation();
    void Move(std::list<Coordinate> snake_pieces, Coordinate limits);
};
