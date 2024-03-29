#include "display.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include <math.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

int window_width;
int window_height;

bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "error trying to initialize SDL\n");
		return false;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_width = display_mode.w * .75;
	window_height = display_mode.h * .75;

	/* create an sdl window */
	window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		window_width, window_height, 
		SDL_WINDOW_RESIZABLE
	);

	if (!window) {
		fprintf(stderr, "there was an error trying to create window");
		return false;
	}

	/* create an sdl renderer */
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "there was an error creating sdl renderer");
		return false;
	}

	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	SDL_SetWindowBordered(window, SDL_TRUE);

	return true;
}

void destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

void draw_grid(int grid_width) 
{
	for (int y = 0; y < window_height; y+=grid_width) {
		for (int x = 0; x < window_width; x+=grid_width) {
				color_buffer[(window_width * y) + x] = 0xFFFFFFFF;
		}
	}
};

// TODO(ergz): option to make the pixel "fatter"
void draw_pixel(int x, int y, uint32_t color) 
{
	if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
		color_buffer[(window_width * y) + x] = color;
	}
};

void draw_rect(int x, int y, int width, int height, uint32_t color) 
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			draw_pixel(current_x, current_y, color);
		}
	}
};


void clear_color_buffer(uint32_t color) 
{
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
};

void render_color_buffer(void)
{
	SDL_UpdateTexture(
		color_buffer_texture, 
		NULL, 
		color_buffer, 
		(int)window_width * sizeof(uint32_t));

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

};

//fdsafdsa
void draw_line(int x0, int y0, int x1, int y1, uint32_t color) 
{
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);
	
	float x_inc = delta_x / (float)longest_side_length;
	float y_inc = delta_y / (float)longest_side_length;

	float curr_x = x0;
	float curr_y = y0;

	for (int i = 0; i <= longest_side_length; i++) {
		draw_pixel(round(curr_x), round(curr_y), color);
		curr_x += x_inc;
		curr_y += y_inc;
	}

};


void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) 
{
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
};


// TODO(ergz): the points can barely be seen on the screen at the moment,
// need to make them fatter so
void draw_triangle_vertices(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	draw_pixel(x0, y0, color);
	draw_pixel(x1, y1, color);
	draw_pixel(x2, y2, color);
};

