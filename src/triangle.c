#include "triangle.h"
#include "display.h"

void int_swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    float inv_slope_left = (float)(x1 - x0)/(float)(y1 - y0);
    float inv_slope_right = (float)(x2 - x0)/(float)(y2 - y0);
    float x_start = x0;
    float x_end = x0;

    for (int y = y0; y <= y2; y++) {
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope_right;
        x_end += inv_slope_left;
    }

}
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    float inv_slope_right = (float)(x2 - x1)/(float)(y2 - y1);
    float inv_slope_left = (float)(x2 - x0)/(float)(y2 - y0);
    float x_start = x2;
    float x_end = x2;

    for (int y = y2; y >= y0; y--) {
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope_right;
        x_end -= inv_slope_left;
    }
}


void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    // sort by y coordinates vertices y0 < y1 < y2
    // TODO(improve): the sorting the of the vertices is working fine but code looks hacky
    if (y0 > y1) {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }
    if (y1 > y2) {
        int_swap(&y1, &y2);
        int_swap(&x1, &x2);
    }
    if (y0 > y1) {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }

    if (y1 == y2) {
        // draw just a flat bottom
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // draw just a flat top
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // calcaulte the mid point of bottom/top triangle
        int my = y1;
        int mx = ((float)((x2 - x0)*(y1 - y0)) / (float)(y2 - y0)) + x0;

        // draw flat-bottom 
        fill_flat_bottom_triangle(x0, y0, x1, y1, mx, my, color);

        // draw flat-top
        fill_flat_top_triangle(x1, y1, mx, my, x2, y2, color);
    }
}
