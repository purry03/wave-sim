#include "../include/renderer.h"  // Include the header file where the class is declared
#include <cmath>  // For pow()
#include <iostream>

Renderer::Renderer(const char* title, int height, int width, int fps)
    : m_title(title), m_height(height), m_width(width), m_fps(fps),
      m_window(nullptr), m_screenSurface(nullptr), m_running(false), m_closeRequested(false) {}

Renderer::~Renderer()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Renderer::isLive() const
{
    return m_running && !m_closeRequested;
}

int Renderer::initialize()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
        return 1;
    }
    m_window = SDL_CreateWindow(
        m_title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_height, m_width,
        SDL_WINDOW_SHOWN
    );
    if (!m_window)
    {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    m_screenSurface = SDL_GetWindowSurface(m_window);
    m_running = true;
    return 0;
}

void Renderer::draw() const
{
    SDL_UpdateWindowSurface(m_window);
    SDL_Delay(1000 / m_fps);
}

void Renderer::handle_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            m_closeRequested = true;
            m_running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP: break;
                case SDLK_DOWN: break;
                case SDLK_LEFT: break;
                case SDLK_RIGHT: break;
                default: break;
            }
        }
    }
}

void Renderer::set_pixel(int x, int y, Uint32 pixel) const
{
    auto* target_pixel = static_cast<Uint32*>(m_screenSurface->pixels
        + y * m_screenSurface->pitch
        + x * m_screenSurface->format->BytesPerPixel);
    *target_pixel = pixel;
}

void Renderer::circle(int x, int y, int radius) const
{
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            if (pow(i - x, 2) + pow(j - y, 2) <= pow(radius, 2))
            {
                set_pixel(i, j, SDL_MapRGB(m_screenSurface->format, 255, 255, 255));
            }
            else
            {
                set_pixel(i, j, SDL_MapRGB(m_screenSurface->format, 0, 0, 0));
            }
        }
    }
}
