#ifndef DISPLAY_H
#define DISPLAY_H

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

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
void draw_line(int, int, int, int, uint32_t);
void draw_rect(int, int, int, int, uint32_t);
void clear_color_buffer(uint32_t);
void render_color_buffer(void);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif
