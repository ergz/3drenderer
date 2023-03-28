#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDL.h"
#include "mesh.h"
#include "display.h"
#include "vector.h"
#include "triangle.h"
#include "array.h"
#include "matrix.h"


triangle_t *triangles_to_render = NULL; // struct of 3 vect2's (x, y)

int previous_frame_time = 0;
vec3_t camera_position = {0, 0, 0};

float fov_factor = 750;
bool is_running = false;

// 8 bits to represent the render options of the triangle
typedef unsigned char triangle_render_ops;

triangle_render_ops triangle_ops = ~0u;

void triangle_option_toggle_bit(triangle_render_ops *tr, int n) 
{
	*tr ^= 1UL << n;
}

void triangle_option_toggle_fill(triangle_render_ops *tr) 
{
	*tr ^= 1UL << 0;
} 

void triangle_option_toggle_wireframe(triangle_render_ops *tr) 
{
	*tr ^= 1UL << 1;
} 

void triangle_option_toggle_vertices(triangle_render_ops *tr) 
{
	*tr ^= 1UL << 2;
} 

void setup(char *filename)
{
	triangle_option_toggle_fill(&triangle_ops);
	
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
	
	color_buffer_texture = SDL_CreateTexture(
		renderer, 
		SDL_PIXELFORMAT_ARGB8888, 
		SDL_TEXTUREACCESS_STREAMING, 
		WINDOW_WIDTH, WINDOW_HEIGHT);
	
	
	// start loading array of vectors
	// load_cube_mesh_data();
	load_obj_file_data(filename);
	
	
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
            } else if (event.key.keysym.sym == SDLK_1) {
                        // Pressing "1" displays the wireframe and a small red dot for each triangle vertex
                triangle_option_toggle_bit(&triangle_ops, 1);
            } else if (event.key.keysym.sym == SDLK_2) {
                        // Pressing “2” displays only the wireframe lines
                triangle_option_toggle_fill(&triangle_ops);
            } else if (event.key.keysym.sym == SDLK_3) {
                triangle_option_toggle_vertices(&triangle_ops);
                        // Pressing “3” displays filled triangles with a solid color
            } else if (event.key.keysym.sym == SDLK_4) {
                        // Pressing “4” displays both filled triangles and wireframe lines
            } else if (event.key.keysym.sym == SDLK_c) {
                        // Pressing “c” we should enable back-face culling
            } else if (event.key.keysym.sym == SDLK_d) {
                        // Pressing “d” we should disable the back-face culling
            }
        } break;
    }
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
	
	mesh.rotation.y += 0.03;
	mesh.rotation.x += 0.008;
	// mesh.rotation.z += 0.008;
	
	// mesh.scale.x += 0.002;
	// mesh.scale.y += 0.002;
	// mesh.translation.x += 0.01;
	mesh.translation.z = 5;

	
    //printf("the value of mesh scale: %.4f\n", mesh.scale.x);
	
	mat4_t scale_matrix = mat4_create_scale(
		mesh.scale.x,
		mesh.scale.y,
		mesh.scale.z
		);
	
	mat4_t tranlate_matrix = mat4_create_translation(
		mesh.translation.x,
		mesh.translation.y,
		mesh.translation.z	
		);
	
	mat4_t rotation_matrix_X = mat4_create_rotation_x(
		mesh.rotation.x
		);
	
	mat4_t rotation_matrix_Y = mat4_create_rotation_y(
		mesh.rotation.y
		);
	
	mat4_t rotation_matrix_Z = mat4_create_rotation_z(
		mesh.rotation.z	
		);
    // print_mat4(scale_matrix);
	
	int num_faces = array_length(mesh.faces);

	
	// iterate through all of the faces
	for (int i = 0; i < num_faces; i++) {

		// get the ith face from the mesh
		// the ith mesh will contain 3 index of vertices
		face_t mesh_face = mesh.faces[i];

		// create a length 3 array of vec3's to store the vertices
		vec3_t mesh_face_vertices[3];

		// get the actual values based on the index of mesh_face from 
		// mesh.vertices at that index
		mesh_face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		mesh_face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		mesh_face_vertices[2] = mesh.vertices[mesh_face.c - 1];
		
		triangle_t projected_triangle;
		
		vec4_t transformed_vertices[3]; // array of length three of vec4's
		
		// for each of the vertices in the triangle project
		for (int j = 0; j < 3; j++) {
			vec4_t transformed_vertex = vec3_to_vec4(mesh_face_vertices[j]);
			
			// create world matrix
			mat4_t world_matrix = mat4_identity();
			world_matrix = mat4_mult_mat4(scale_matrix, world_matrix);
			world_matrix = mat4_mult_mat4(rotation_matrix_Z, world_matrix);
			world_matrix = mat4_mult_mat4(rotation_matrix_Y, world_matrix);
			world_matrix = mat4_mult_mat4(rotation_matrix_X, world_matrix);
			world_matrix = mat4_mult_mat4(tranlate_matrix, world_matrix);
			
			transformed_vertex = mat4_mult_vec4(world_matrix, transformed_vertex);

			
			transformed_vertices[j] = transformed_vertex; 
		}
		
		// check back-face culling
		vec3_t vector_a = vec4_to_vec3(transformed_vertices[0]);
		vec3_t vector_b = vec4_to_vec3(transformed_vertices[1]);
		vec3_t vector_c = vec4_to_vec3(transformed_vertices[2]);
		
		// find B-A and C-A
		vec3_t vector_ab = vec3_sub(vector_b, vector_a);
		vec3_t vector_ac = vec3_sub(vector_c, vector_a);
		
		vec3_normalize(&vector_ab);
		vec3_normalize(&vector_ac);
		
		// get normal vector
		vec3_t normal = vec3_cross_prod(vector_ab, vector_ac);
		vec3_normalize(&normal);
		
		// get vector from camera to a
		vec3_t camera_ray = vec3_sub(camera_position, vector_a);
		
		// compute the dot product between the normal and camera_ray
		float dot_normal_camera = vec3_dot(camera_ray, normal);
		
		if (dot_normal_camera >= 0) {
			
			// project to 2d
			for (int j = 0; j < 3; j++) {
				
				vec2_t projected_point = project(vec4_to_vec3(transformed_vertices[j]));
				projected_point.x += (WINDOW_WIDTH / 2);
				projected_point.y += (WINDOW_HEIGHT / 2);
				
				projected_triangle.point[j] = projected_point;
			}
			
			array_push(triangles_to_render, projected_triangle);
		}
	}
};


