#include "../include/renderer.h"
#include "../include/fluid.h"
#include "../include/random.h"
// #include "../include/input.h"

#include <cmath>
#include <vector>
#include <ctime>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

int circ_x = SCREEN_WIDTH / 2;
int circ_y = SCREEN_HEIGHT / 2;


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
            int xMouse = 0, yMouse = 0;
            SDL_GetGlobalMouseState(&xMouse,&yMouse);
            FluidAddDensity(fluid, xMouse, yMouse, 100);
        }
    }
}

std::vector<double> vectorFromAngle2D(double angle) {
    return {cos(angle)*6, sin(angle)*6};
}


int main()
{
    auto renderer = Renderer("Fluid Sim", SCREEN_HEIGHT, SCREEN_WIDTH, 60);
    renderer.initialize();

    auto *fluid = FluidCreate(250,0.05,0.000001, 0.00000173);


    int SCALE = 4;

    int max_density = 125, min_density = 10;
    int range = max_density - min_density + 1;

    srand(time(nullptr));  // Seed random generator

    SmoothRandom smoothRand(0.0, 360, 0.00000005);  // Slowly change between 0 and 100

    while(renderer.isLive())
    {
        handle_input(&renderer,fluid);


        int cx = int((0.5 * SCREEN_WIDTH) / SCALE);
        int cy = int((0.5 * SCREEN_HEIGHT) / SCALE);
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                FluidAddDensity(fluid, cx + i, cy + j, rand() % range + min_density);
            }
        }

        for (int i = 0; i < 2; i++) {
            float angle = smoothRand.getNextValue() * 2 * 3.14 * 2;
            std::vector<double> v = vectorFromAngle2D(angle);
            FluidAddVelocity(fluid, cx, cy, v[0], v[1]);
        }

        FluidCubeStep(fluid);
        FluidRender(fluid, &renderer, SCALE);
        renderer.draw();
    }
    return 0;
}
