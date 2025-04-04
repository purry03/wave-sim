#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <string>

class Renderer {
public:
    /**
     * Constructor for the Renderer class
     * @param title Window title
     * @param height Window height
     * @param width Window width
     * @param fps Target frames per second
     */
    Renderer(const char* title, int height, int width, int fps);

    /**
     * Destructor - cleans up SDL resources
     */
    ~Renderer();

    /**
     * Initializes SDL, creates window and renderer
     * @throws std::runtime_error if initialization fails
     */
    void initialize();

    /**
     * Check if the renderer is still running and not requested to close
     * @return True if the renderer is live
     */
    bool isLive() const;

    /**
     * Signal that the renderer should close
     */
    void close();

    /**
     * Present the rendered frame and delay based on FPS
     */
    void draw() const;

    /**
     * Clear the renderer with black background
     */
    void clear() const;

    /**
     * Draw a colored rectangle
     * @param x X coordinate
     * @param y Y coordinate
     * @param width Rectangle width
     * @param height Rectangle height
     * @param color Rectangle color
     */
    void drawRectangle(int x, int y, int width, int height, SDL_Color color) const;

    /**
     * Process SDL events, including quit events
     */
    void handleEvents();

    /**
     * Set window title
     * @param title New window title
     */
    void setTitle(const char* title);

    /**
     * Set target frames per second
     * @param fps Target FPS
     */
    void setFPS(int fps);

private:
    // Window properties
    const char* m_title;
    int m_height;
    int m_width;
    int m_fps;

    // SDL objects
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    // State
    bool m_running;
    bool m_closeRequested;

    // Helper methods for initialization
    void initializeSDL();
    void createWindow();
    void createRenderer();
    void cleanup();
};

#endif // RENDERER_H
