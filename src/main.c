#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "display.h"
#include "vector.h"

#define N_POINTS  (9 * 9 * 9)

vec3_t cube_points[N_POINTS];

bool is_running = false;

void setup(void)
{
	
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
	
	color_buffer_texture = SDL_CreateTexture(
		renderer, 
		SDL_PIXELFORMAT_ARGB8888, 
		SDL_TEXTUREACCESS_STREAMING, 
		WINDOW_WIDTH, WINDOW_HEIGHT);

	// start loading array of vectors

	int point_count = 0;

	for (float x = -1; x <= 1; x += .25) {
		for (float y = -1; y <= 1; y += .25) {
			for (float z = -1; z <= 1; z += .25) {
				vec3_t new_point = {.x = x, .y = y, .z = z};
				cube_points[point_count++] = new_point;
			}
		}
	} 

};

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type) {
		case SDL_QUIT: {
			is_running = false;
		} break;
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				is_running = false;
			
		} break;
	}}
};

void update(void)
{

};

void render()
{
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	SDL_RenderClear(renderer);

	draw_grid(50);
	draw_rect(100, 100, 100, 100, 0xffffdf0f);
	draw_pixel(20, 20, 0xFFFFFF00);
	render_color_buffer();
	clear_color_buffer(0xFF00000F);


	SDL_RenderPresent(renderer);
};

int main(int argc, char *argv[])
{
	is_running = initialize_window();

	setup();



	while(is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
