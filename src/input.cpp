#include "../include/input.h"
#include "../include/renderer.h"
#include "../include/fluid.h"

void handle_input(Renderer* renderer, const Fluid* fluid)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            renderer->m_closeRequested = true;
            renderer->m_running = false;
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
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int *xMouse = nullptr, *yMouse = nullptr;
            SDL_GetGlobalMouseState(xMouse,yMouse);
            FluidAddDensity(fluid, *xMouse, *yMouse, 100);
        }
    }
}
