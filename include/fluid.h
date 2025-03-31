#ifndef FLUID_H
#define FLUID_H

#include "renderer.h"

struct Fluid {
    int m_size;
    float m_dt;
    float m_diff;
    float m_visc;

    float* m_s;
    float* m_density;

    float* m_Vx;
    float* m_Vy;

    float* m_Vx0;
    float* m_Vy0;
};

Fluid* FluidCreate(int size, float dt, float diff, float visc);
void FluidDelete(Fluid* fluid);
void FluidAddDensity(const Fluid* fluid, int x, int y, float amount);
void FluidAddVelocity(const Fluid* fluid, int x, int y, float amountX, float amountY);
void FluidCubeStep(Fluid* fluid);
void FluidRender(const Fluid* fluid, const Renderer* renderer, const int scale);

#endif // FLUID_H