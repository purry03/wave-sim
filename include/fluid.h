#ifndef FLUID_H
#define FLUID_H

#include <vector>
#include <thread>
#include "../include/renderer.h"  // Assuming this includes SDL_Color

class Fluid {
public:
    /**
    * Constructor for the Fluid class
    * @param size 2D Size of the simulaiton
    * @param dt Timestep
    * @param c Wave speed
    * @param s Wave width
    * @param screen_size 2D Size of the screen
    */
    Fluid(int height, int width, float dt, float c, float s, int screen_height, int screen_width);
    ~Fluid();

    /**
     * Step through the simulation
     * @param halflife Decay time for waves
     */
    void step(float halflife);

    /**
     * Send the current state of the sim to the render buffer
     * @param renderer Pointer to the renderer
     */
    void render(const Renderer* renderer);

    /**
     * Add velocity in a circle around to point to initiate a wave
     * @param x x coordinate on screen
     * @param y Y coordinate on screen
     */
    void add_velocity(int x, int y);

    /**
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @param size Size in pixels
     * @param level Recursion depth of the carpet
     */
    void generate_sierpinski_carpet(int x, int y, int size, int level);

private:
    // Simulation parameters
    int m_height;         // Grid height
    int m_width;        // Grid width
    float m_dt;         // Time step
    float m_c;          // Wave speed
    float m_s;          // Grid spacing
    int m_screen_width;  // Rendering screen width
    int m_screen_height;  // Rendering screen height

    // Simulation state
    std::vector<float> m_H;    // Height
    std::vector<float> m_V;    // Velocity
    std::vector<float> m_Wet;  // Wetness (obstacle map)

    std::thread m_plot_thread;

    // Helper methods
    void initializeArrays();
    int transform_idx(int x, int y) const;
    float get_height(int x, int y, int x0, int y0) const;
    float get_wet(int x, int y) const;
    float acceleration(int x, int y, int x0, int y0) const;
    float constrain(float value, float min, float max, float newMin, float newMax);

    // Simulation update methods
    void updateVelocities(float damp, float c_squared_over_s_squared);
    void applyBoundaryConditions();
    void updateHeights();

    // Visualization methods
    void plot_waves();
    SDL_Color calculateColor(float wet, float height);
    void mapHeightToColor(float height, unsigned char* r, unsigned char* g, unsigned char* b);
};

#endif // FLUID_H