#include "display.h"
#include <assert.h>

bool is_running = false;

int window_width = 800;
int window_height = 600;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

void setup(void) {
    // Allocate the require memory in bytes to hold the color buffer
    color_buffer =
        (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
    assert(color_buffer);

    // Create an SDL Texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             window_width, window_height);
    assert(color_buffer_texture);
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}

void update(void) {
    // TODO:
}

void render(void) {
    // Set background color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid();

    draw_rect(300, 200, 300, 150, 0xFFFF00FF);

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    // Display the backbuffer
    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
