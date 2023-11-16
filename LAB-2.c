#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNumber;
    char name[50];
    float marks;
    struct Student *next;
};

struct Student *createStudent(int rollNumber, const char *name, float marks) {
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    
    if (newStudent == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newStudent->rollNumber = rollNumber;
    strncpy(newStudent->name, name, sizeof(newStudent->name));
    newStudent->marks = marks;
    newStudent->next = NULL;

    return newStudent;
}

struct Student *insertAtBeginning(struct Student *head, int rollNumber, const char *name, float marks) {
    struct Student *newStudent = createStudent(rollNumber, name, marks);
    newStudent->next = head;
    return newStudent;
}

struct Student *insertAtEnd(struct Student *head, int rollNumber, const char *name, float marks) {
    struct Student *newStudent = createStudent(rollNumber, name, marks);

    if (head == NULL) {
        return newStudent;
    }

    struct Student *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newStudent;
    return head;
}

struct Student *deleteStudent(struct Student *head, int rollNumber) {
    struct Student *current = head;
    struct Student *prev = NULL;

    while (current != NULL && current->rollNumber != rollNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with Roll Number %d not found\n", rollNumber);
        return head;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Student with Roll Number %d deleted successfully\n", rollNumber);
    return head;
}

struct Student *searchStudent(struct Student *head, int rollNumber) {
    struct Student *current = head;

    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            return current;
        }
        current = current->next;
    }

    return NULL; 
}

void displayStudents(struct Student *head) {
    struct Student *current = head;

    if (current == NULL) {
        printf("Student list is empty\n");
        return;
    }

    printf("Student List:\n");
    while (current != NULL) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", current->rollNumber, current->name, current->marks);
        current = current->next;
    }
}

void freeList(struct Student *head) {
    struct Student *current = head;
    struct Student *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Student *head = NULL;
    int choice, rollNumber;
    char name[50];
    float marks;

    do {
        printf("\nMenu:\n");
        printf("1. Insert Student at the Beginning\n");
        printf("2. Insert Student at the End\n");
        printf("3. Delete Student\n");
        printf("4. Search Student\n");
        printf("5. Display Students\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll Number, Name, and Marks: ");
                scanf("%d %s %f", &rollNumber, name, &marks);
                head = insertAtBeginning(head, rollNumber, name, marks);
                break;

            case 2:
                printf("Enter Roll Number, Name, and Marks: ");
                scanf("%d %s %f", &rollNumber, name, &marks);
                head = insertAtEnd(head, rollNumber, name, marks);
                break;

            case 3:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                head = deleteStudent(head, rollNumber);
                break;

            case 4:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNumber);
                struct Student *searchResult = searchStudent(head, rollNumber);
                if (searchResult != NULL) {
                    printf("Student found: Roll Number: %d, Name: %s, Marks: %.2f\n", searchResult->rollNumber, searchResult->name, searchResult->marks);
                } else {
                    printf("Student with Roll Number %d not found\n", rollNumber);
                }
                break;

            case 5:
                displayStudents(head);
                break;

            case 6:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    freeList(head);

    return 0;
}
