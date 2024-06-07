#pragma once

struct Coordinate
{
    int x;
    int y;

    bool operator==(Coordinate c)
    {
        if (x == c.x && y == c.y)
        {
            return true;
        }
        return false;
    }

    bool operator!=(Coordinate c)
    {
        if (x != c.x || y != c.y)
        {
            return true;
        }
        return false;
    }
};
