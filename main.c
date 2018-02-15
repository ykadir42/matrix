#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;
  struct matrix *identity;

  c.red = 255;
  c.green = 255;
  c.blue = 255;

  identity = new_matrix(4, 4);
  

  ident(identity);
  print_matrix(identity);

  edges = new_matrix(4, 0);
  print_matrix(edges);

  add_point(edges, 250, 250, 0);
  add_point(edges, 350, 350, 0);




  print_matrix(edges);
  
  draw_lines(edges, s, c);
  display(s);
  free_matrix( edges );
}
