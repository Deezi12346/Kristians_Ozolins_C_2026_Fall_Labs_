// week5_task4_struct_binary_io.c
// Name: Kristians  Surname: Ozolins  Student ID: 251RDC075
//
// Task 4: Save and load a struct in binary format
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (keep these signatures).
int save_student_binary(const Student *s, const char *filename);
int load_student_binary(const char *filename, Student *out);
long file_size(const char *filename);

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";
    FILE *fp;
    long text_size;
    long binary_size;

    printf("Saving student in binary format...\n");

    if (save_student_binary(&s1, bin_file) != 0) {
        printf("Error saving binary student.\n");
        return EXIT_FAILURE;
    }

    // Save the same student in text format.
    fp = fopen(txt_file, "w");

    if (fp == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }

    if (fprintf(fp, "%s %d %.2f\n",
                s1.name, s1.age, s1.gpa) < 0) {
        fclose(fp);
        printf("Error writing text file.\n");
        return EXIT_FAILURE;
    }

    if (fclose(fp) != 0) {
        printf("Error closing text file.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");

    if (load_student_binary(bin_file, &loaded) != 0) {
        printf("Error loading binary student.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);

    text_size = file_size(txt_file);
    binary_size = file_size(bin_file);

    if (text_size == -1 || binary_size == -1) {
        printf("Error getting file size.\n");
        return EXIT_FAILURE;
    }

    printf("Text file size: %ld bytes\n", text_size);
    printf("Binary file size: %ld bytes\n", binary_size);

    return EXIT_SUCCESS;
}

// Save a Student structure in binary format.
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp;
    int result;

    if (s == NULL || filename == NULL) {
        return -1;
    }

    fp = fopen(filename, "wb");

    if (fp == NULL) {
        return -1;
    }

    result = (fwrite(s, sizeof(Student), 1, fp) == 1) ? 0 : -1;

    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// Load a Student structure from a binary file.
int load_student_binary(const char *filename, Student *out) {
    FILE *fp;
    int result;

    if (filename == NULL || out == NULL) {
        return -1;
    }

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        return -1;
    }

    result = (fread(out, sizeof(Student), 1, fp) == 1) ? 0 : -1;

    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// Return the file size in bytes.
long file_size(const char *filename) {
    FILE *fp;
    long size;

    if (filename == NULL) {
        return -1;
    }

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    size = ftell(fp);

    if (fclose(fp) != 0) {
        return -1;
    }

    return size;
}