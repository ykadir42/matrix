#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
int x
int y
int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
	if(points -> lastcol >= points -> cols - 1)
	grow_matrix(points, points -> cols + 1);
	points -> m[0][points -> lastcol] = x;
	points -> m[1][points -> lastcol] = y;
	points -> m[2][points -> lastcol] = z;
	points -> m[3][points -> lastcol] = 1;
	points -> lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points,
	double x0, double y0, double z0,
	double x1, double y1, double z1) {
		add_point(points, x0, y0, z0);
		add_point(points, x1, y1, z1);
	}

	/*======== void draw_lines() ==========
	Inputs:   struct matrix * points
	screen s
	color c
	Returns:
	Go through points 2 at a time and call draw_line to add that line
	to the screen
	====================*/
	void draw_lines( struct matrix * points, screen s, color c) {
		int i;
		for(i = 0; i < points -> cols; i += 2){
			draw_line((int)points -> m[0][i], (int)points -> m[1][i], (int)points -> m[0][i+1], (int)points -> m[1][i+1], s, c);
			//printf("drawing line from (%d, %d) to (%d, %d)\n", (int)points -> m[0][i], (int)points -> m[1][i], (int)points -> m[0][i+1], (int)points -> m[1][i+1]);
		}
	}

	void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

		if(x0 > x1){
			int temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
		int x = x0;
		int y = y0;
		int a = y1 - y0;
		int b = x0 - x1;

		if(a >= 0){
			if(a + b <= 0){
				int d = 2 * a + b;
				while (x <= x1){
					plot(s, c, x, y);
					if(d > 0){
						y++;
						d += 2 * b;
					}
					x++;
					d += 2 * a;
				}
			}
			else{
				int d = a + 2 * b;
				while (y <= y1){
					plot(s, c, x, y);
					if(d < 0){
						x++;
						d += 2 * a;
					}
					y++;
					d += 2 * b;
				}
			}
		}

		else{
			if(b - a <= 0){
				int d = 2 * a - b;
				while (x <= x1){
					plot(s, c, x, y);
					if(d < 0){
						y--;
						d -= 2 * b;
					}
					x++;
					d += 2 * a;
				}
			}
			else{
				int d = a - 2 * b;
				while (y >= y1){
					plot(s, c, x, y);
					if(d > 0){
						x++;
						d += 2 * a;
					}
					y--;
					d -= 2 * b;
				}
			}
		}

	} //end draw_line
