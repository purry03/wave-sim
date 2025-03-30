#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Renderer
{
private:
    const char* m_title;
    int m_height;
    int m_width;
    int m_fps;
    SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
    bool m_running;
    bool m_closeRequested;

    void set_pixel(const int x, const int y, const Uint32 pixel) const;

public:
    Renderer(const char* title, const int height, const int width, const int fps);
    ~Renderer();

    bool isLive() const;
    int initialize();
    void draw() const;
    void handle_input();
    void circle(const int x, const int y, const int radius) const;
};

#endif // RENDERER_H
