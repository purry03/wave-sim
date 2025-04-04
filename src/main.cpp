#include "../include/renderer.h"
#include "../include/fluid.h"
#include "../include/random.h"
// #include "../include/input.h"

#include <cmath>
#include <vector>
#include <ctime>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int circ_x = SCREEN_WIDTH / 2;
int circ_y = SCREEN_HEIGHT / 2;


void handle_input(Renderer* renderer, Fluid& fluid)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            renderer->close();
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
            int xMouse = 0, yMouse = 0;
            SDL_GetMouseState(&xMouse,&yMouse);
            fluid.add_velocity(xMouse, yMouse);
        }
    }
}

int main()
{
    auto renderer = Renderer("Fluid Sim", SCREEN_HEIGHT, SCREEN_WIDTH, 240);
    renderer.initialize();

    auto fluid = Fluid(200, 1.0f / 48000.0f,2.0f, 0.001f, SCREEN_HEIGHT);

    while(renderer.isLive())
    {
        handle_input(&renderer,fluid);
        fluid.step(0.7f);
        fluid.render(&renderer);
        renderer.draw();
    }
    return 0;
}
