#include "../include/fluid.h"
#include "../include/matplotlibcpp.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

namespace plt = matplotlibcpp;

Fluid::Fluid(const int height, const int width,const float dt,const float c,const float s,const int screen_height, const int screen_width)
    : m_height(height) , m_width(width), m_dt(dt), m_c(c), m_s(s), m_screen_height(screen_height), m_screen_width(screen_width)
{
    // Check simulation stability criteria
    if (m_dt * m_c >= m_s) {
        std::cerr << "Simulation stability criterion not met. dt*c >= s" << std::endl;
        exit(1);
    }

    // Initialize simulation arrays
    initializeArrays();

    std::cout << "Fluid initialized with a grid of size:" << m_height << " x " << m_width << std::endl;

    // Generate sierpinski carpet obstacle pattern
    const int carpet_size = m_height * 0.95;
    constexpr int level = 3; // Using direct value instead of pow(2,3) for clarity
    generate_sierpinski_carpet(m_width / 2 - carpet_size / 2, m_height / 2 - carpet_size / 2, carpet_size, level);

    // Uncomment to start plotting thread
    // m_plot_thread = std::thread(&Fluid::plot_waves, this);
}

Fluid::~Fluid() {
    if (m_plot_thread.joinable()) {
        m_plot_thread.join();
    }
}

void Fluid::initializeArrays() {
    // Resize arrays
    m_H.resize(m_height * m_width, 0.0f);
    m_V.resize(m_height * m_width, 0.0f);
    m_Wet.resize(m_height * m_width, 1.0f);
}

int Fluid::transform_idx(const int x,const int y) const {
    return y * m_width + x;
}

float Fluid::get_height(int x, int y, int x0, int y0) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return 0.0f;  // Return 0 for out-of-bounds
    }
    return m_H[transform_idx(x, y)];
}

float Fluid::get_wet(int x, int y) const {
    return m_Wet[transform_idx(x, y)];
}

float Fluid::acceleration(int x, int y, int x0, int y0) const {
    const float height0 = get_height(x0, y0, x0, y0);
    const float height1 = get_height(x, y, x0, y0);
    const float wet = get_wet(x, y);
    return wet * (height1 - height0);
}

void Fluid::step(const float halflife) {
    const float damp = pow(0.5, m_dt/halflife);
    const float c_squared_over_s_squared = pow(m_c, 2) / pow(m_s, 2);

    // Update velocities
    updateVelocities(damp, c_squared_over_s_squared);

    // Apply boundary conditions
    applyBoundaryConditions();

    // Update heights
    updateHeights();
}

void Fluid::updateVelocities(const float damp,const float c_squared_over_s_squared) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (get_wet(x, y) > 0.0f) {
                const float top = acceleration(x, y + 1, x, y);
                const float bottom = acceleration(x, y - 1, x, y);
                const float left = acceleration(x - 1, y, x, y);
                const float right = acceleration(x + 1, y, x, y);
                const float acc = c_squared_over_s_squared * (top + bottom + left + right);
                const int idx = transform_idx(x, y);
                m_V[idx] = damp * m_V[idx] + m_dt * acc;
            }
        }
    }
}

void Fluid::applyBoundaryConditions() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (x == 0 || x == m_width - 1 || y == 0 || y == m_height - 1) {
                // Apply zero velocity at boundaries
                m_V[transform_idx(x, y)] = 0.0f;
            }
        }
    }
}

void Fluid::updateHeights() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (get_wet(x, y) > 0.0f) {
                const int idx = transform_idx(x, y);
                m_H[idx] += m_dt * m_V[idx];
            }
        }
    }
}

void Fluid::generate_sierpinski_carpet(const int x,const int y,const int size,const int level) {
    if (level == 0 || size < 3) return;

    const int newSize = size / 3;

    // Create the central empty square
    for (int i = x + newSize; i < x + 2 * newSize; ++i) {
        for (int j = y + newSize; j < y + 2 * newSize; ++j) {
            m_Wet[transform_idx(i, j)] = 0.0f;
        }
    }

    // Recursively generate all 8 surrounding squares
    for (int dx = 0; dx < 3; ++dx) {
        for (int dy = 0; dy < 3; ++dy) {
            if (dx == 1 && dy == 1) continue;  // Skip the center
            generate_sierpinski_carpet(x + dx * newSize, y + dy * newSize, newSize, level - 1);
        }
    }
}

void Fluid::add_velocity(int x, int y) {
    // Convert screen coordinates to simulation coordinates
    const int scale_y = m_screen_height / m_height;
    const int scale_x = m_screen_width / m_width;
    const int sim_x = x / scale_x;
    const int sim_y = y / scale_y;

    // Add a splash pattern
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (sim_x + i >= 0 && sim_x + i < m_width &&
                sim_y + j >= 0 && sim_y + j < m_height) {
                const int r = 1 + i*i + j*j;  // Distance from center
                m_V[transform_idx(sim_x + i, sim_y + j)] = 20000.0f / r;
            }
        }
    }
}

float Fluid::constrain(const float value,const float min,const float max,const float newMin,const float newMax) {
    const float mapped = newMin + (value - min) * (newMax - newMin) / (max - min);
    return std::max(newMin, std::min(mapped, newMax));
}

void Fluid::render(const Renderer* renderer) {
    const int scale_y = m_screen_height / m_height;
    const int scale_x = m_screen_width / m_width;

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            const int idx = transform_idx(x, y);
            const float wet = m_Wet[idx];
            const float height = m_H[idx];

            const SDL_Color color = calculateColor(wet, height);
            renderer->drawRectangle(x * scale_x, y * scale_y, scale_x, scale_y, color);
        }
    }
}

SDL_Color Fluid::calculateColor(const float wet,const float height) {
    SDL_Color color = {0, 0, 0, 150};

    if (wet == 0.0f) {
        // Obstacle color
        color.r = 255;
        color.g = 255;
        color.b = 255;
    } else {
        // Water color based on height
        color.r = 45;
        color.g = 35;
        // Map height to blue intensity
        const float blue = 128.0f * (height + 1.0f);
        color.b = std::clamp(blue, 0.0f, 255.0f);
    }

    return color;
}

void Fluid::mapHeightToColor(const float height, unsigned char* r, unsigned char* g, unsigned char* b) {
    // Normalize height for color mapping (between 0 and 1)
    const float normHeight = (height - 1.0f) / (10.0f - 1.0f);

    // Blue for low heights, red for high heights
    *r = static_cast<unsigned char>(255.0f * normHeight);                // Red increases with height
    *g = static_cast<unsigned char>(std::max(0.0f, 255.0f * (1.0f - 2.0f * std::abs(normHeight - 0.5f)))); // Green peaks in middle
    *b = static_cast<unsigned char>(255.0f * (1.0f - normHeight));       // Blue decreases with height
}

void Fluid::plot_waves() {
    while (true) {
        std::vector<unsigned char> image_data(m_height * m_width * 3);  // RGB values

        // Generate height-mapped image
        for (int x = 1; x < m_height - 1; x++) {
            for (int y = 1; y < m_width - 1; y++) {
                const int idx = transform_idx(x, y);
                const float height = m_H[idx];

                // Calculate pixel color
                int pixel_idx = (x * m_height + y) * 3;
                mapHeightToColor(height,
                                 &image_data[pixel_idx],
                                 &image_data[pixel_idx + 1],
                                 &image_data[pixel_idx + 2]);
            }
        }

        // Render the image
        plt::imshow(image_data.data(), m_height, m_width, 3);
        plt::pause(0.05);  // Pause for smooth update
    }
}

