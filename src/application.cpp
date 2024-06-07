
#include "application.hpp"

Application::Application()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    m_window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_screen_width,
        m_screen_height,
        SDL_WINDOW_SHOWN);

    m_surface = SDL_GetWindowSurface(m_window);

    m_coordinate_limit.x = m_screen_width / m_piece_size;
    m_coordinate_limit.y = m_screen_height / m_piece_size;

    m_food.Move(m_snake.GetPieces(), m_coordinate_limit);

    GameLoop();
}

void Application::GameLoop()
{
    SDL_Event event;

    while (true)
    {
        bool event_returned = (bool)SDL_PollEvent(&event);

        if (event_returned)
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    HandleKeyPress(event.key);
                    break;

                case SDL_QUIT:
                    return;
            }
        }
        else if (!m_game_paused && m_snake.IsAlive())
        {
            bool snake_moved = m_snake.Move();
            if (snake_moved)
            {
                CheckCollision();
                UpdateScreen();
            }
            SDL_Delay(1000/60);
        }
        else
        {
            SDL_Delay(1000/60);
        }
    }
}

void Application::UpdateScreen()
{
    SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0x10, 0x10, 0x10));

    SDL_Rect rect;
    rect.w = m_piece_size;
    rect.h = m_piece_size;

    for (Coordinate coord : m_snake.GetPieces())
    {
        rect.x = coord.x * m_piece_size;
        rect.y = coord.y * m_piece_size;
        SDL_FillRect(m_surface, &rect, SDL_MapRGB(m_surface->format, 0xFF, 0xFF, 0xFF));
    }

    Coordinate food = m_food.GetLocation();
    rect.x = food.x * m_piece_size;
    rect.y = food.y * m_piece_size;
    SDL_FillRect(m_surface, &rect, SDL_MapRGB(m_surface->format, 0xFF, 0x00, 0x00));

    SDL_UpdateWindowSurface(m_window);
}

void Application::HandleKeyPress(SDL_KeyboardEvent event)
{
    switch (event.keysym.sym)
    {
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDLK_w:
        case SDLK_a:
        case SDLK_s:
        case SDLK_d:
            m_snake.UpdateDirection(event.keysym.sym);
            break;
        case SDLK_p:
            m_game_paused = !m_game_paused;
            break;
        default:
            DEBUG_PRINT("pressed other key: " << event.keysym.sym);
    }
}

void Application::CheckCollision()
{
    std::list<Coordinate> snake_pieces = m_snake.GetPieces();
    Coordinate head = m_snake.GetHead();

    if (head.x < 0 ||
        head.y < 0 ||
        head.x >= m_coordinate_limit.x ||
        head.y >= m_coordinate_limit.y)
    {
        m_snake.Die();
    }

    if (head == m_food.GetLocation())
    {
        m_snake.Eat();
        m_food.Move(snake_pieces, m_coordinate_limit);
    }

    std::list<Coordinate>::iterator iter = snake_pieces.begin();
    std::advance(iter, 1);
    bool eats_self = (std::find(iter, snake_pieces.end(), head) != snake_pieces.end());

    if (eats_self)
    {
        m_snake.Die();
    }
}
