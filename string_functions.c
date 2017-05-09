#include "string_functions.h"

size_t read_line(char * string, int size, FILE * file_ptr) {
    size_t length = 0;

    if ( fgets(string, size, file_ptr) != NULL )
    {
        length = strlen(string);
        // Change the last character in the string, if it is a '\n'
        if (length < size-1 && *(string + length - 1) == '\n')
        {
            // Set it as a null character
            *(string + length - 1) = '\0';
            // Reduce the length of the string
            length--;
        }
    }
    else
    {
        perror("Unable to read string from standard input\n");
        exit(EXIT_FAILURE);
    }

    return length;
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
