#include "../include/renderer.h"
#include "../include/fluid.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Renderer::Renderer(const char* title, int height, int width, int fps)
    : m_title(title),
      m_height(height),
      m_width(width),
      m_fps(fps),
      m_window(nullptr),
      m_renderer(nullptr),
      m_running(false),
      m_closeRequested(false)
{
}

Renderer::~Renderer()
{
    cleanup();
}

void Renderer::cleanup()
{
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    SDL_Quit();
}

bool Renderer::isLive() const
{
    return m_running && !m_closeRequested;
}

void Renderer::close()
{
    m_closeRequested = true;
}

void Renderer::initialize()
{
    try {
        initializeSDL();
        createWindow();
        createRenderer();
        m_running = true;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Initialization failed: " << e.what() << std::endl;
        cleanup();
        throw;
    }
}

void Renderer::initializeSDL()
{
    // Set rendering quality
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(std::string("Could not initialize SDL2: ") + SDL_GetError());
    }
}

void Renderer::createWindow()
{
    m_window = SDL_CreateWindow(
        m_title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_height, m_width,
        SDL_WINDOW_SHOWN
    );

    if (!m_window) {
        throw std::runtime_error(std::string("Could not create window: ") + SDL_GetError());
    }
}

void Renderer::createRenderer()
{
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        throw std::runtime_error(std::string("Could not create renderer: ") + SDL_GetError());
    }

    // Set blend mode
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

void Renderer::clear() const
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::draw() const
{
    SDL_RenderPresent(m_renderer);
    SDL_Delay(1000 / m_fps);
}

void Renderer::drawRectangle(int x, int y, int width, int height, SDL_Color color) const
{
    // Set the drawing color
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    // Create the rectangle
    SDL_Rect rect = {x, y, width, height};

    // Fill the rectangle with the specified color
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_closeRequested = true;
                break;

            // Add more event handlers as needed

            default:
                break;
        }
    }
}

void Renderer::setTitle(const char* title)
{
    m_title = title;
    if (m_window) {
        SDL_SetWindowTitle(m_window, title);
    }
}

void Renderer::setFPS(int fps)
{
    m_fps = fps;
}