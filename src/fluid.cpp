#include "../include/fluid.h"
#include  "../include/renderer.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <cmath>
#include <tuple>

#define IX(x, y) ((x) + (y) * N)


Fluid* FluidCreate(const int size, const float dt, const float diff, const float visc)
{
    auto* fluid = static_cast<Fluid*>(malloc(sizeof(Fluid)));
    fluid->m_size = size;
    fluid->m_dt = dt;
    fluid->m_diff = diff;
    fluid->m_visc = visc;

    fluid->m_s = static_cast<float*>(calloc(size * size, sizeof(float)));
    fluid->m_density = static_cast<float*>(calloc(size * size, sizeof(float)));

    fluid->m_Vx = static_cast<float*>(calloc(size * size, sizeof(float)));
    fluid->m_Vy = static_cast<float*>(calloc(size * size, sizeof(float)));

    fluid->m_Vx0 = static_cast<float*>(calloc(size * size, sizeof(float)));
    fluid->m_Vy0 = static_cast<float*>(calloc(size * size, sizeof(float)));

    return fluid;
}

void FluidDelete(Fluid* fluid)
{
    free(fluid->m_s);
    free(fluid->m_density);
    free(fluid->m_Vx);
    free(fluid->m_Vy);
    free(fluid->m_Vx0);
    free(fluid->m_Vy0);
    free(fluid);
}

void FluidAddDensity(const Fluid* fluid, const int x, const int y, const float amount)
{
    const int N = fluid->m_size;
    fluid->m_density[IX(x, y)] += amount;
}

void FluidAddVelocity(const Fluid* fluid, const int x, const int y, const float amountX, const float amountY)
{
    const int N = fluid->m_size;
    const int index = IX(x, y);

    fluid->m_Vx[index] += amountX;
    fluid->m_Vy[index] += amountY;
}

static void set_bnd(const int b, float* x, const int N)
{
    for (int i = 1; i < N - 1; i++)
    {
        x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
        x[IX(i, N-1)] = b == 2 ? -x[IX(i, N-2)] : x[IX(i, N-2)];
    }

    for (int j = 1; j < N - 1; j++)
    {
        x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
        x[IX(N-1, j)] = b == 1 ? -x[IX(N-2, j)] : x[IX(N-2, j)];
    }


    x[IX(0, 0)] = 0.5 * (x[IX(1, 0)] + x[IX(0, 1)]);
    x[IX(0, N - 1)] = 0.5 * (x[IX(1, N - 1)] + x[IX(0, N - 2)]);
    x[IX(N - 1, 0)] = 0.5 * (x[IX(N - 2, 0)] + x[IX(N - 1, 1)]);
    x[IX(N - 1, N - 1)] = 0.5 * (x[IX(N - 2, N - 1)] + x[IX(N - 1, N - 2)]);
}

static void lin_solve(const int b, float* x, const float* x0, const float a, const float c, const int iter, const int N)
{
    const float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            for (int i = 1; i < N - 1; i++)
            {
                x[IX(i, j)] =
                   (x0[IX(i, j)] +
                     a *
                       (x[IX(i + 1, j)] +
                         x[IX(i - 1, j)] +
                         x[IX(i, j + 1)] +
                         x[IX(i, j - 1)])) *
                   cRecip;
            }
        }
        set_bnd(b, x, N);
    }
}

static void diffuse(const int b, float* x, const float* x0, const float diff, const float dt, const int iter,
                    const int N)
{
    float a = dt * diff * (N - 2) * (N - 2);
    lin_solve(b, x, x0, a, 1 + 6 * a, iter, N);
}

