#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "mesh.h"
#include "display.h"
#include "vector.h"
#include "triangle.h"
#include "array.h"

triangle_t *triangles_to_render = NULL;

int previous_frame_time = 0;
vec3_t camera_position = {0, 0, -5};
vec3_t cube_rotation = {0, 0, 0};

float fov_factor = 750;
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

	load_cube_mesh_data();

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

vec2_t project(vec3_t point)
{
	vec2_t projected_point = {
		.x = (fov_factor * point.x) / point.z, 
		.y = (fov_factor * point.y) / point.z
	};

	return projected_point;
};

void update(void)
{
	// while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
	
	previous_frame_time = SDL_GetTicks();
	
	triangles_to_render = NULL;

	cube_rotation.y += 0.01;
	cube_rotation.x += 0.01;
	cube_rotation.z += 0.01;

	int num_faces = array_length(mesh.faces);

	for (int i = 0; i < num_faces; i++) {
		face_t mesh_face = mesh.faces[i];
		vec3_t mesh_face_vertices[3];
		mesh_face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		mesh_face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		mesh_face_vertices[2] = mesh.vertices[mesh_face.c - 1];

		triangle_t projected_triangle;

		for (int j = 0; j < 3; j++) {
			vec3_t transformed_vertex = mesh_face_vertices[j];
			transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
			transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
			// transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

			transformed_vertex.z -= camera_position.z;

			vec2_t projected_point = project(transformed_vertex);
			projected_point.x += (WINDOW_WIDTH / 2);
			projected_point.y += (WINDOW_HEIGHT / 2);

			projected_triangle.point[j] = projected_point;
		}

		array_push(triangles_to_render, projected_triangle);
	}
};

void render()
{
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	SDL_RenderClear(renderer);

	int num_triangles = array_length(triangles_to_render);

	for (int i = 0; i < num_triangles; i++) {
		triangle_t triangle = triangles_to_render[i];

		draw_triangle(
			triangle.point[0].x, triangle.point[0].y, 
			triangle.point[1].x, triangle.point[1].y,
			triangle.point[2].x, triangle.point[2].y, 0xFF00FF00);
	}

	array_free(triangles_to_render);
	render_color_buffer();
	clear_color_buffer(0xFF00000F);


	SDL_RenderPresent(renderer);
};

void free_resources(void) 
{
	array_free(mesh.faces);
	array_free(mesh.vertices);
	free(color_buffer);
}

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
	free_resources();
	return 0;
}
