#include "../include/renderer.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int circ_x = SCREEN_WIDTH / 2;
int circ_y = SCREEN_HEIGHT / 2;


int main()
{
    auto renderer = Renderer("FluidSim", SCREEN_HEIGHT, SCREEN_WIDTH, 30);
    renderer.initialize();
    while(renderer.isLive())
    {
        renderer.handle_input();
        renderer.circle(circ_x, circ_y, 150);
        renderer.draw();
    }

    return 0;
}
