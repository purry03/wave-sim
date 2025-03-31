#include "../include/renderer.h"
#include  "../include/fluid.h"
#include <cmath>
#include <iostream>

Renderer::Renderer(const char* title, int height, int width, int fps)
    : m_title(title), m_height(height), m_width(width), m_fps(fps),
      m_window(nullptr), m_screenSurface(nullptr), m_running(false), m_closeRequested(false) {}

Renderer::~Renderer()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
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
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    m_screenSurface = SDL_GetWindowSurface(m_window);
    m_running = true;
    return 0;
}

void Renderer::draw() const
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(1000 / m_fps);
}


void Renderer::set_pixel(int x, int y, Uint32 pixel) const
{
    auto* target_pixel = static_cast<Uint32*>(m_screenSurface->pixels
        + y * m_screenSurface->pitch
        + x * m_screenSurface->format->BytesPerPixel);
    *target_pixel = pixel;
}

void Renderer::draw_pixel(const int x, const int y, const int r, const int g, const int b, const int a) const
{
    const auto pixel = SDL_MapRGBA(m_screenSurface->format, r, g, b, a*100);
    auto* target_pixel = static_cast<Uint32*>(m_screenSurface->pixels
        + y * m_screenSurface->pitch
        + x * m_screenSurface->format->BytesPerPixel);
    *target_pixel = pixel;
}

void Renderer::drawRectangle(int x, int y, int width, int height, SDL_Color color) const {
    // Set the drawing color
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    // Create the rectangle
    SDL_Rect rect = {x, y, width, height};

    // Fill the rectangle with the specified color
    SDL_RenderFillRect(m_renderer, &rect);
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
