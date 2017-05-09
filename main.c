#include "main.h"

int main(int argc, char const *argv[]) {

  gettimeofday(&start, NULL); // Get the time of start of the program

  int *columns = malloc(sizeof(int));
  int *rows = malloc(sizeof(int));
  int iterations;
  int **matrix;
  int **temp_matrix;
  FILE *file_pointer;

  // Check we have correct number of arguments
  if (argc != 3) {
    printf("Include initial state file path and number of iterations\n");
    exit(1);
  }

  // Open the file
  file_pointer = fopen(argv[1], "r");
  if (file_pointer == NULL) {
    printf("Error opening file '%s'\n", argv[1]);
    exit(1);
  }

  // Get iterations
  iterations = atoi(argv[2]);

  // Get number of rows and stuff
  read_size(columns, rows, file_pointer);

  /* Initialize the matrix */
  matrix = init_matrix(*columns, *rows);
  temp_matrix = init_matrix(*columns, *rows);

  // Set the content of the file to the matrix
  read_content(columns, rows, file_pointer, matrix);

  // Generate image of initial state
  generate_pgm(matrix, 0, *columns, *rows);

  int count = 0;
  while (count < iterations) {
    count++;
    /* Calculations in parallel */
    #pragma omp parallel for collapse(2) shared(temp_matrix,matrix)
    for (int x = 0; x < *rows; x++) {
      for (int y = 0; y < *columns; y++) {
        int neighbours = 0;
        if (x > 0) {
          neighbours+= matrix[x-1][y];
          if (y > 0) neighbours+= matrix[x-1][y-1];
          if (y < *(rows)-1) neighbours+= matrix[x-1][y+1];
        }
        if (y > 0) neighbours+= matrix[x][y-1];
        if (x < *(rows)-1) {
          neighbours+= matrix[x+1][y];
          if (y < *(rows)-1) neighbours+= matrix[x+1][y+1];
          if (y > 0) neighbours+= matrix[x+1][y-1];
        }
        if (y < *(rows)-1) neighbours+= matrix[x][y+1];
        if (neighbours < 2) temp_matrix[x][y] = 0; // Any live cell with fewer than two live neighbours dies, as if caused by underpopulation
        if (matrix[x][y] == 1 && neighbours == 2 || matrix[x][y] == 1 && neighbours == 3) temp_matrix[x][y] = 1; // Any live cell with two or three live neighbours lives on to the next generation
        if (neighbours > 3) temp_matrix[x][y] = 0; // Any live cell with more than three live neighbours dies, as if by overpopulation
        if (neighbours == 3) temp_matrix[x][y] = 1; // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
      }
    }

    /* Snap matrix state in a file */
    generate_pgm(temp_matrix, count, *columns, *rows); // This can't be optimized in parallelism, writing the files is what slows down the programm, diabling it we can see the true difference between parallelism and normal
    /* Set the new state from temp_matrix to matrix */
    copy_matrix(temp_matrix, matrix, *columns, *rows);
  }

  /* Free the matrix */
  free_matrix(matrix, *rows);
  free_matrix(temp_matrix, *rows);
  free_dimensions(columns, rows);

  // Print the time of program end
  gettimeofday(&end, NULL);
  double delta = difftime(end.tv_sec, start.tv_sec) + ((double)end.tv_usec - (double)start.tv_usec) / 1000000.0;
  printf("Finished in : %f\n",delta);

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
– Function to copy the context of one matrix to the other –
*/
void copy_matrix(int ** origin_matrix, int ** dest_matrix, int rows, int columns) {
  #pragma omp parallel for collapse(2) shared(origin_matrix,dest_matrix)
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < columns; y++) {
      dest_matrix[x][y] = origin_matrix[x][y];
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

  fprintf(fp, "P2\n# GAME OF LIFE - ITERATION; %d\n", iteration);
  fprintf(fp, "%d %d\n1\n", columns, rows);

  for (int i = 0; i < (rows); i++) {
    for (int j = 0; j < (columns); j++) {
      fprintf(fp, "%d ", matrix[j][i]);
    }
    fputs("\n", fp);
  }
  fclose(fp);
}
