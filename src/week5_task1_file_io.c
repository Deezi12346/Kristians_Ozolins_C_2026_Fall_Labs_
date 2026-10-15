// week5_task1_file_io.c
// Name: Kristians  Surname: Ozolins  Student ID: 251RDC075
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];
    int line_count = 0;

    // Use the file name from the command line if provided.
    if (argc > 1) {
        filename = argv[1];
    }

    // Open the file for writing.
    printf("Writing lines to %s...\n", filename);
    fp = fopen(filename, "w");

    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // Write two lines to the file.
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");

    if (fclose(fp) != 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // Open the file again for reading.
    fp = fopen(filename, "r");

    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    printf("Reading contents:\n");

    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
        line_count = line_count + 1;
    }

    if (fclose(fp) != 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    printf("Lines read: %d\n", line_count);

    return EXIT_SUCCESS;
}