static void project(float* velocX, float* velocY, float* p, float* div, const int iter, int N)
{
    for (int j = 1; j < N - 1; j++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            div[IX(i, j)] =
              (-0.5 *
                (velocX[IX(i + 1, j)] -
                  velocX[IX(i - 1, j)] +
                  velocY[IX(i, j + 1)] -
                  velocY[IX(i, j - 1)])) /
              N;
            p[IX(i, j)] = 0;
        }
    }
    set_bnd(0, div, N);
    set_bnd(0, p, N);
    lin_solve(0, p, div, 1, 6, iter, N);


    for (int j = 1; j < N - 1; j++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            velocX[IX(i, j)] -= 0.5 * (p[IX(i + 1, j)] - p[IX(i - 1, j)]) * N;
            velocY[IX(i, j)] -= 0.5 * (p[IX(i, j + 1)] - p[IX(i, j - 1)]) * N;
        }
    }

    set_bnd(1, velocX, N);
    set_bnd(2, velocY, N);
}

static void advect(const int b, float* d, const float* d0, const float* velocX, const float* velocY, const float dt,
                   const int N)
{
    float i0, i1, j0, j1;

    float dtx = dt * (N - 2);
    float dty = dt * (N - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, tmp3, x, y;

    float Nfloat = N - 2;
    float ifloat, jfloat;
    int i, j;

    for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++)
    {
        for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++)
        {
            tmp1 = dtx * velocX[IX(i, j)];
            tmp2 = dty * velocY[IX(i, j)];
            x = ifloat - tmp1;
            y = jfloat - tmp2;

            if (x < 0.5f) x = 0.5f;
            if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
            i0 = floorf(x);
            i1 = i0 + 1.0f;
            if (y < 0.5f) y = 0.5f;
            if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
            j0 = floorf(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;


            int i0i = i0;
            int i1i = i1;
            int j0i = j0;
            int j1i = j1;


            d[IX(i, j)] =
                s0 * (t0 * d0[IX(i0i, j0i)] + t1 * d0[IX(i0i, j1i)]) +
                s1 * (t0 * d0[IX(i1i, j0i)] + t1 * d0[IX(i1i, j1i)]);
        }
    }
    set_bnd(b, d, N);
}

void FluidCubeStep(Fluid* fluid)
{
    int N = fluid->m_size;
    float visc = fluid->m_visc;
    float diff = fluid->m_diff;
    float dt = fluid->m_dt;
    float* Vx = fluid->m_Vx;
    float* Vy = fluid->m_Vy;
    float* Vx0 = fluid->m_Vx0;
    float* Vy0 = fluid->m_Vy0;
    float* s = fluid->m_s;
    float* density = fluid->m_density;

    diffuse(1, Vx0, Vx, visc, dt, 16, N);
    diffuse(2, Vy0, Vy, visc, dt, 16, N);

    project(Vx0, Vy0, Vx, Vy, 16, N);

    advect(1, Vx, Vx0, Vx0, Vy0, dt, N);
    advect(2, Vy, Vy0, Vx0, Vy0, dt, N);

    project(Vx, Vy, Vx0, Vy0, 16, N);

    diffuse(0, s, density, diff, dt, 16, N);
    advect(0, density, s, Vx, Vy, dt, N);
}

std::tuple<int, int, int> HSBtoRGB(float h, float s, float b) {
    float r = 0, g = 0, blue = 0;

    int i = static_cast<int>(h / 60) % 6;
    float f = (h / 60) - i;
    float p = b * (1 - s);
    float q = b * (1 - f * s);
    float t = b * (1 - (1 - f) * s);

    switch (i) {
    case 0: r = b, g = t, blue = p; break;
    case 1: r = q, g = b, blue = p; break;
    case 2: r = p, g = b, blue = t; break;
    case 3: r = p, g = q, blue = b; break;
    case 4: r = t, g = p, blue = b; break;
    case 5: r = b, g = p, blue = q; break;
    }

    return {static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(blue * 255)};
}

void FluidRender(const Fluid* fluid, const Renderer* renderer, const int scale)
{
    const int N=fluid->m_size;
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            const float density = fluid->m_density[IX(i,j)];
            if (density != 0)
            {
                auto [r,g,b] = HSBtoRGB(int(density+50.0)%255,200,density);
                renderer->drawRectangle(i*scale,j*scale,scale,scale,{int(density+50.0)%255,200,density,density/5});
            }
            else
            {
                renderer->drawRectangle(i*scale,j*scale,scale,scale,{0,0,0,255});
            }
        }
    }
}