/*
César Guadarrama Cantú
A01364853

*/

#include <stdlib.h>
#include <stdio.h>
#include "string_functions.h"

#define LINE_SIZE 500

// Macro to matrix size
#define MATRIX_SIZE(a) (sizeof(a) / sizeof(a[0]))

void free_matrix(int **, int);
int ** init_matrix(int, int);
void free_dimensions(int *, int *);
void read_size(int *, int *, FILE *);

void generate_pgm(int ** matrix, int iteration, int columns, int rows) {

  char filename[50];
  sprintf(filename, "./build/state-%d.pgm", iteration);
  // printf("FIlENAME %s\n", filename);

  FILE *fp;
  fp = fopen(filename, "w");

  fprintf(fp, "# GAME OF LIFE - ITERATION %d...\n", iteration);
  fputs("P2\n", fp);
  fprintf(fp, "%d %d\n", columns, rows);

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *columns; j++) {
      fputs("%d", matrix[j][i]);
    }
    fputs("\n");
  }

  fclose(fp);
}

void read_content(int * columns, int * rows, FILE * file_pointer, int ** matrix) {
  int temp_int;
  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *columns; j++) {
      fscanf(file_pointer, "%d", &temp_int);
      matrix[j][i] = temp_int;
    }
  }
}

int main(int argc, char const *argv[]) {
  int *columns = malloc(sizeof(int));
  int *rows = malloc(sizeof(int));
  int iterations;
  int **matrix;
  FILE *file_pointer;

  // Check we have correct number of arguments
  if (argc != 3) {
    printf("Include initial state file path and number of iterations\n");
    exit(1);
  }

  // Open the file
  file_pointer = fopen(argv[1], "r");
  if (file_pointer == NULL) {
    printf("Error opening file %s\n", argv[1]);
    exit(1);
  }

  // Get iearations
  iterations = atoi(argv[2]);

  /* Read the file */

  // Get number of rows and stuff
  read_size(columns, rows, file_pointer);

  /* Initialize the matrix */
  matrix = init_matrix(*columns, *rows);
  // Set the content of the file to the matrix
  read_content(columns, rows, file_pointer, matrix);

  /* Start parallel calculations */

  /* Snap matrix state in a file */
  generate_pgm(matrix, 0, *columns, *rows);

  /* Free the matrix */
  free_matrix(matrix, *rows);
  free_dimensions(columns, rows);

  return 0;
}

/*
Free the memory used to store the number of columns and rows of the file
*/
void free_dimensions(int * columns, int * rows) {
  free(columns);
  free(rows);
}


/*
Init the matrix allocating memory with the values of the file
*/
int ** init_matrix(int columns, int rows) {

  int ** matrix  = (int **) malloc(sizeof(int *)*columns);

  for (int i = 0; i < columns; i++) {
    matrix[i] = (int *) malloc(sizeof(int)*rows);
  }

  return matrix;
}

/*
Free the memory allocated to store the matrix
*/
void free_matrix(int ** matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

/*
Read the size of the file indicated in the header
*/
void read_size(int * columns, int * rows, FILE * file_pointer) {
  char line[LINE_SIZE];
  int temp_columns;
  int temp_rows;

  read_line(line, LINE_SIZE, file_pointer);
  sscanf(line, "%d %d", &temp_columns, &temp_rows);

  *columns = temp_columns;
  *rows = temp_rows;
}