void render()
{
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	SDL_RenderClear(renderer);
	
	int num_triangles = array_length(triangles_to_render);
	
	for (int i = 0; i < num_triangles; i++) {
		triangle_t triangle = triangles_to_render[i];
		
		if (triangle_ops & 1) {
			draw_filled_triangle(
				triangle.point[0].x, triangle.point[0].y, 
				triangle.point[1].x, triangle.point[1].y,
				triangle.point[2].x, triangle.point[2].y, 0xFFFFFFFF
				);
		}
		
		if (triangle_ops & 1 << 1) {
			draw_triangle(
				triangle.point[0].x, triangle.point[0].y, 
				triangle.point[1].x, triangle.point[1].y,
				triangle.point[2].x, triangle.point[2].y, 0xFF00FF00
				);
		}
		
		if (triangle_ops & 1 << 2) {
			draw_triangle_vertices(
				triangle.point[0].x, triangle.point[0].y, 
				triangle.point[1].x, triangle.point[1].y,
				triangle.point[2].x, triangle.point[2].y, 0xFFFF0000
				);
		}
		
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
	
	char *filename;
	if (argc == 1) {
		printf("using default file\n");
		filename = "assets/cube.obj";
	} else {
		
		filename = argv[1];
	}
	
    is_running = initialize_window();
	
	setup(filename);
	
	
	
	while (is_running) {
		process_input();
		update();
		render();
	}
	
	destroy_window();
	free_resources();
	return 0;
}

