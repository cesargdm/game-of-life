/*
GAME OF LIFE

César Guadarrama Cantú
cesargdm@icloud.com
A01364853

Some code borrowed from Gilberto Echeverria
gilecheverria@yahoo.com
*/

#include <stdlib.h>
#include <stdio.h>
#include "string_functions.h"
#include <omp.h>

#define LINE_SIZE 500

void free_matrix(int **, int);
int ** init_matrix(int, int);
void free_dimensions(int *, int *);
void read_size(int *, int *, FILE *);
void read_content(int *, int *, FILE *, int **);
void generate_pgm(int **, int, int, int);

int main(int argc, char const *argv[]) {
  int *columns = malloc(sizeof(int));
  int *rows = malloc(sizeof(int));
  int iterations;
  int **matrix;
  FILE *file_pointer;

  /*
  #pragma omp parallel default(none), private(i), shared(a, b) {
    #pragma omp for
    for (i=0; i<SIZE; i++) {
        a[i] = i+1 * 1;
        b[i] = i+1 * 2;
        printf("%d  [%d]  [%d]\n", i, a[i], b[i]);
    }
  }
  */

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

  // Get number of rows and stuff
  read_size(columns, rows, file_pointer);

  /* Initialize the matrix */
  matrix = init_matrix(*columns, *rows);
  // Set the content of the file to the matrix
  read_content(columns, rows, file_pointer, matrix);

  /* Start parallel calculations */

  /*

  */

  // for columns
    // for rows
      //matrix[i][j] = 0 || 1 if matrix[i+1][j+1] == 0 && if matrix[i][j+1] == 0

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

/*
– Function to read the context of a txt initial state file and store it on a matrix –
*/
void read_content(int * columns, int * rows, FILE * file_pointer, int ** matrix) {
  int temp_int;
  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *columns; j++) {
      fscanf(file_pointer, "%d", &temp_int);
      matrix[j][i] = temp_int;
    }
  }
}

/*
– Function to generate a pgm file from matrix –
The files are stored in ./build
Recieves the matrix, numer of iteration, number of columns and rows of matrix
*/
void generate_pgm(int ** matrix, int iteration, int columns, int rows) {
  char filename[50];
  sprintf(filename, "./build/state-%d.pgm", iteration);

  FILE *fp;
  fp = fopen(filename, "w");

  fputs("P2\n", fp);
  fprintf(fp, "# GAME OF LIFE - ITERATION %d...\n", iteration);
  fprintf(fp, "%d %d\n", columns, rows);
  fputs("1\n", fp);

  for (int i = 0; i < (rows); i++) {
    for (int j = 0; j < (columns); j++) {
      fprintf(fp, "%d ", matrix[j][i]);
    }
    fputs("\n", fp);
  }

  fclose(fp);
}
