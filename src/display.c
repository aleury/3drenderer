#include "display.h"

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // Use SDL to query what is the fullscreen max. width and height
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    window_width = display_mode.w;
    window_height = display_mode.h;

    // Create an SDL window
    window =
        SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         window_width, window_height, SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Create an SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

bool in_bounds(int x, int y) {
    bool x_in_bounds = x >= 0 && x < window_width;
    bool y_in_bounds = y >= 0 && y < window_height;
    return x_in_bounds && y_in_bounds;
}

void draw_pixel(int x, int y, uint32_t color) {
    if (in_bounds(x, y)) {
        color_buffer[(window_width * y) + x] = color;
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            draw_pixel(x + i, y + j, color);
        }
    }
}

void draw_grid(void) {
    // Draw a background grid that fills the entire window.
    // Lines should be rendered at every row/col multiple of 10.
    //
    // +--+--+--+--+--+--+--+--+
    // |  |  |  |  |  |  |  |  |
    // +--+--+--+--+--+--+--+--+
    // |  |  |  |  |  |  |  |  |
    // +--+--+--+--+--+--+--+--+
    // |  |  |  |  |  |  |  |  |
    // +--+--+--+--+--+--+--+--+
    // |  |  |  |  |  |  |  |  |
    // +--+--+--+--+--+--+--+--+
    uint32_t grid_color = 0xFF333333;

    for (int y = 0; y < window_height; y += 10) {
        for (int x = 0; x < window_width; x += 10) {
            draw_pixel(x, y, grid_color);
        }
    }
}

void render_color_buffer(void) {
    // The number of bytes in a row of pixel data
    int pitch = (int)(window_width * sizeof(uint32_t));

    // Copy pixel data from the color buffer into the texture
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, pitch);

    // Copy the texture to the current rendering target
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            draw_pixel(x, y, color);
        }
    }
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
