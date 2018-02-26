#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

#define nl() printf("\n")
#define INTERVAL 0.1

int main() {

	screen s;
	color c;
	struct matrix *edges;
	struct matrix *identity;
	struct matrix *translate;

	c.red = 255;
	c.green = 255;
	c.blue = 255;

	identity = new_matrix(4, 4);

	translate = new_matrix(4, 4);

	translate -> m[0][0] = 1;
	translate -> m[0][1] = 0;
	translate -> m[0][2] = 0;
	translate -> m[0][3] = 100;
	translate -> m[1][0] = 0;
	translate -> m[1][1] = 1;
	translate -> m[1][2] = 0;
	translate -> m[1][3] = 100;
	translate -> m[2][0] = 0;
	translate -> m[2][1] = 0;
	translate -> m[2][2] = 1;
	translate -> m[2][3] = 0;
	translate -> m[3][0] = 0;
	translate -> m[3][1] = 0;
	translate -> m[3][2] = 0;
	translate -> m[3][3] = 1;

	ident(identity);
	printf("Printing 4x4 identity matrix:\n");
	print_matrix(identity);
	nl();

	edges = new_matrix(4, 0);
	printf("Printing empty matrix:\n");
	print_matrix(edges);
	nl();

	printf("Adding 2 points...\n");
	add_point(edges, 250, 100, 0);
	add_point(edges, 350, 150, 0);
	nl();

	printf("Printing matrix:\n");
	print_matrix(edges);
	nl();

	printf("Adding edge to matrix...\n");
	add_edge(edges, 150, 200, 0, 100, 50, 0);
	nl();

	printf("Printing matrix:\n");
	print_matrix(edges);
	nl();

	printf("Multiplying this matrix:\n");
	print_matrix(translate);
	nl();
	printf("And this one:\n");
	print_matrix(edges);
	nl();
	matrix_mult(translate, edges);
	printf("Result:\n");
	print_matrix(edges);
	nl();

	//--------------------------------------------------------------------------

	c.red = MAX_COLOR;
	c.green = MAX_COLOR;
	c.blue = MAX_COLOR / 2;

	edges = new_matrix(4, 0);

	translate -> m[0][0] = 1;
	translate -> m[0][1] = 0;
	translate -> m[0][2] = 0;
	translate -> m[0][3] = 0;
	translate -> m[1][0] = 0;
	translate -> m[1][1] = 1;
	translate -> m[1][2] = 0;
	translate -> m[1][3] = 50;
	translate -> m[2][0] = 0;
	translate -> m[2][1] = 0;
	translate -> m[2][2] = 1;
	translate -> m[2][3] = 0;
	translate -> m[3][0] = 0;
	translate -> m[3][1] = 0;
	translate -> m[3][2] = 0;
	translate -> m[3][3] = 1;

	float x, y;
	int pixels = 500;
	for(x = -3; x <= 3; x += INTERVAL){
		for(y = -3; y <= 3; y += INTERVAL){
				float z = -1 * (x * x - y * y) / 2;
				float partial_x = -1 * x / 1;
				float partial_y = 1 * y / 1;

					int col = (int)(pixels / 2 - y * 4 * pixels / 48 + x * 8 * pixels / 48);
					int dest_col = (int)(pixels / 2 - y * 4 * pixels / 48 + (x + INTERVAL) * 8 * pixels / 48);
					int row = (int)(-z * pixels / 20 + y * pixels / 16 + x * pixels / 16);
					int dest_row = (int)(-(z + partial_x * INTERVAL) * pixels / 20 + y * pixels / 16 + (x + INTERVAL) * pixels / 16);
					add_edge(edges, col, row, 0, dest_col, dest_row, 0);

					col = (int)(pixels / 2 - y * 4 * pixels / 48 + x * 8 * pixels / 48);
					dest_col = (int)(pixels / 2 - (y + INTERVAL) * 4 * pixels / 48 + x * 8 * pixels / 48);
					row = (int)(-z * pixels / 20 + y * pixels / 16 + x * pixels / 16);
					dest_row = (int)(-(z + partial_y * INTERVAL) * pixels / 20 + (y + INTERVAL) * pixels / 16 + x * pixels / 16);
					add_edge(edges, col, row, 0, dest_col, dest_row, 0);
		}
	}

	draw_lines(edges, s, c);

	int i;
	for(i = 0; i < 10; i++){
		matrix_mult(translate, edges);
		draw_lines(edges, s, c);
	}

	display(s);
	free_matrix( edges );
}
