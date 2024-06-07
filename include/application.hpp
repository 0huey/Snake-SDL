#include <SDL.h>
#include "snake.hpp"
#include "food.hpp"
#include "debug.hpp"
#include "coordinate.hpp"
#include "debug.hpp"

class Application
{
private:
    SDL_Window* m_window;
    SDL_Surface* m_surface;
    int m_screen_width = 640;
    int m_screen_height = 480;
    Coordinate m_coordinate_limit;
    int m_piece_size = 20;
    Snake m_snake;
    Food m_food;
    bool m_game_paused = false;

public:
    Application();

private:
    void GameLoop();
    void UpdateScreen();
    void HandleKeyPress(SDL_KeyboardEvent event);
    void CheckCollision();
};
