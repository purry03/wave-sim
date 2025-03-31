#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Renderer
{
public:
    const char* m_title;
    int m_height;
    int m_width;
    int m_fps;
    SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
    SDL_Renderer* m_renderer;
    bool m_running;
    bool m_closeRequested;

    void set_pixel(const int x, const int y, const Uint32 pixel) const;

    Renderer(const char* title, const int height, const int width, const int fps);
    ~Renderer();
    void draw_pixel(const int x, const int y, const int r, const int g, const int b, const int a) const;
    void drawRectangle(int x, int y, int width, int height, SDL_Color color) const;
    bool isLive() const;
    int initialize();
    void draw() const;
    void circle(const int x, const int y, const int radius) const;
};

#endif // RENDERER_H
