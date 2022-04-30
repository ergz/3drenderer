#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "SDL2/SDL.h"

extern uint32_t *color_buffer;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *color_buffer_texture;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

bool initialize_window(void);
void destroy_window(void);
void draw_grid(int);
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int, int, int, int, uint32_t);
void clear_color_buffer(uint32_t);
void render_color_buffer(void);

#endif
