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
