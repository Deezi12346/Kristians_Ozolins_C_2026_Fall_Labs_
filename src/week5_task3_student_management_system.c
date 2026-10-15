// week5_task3_student_management_system.c
// Name: Kristians  Surname: Ozolins  Student ID: 251RDC075
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (keep these signatures).
int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    // Load saved student data.
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;

        if (read_line("Select an option: ",
                      input, sizeof input) != 0) {
            choice = 3;
        } else {
            char *end;
            long value = strtol(input, &end, 10);

            choice = (end != input && *end == '\0')
                     ? (int)value : 0;
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;

            case 2:
                add_student(students, &count);
                break;

            case 3:
                if (save_students(students, count) != 0) {
                    printf("Error saving data.\n");
                }

                printf("Data saved. Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Read one line from the keyboard.
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    size_t len = strcspn(buf, "\r\n");

    if (buf[len] == '\0' && len == size - 1) {
        int c;

        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    buf[len] = '\0';

    return 0;
}

// Load student records from the file.
int load_students(Student arr[], int max) {
    FILE *fp;
    char line[LINE_LEN];
    int count = 0;

    fp = fopen(DATA_FILE, "r");

    if (fp == NULL) {
        return 0;
    }

    while (count < max &&
           fgets(line, sizeof line, fp) != NULL) {

        if (sscanf(line, "%49[^,],%d,%f",
                   arr[count].name,
                   &arr[count].id,
                   &arr[count].gpa) == 3) {
            count = count + 1;
        }
    }

    fclose(fp);

    return count;
}

// Save all students to the file.
int save_students(const Student arr[], int count) {
    FILE *fp;

    fp = fopen(DATA_FILE, "w");

    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < count; i = i + 1) {
        if (fprintf(fp, "%s,%d,%.2f\n",
                    arr[i].name,
                    arr[i].id,
                    arr[i].gpa) < 0) {
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) != 0) {
        return -1;
    }

    return 0;
}

// Add a student after checking the input.
void add_student(Student arr[], int *count) {
    char name[NAME_LEN];
    char id_text[LINE_LEN];
    char gpa_text[LINE_LEN];
    char *id_end;
    char *gpa_end;
    long id_value;
    float gpa_value;
    int valid = 1;

    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    if (read_line("Enter name: ", name, sizeof name) != 0) {
        return;
    }

    if (read_line("Enter ID: ", id_text, sizeof id_text) != 0) {
        return;
    }

    if (read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
        return;
    }

    if (name[0] == '\0' || strchr(name, ',') != NULL) {
        valid = 0;
    }

    errno = 0;
    id_value = strtol(id_text, &id_end, 10);

    if (id_end == id_text || *id_end != '\0' ||
        errno == ERANGE ||
        id_value < INT_MIN || id_value > INT_MAX) {
        valid = 0;
    }

    errno = 0;
    gpa_value = strtof(gpa_text, &gpa_end);

    if (gpa_end == gpa_text || *gpa_end != '\0' ||
        errno == ERANGE ||
        !(gpa_value >= 0.0f && gpa_value <= 4.0f)) {
        valid = 0;
    }

    if (!valid) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id_value;
    arr[*count].gpa = gpa_value;

    *count = *count + 1;

    printf("Student added successfully!\n");
}

// Print all student records.
void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");

    for (int i = 0; i < count; i = i + 1) {
        printf("%-5d %-20s %.2f\n",
               arr[i].id, arr[i].name, arr[i].gpa);
    }
}