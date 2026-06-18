#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definition

struct Student {
    int id;
    char name[50];
    float marks;
    char specialization[50];
    struct Student* next;
};

struct Student* head = NULL;

// Helper: Clear Input Buffer

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Duplicate ID Check

int isDuplicate(int id) {
    struct Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// Insert Student (Push to Head)

void insert() {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Read ID
    printf("Enter ID: ");
    if (scanf("%d", &newNode->id) != 1) {
        printf("Invalid ID!\n");
        clearBuffer();
        free(newNode);
        return;
    }
    clearBuffer(); // clear '\n' after ID

    // Duplicate check
    if (isDuplicate(newNode->id)) { 
        printf("ID already exists! Try a different ID.\n");
        free(newNode);
        return;
    }

    // Read Name
    printf("Enter Name: ");
    if (fgets(newNode->name, sizeof(newNode->name), stdin) == NULL) {
        printf("Error reading name!\n");
        free(newNode);
        return;
    }
    // Remove trailing newline from fgets
    newNode->name[strcspn(newNode->name, "\n")] = '\0';

    // Read Marks — loop until valid float
    printf("Enter Marks: ");
    while (scanf("%f", &newNode->marks) != 1) {
        printf("Invalid input! Enter marks again: ");
        clearBuffer();
    }
    clearBuffer(); // clear '\n' after marks

    // Validate marks range
    if (newNode->marks < 0 || newNode->marks > 100) {
        printf("Warning: Marks should be between 0 and 100. Saved anyway.\n");
    }

    // Read Specialization
    printf("Enter Specialization: ");
    if (fgets(newNode->specialization, sizeof(newNode->specialization), stdin) == NULL) {
        printf("Error reading specialization!\n");
        free(newNode);
        return;
    }
    // Remove trailing newline from fgets
    newNode->specialization[strcspn(newNode->specialization, "\n")] = '\0';

    // Insert at head
    newNode->next = head;
    head = newNode;

    printf("Student added successfully!\n");
}

// Pop - Delete from Head (Stack behavior)

void pop() {
    if (head == NULL) {
        printf("No records to delete.\n");
        return;
    }

    struct Student* temp = head;
    head = head->next;
    printf("Deleted student: ID=%d | Name=%s\n", temp->id, temp->name);
    free(temp);
    printf("Last inserted student record deleted successfully.\n");
}

// Peek - View Head (Top of Stack)

void peek() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Top Record ---\n");
    printf("ID: %d | Name: %s | Marks: %.2f | Specialization: %s\n",
           head->id, head->name, head->marks, head->specialization);
}

// Display All Students

void display() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    struct Student* temp = head;
    int i = 1;
    printf("\n%-5s %-6s %-25s %-10s %-20s\n", "No.", "ID", "Name", "Marks", "Specialization");
    printf("-----------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-5d %-6d %-25s %-10.2f %-20s\n",
               i++, temp->id, temp->name, temp->marks, temp->specialization);
        temp = temp->next;
    }
    printf("-----------------------------------------------------------------------\n");
}

// Search by ID

void search() {
    int id;
    printf("Enter ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    struct Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Found: ID=%d | Name=%s | Marks=%.2f | Specialization=%s\n",
                   temp->id, temp->name, temp->marks, temp->specialization);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}

// Search by Specialization

void searchBySpecialization() {
    char spec[50];
    int found = 0;

    clearBuffer(); // safety clear before fgets
    printf("Enter Specialization to search: ");
    if (fgets(spec, sizeof(spec), stdin) == NULL) {// safety check for fgets
        printf("Error reading input!\n");// if fgets fails, we can't proceed
        return;// we return early to avoid using uninitialized data
    }
    spec[strcspn(spec, "\n")] = '\0'; // remove trailing newline

    struct Student* temp = head;
    printf("\n");
    while (temp != NULL) {
        if (strcmp(temp->specialization, spec) == 0) {// case-sensitive match
            printf("ID: %d | Name: %s | Marks: %.2f | Specialization: %s\n",// print matching record
                   temp->id, temp->name, temp->marks, temp->specialization);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No students found with specialization: %s\n", spec);
    }
}

// Update Student by ID

void updateStudent() {
    int id;
    printf("Enter ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    struct Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter new name: ");
            if (fgets(temp->name, sizeof(temp->name), stdin) == NULL) {
                printf("Error reading name!\n");
                return;
            }
            temp->name[strcspn(temp->name, "\n")] = '\0';

            printf("Enter new marks: ");
            while (scanf("%f", &temp->marks) != 1) {
                printf("Invalid! Enter marks again: ");
                clearBuffer();
            }
            clearBuffer();

            printf("Enter new specialization: ");
            if (fgets(temp->specialization, sizeof(temp->specialization), stdin) == NULL) {
                printf("Error reading specialization!\n");
                return;
            }
            temp->specialization[strcspn(temp->specialization, "\n")] = '\0';

            printf("Record updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}

// Delete Student by ID

void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    struct Student *temp = head, *prev = NULL;

    // Check if head node is the one to delete
    if (temp != NULL && temp->id == id) {
        head = temp->next;
        printf("Deleted: %s\n", temp->name);
        free(temp);
        printf("Student deleted successfully.\n");
        return;
    }

    // Traverse to find node
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    printf("Deleted: %s\n", temp->name);
    free(temp);
    printf("Student deleted successfully.\n");
}

// Highest and Lowest Marks

void highestLowest() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    struct Student *temp = head;
    struct Student *maxNode = head, *minNode = head;

    while (temp != NULL) {
        if (temp->marks > maxNode->marks) maxNode = temp;
        if (temp->marks < minNode->marks) minNode = temp;
        temp = temp->next;
    }

    printf("Topper : ID=%d | Name=%s | Marks=%.2f\n",
           maxNode->id, maxNode->name, maxNode->marks);
    printf("Lowest : ID=%d | Name=%s | Marks=%.2f\n",
           minNode->id, minNode->name, minNode->marks);
}

// Count Students

void countStudents() {
    int count = 0;
    struct Student* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total Students: %d\n", count);
}

// Average Marks

void averageMarks() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    float sum = 0;
    int count = 0;
    struct Student* temp = head;

    while (temp != NULL) {
        sum += temp->marks;
        count++;
        temp = temp->next;
    }

    printf("Average Marks: %.2f\n", sum / count);
}

// Sort by Marks - Bubble Sort (Descending)

void sortByMarks() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort.\n");
        return;
    }

    int swapped;
    struct Student* temp;

    do {
        swapped = 0;
        temp = head;

        while (temp->next != NULL) {
            if (temp->marks < temp->next->marks) {
                // Swap all data fields
                int idTemp = temp->id;
                char nameTemp[50], specTemp[50];
                float marksTemp = temp->marks;

                strcpy(nameTemp, temp->name);
                strcpy(specTemp, temp->specialization);

                temp->id = temp->next->id;
                temp->marks = temp->next->marks;
                strcpy(temp->name, temp->next->name);
                strcpy(temp->specialization, temp->next->specialization);

                temp->next->id = idTemp;
                temp->next->marks = marksTemp;
                strcpy(temp->next->name, nameTemp);
                strcpy(temp->next->specialization, specTemp);

                swapped = 1;
            }
            temp = temp->next;
        }
    } while (swapped);

    printf("Students sorted by marks (Highest to Lowest).\n");
}

// Sort by Name - Bubble Sort (A to Z)

void sortByName() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort.\n");
        return;
    }

    int swapped;
    struct Student* temp;

    do {
        swapped = 0;
        temp = head;

        while (temp->next != NULL) {
            if (strcmp(temp->name, temp->next->name) > 0) {
                int idTemp = temp->id;
                char nameTemp[50], specTemp[50];
                float marksTemp = temp->marks;

                strcpy(nameTemp, temp->name);
                strcpy(specTemp, temp->specialization);

                temp->id = temp->next->id;
                temp->marks = temp->next->marks;
                strcpy(temp->name, temp->next->name);
                strcpy(temp->specialization, temp->next->specialization);

                temp->next->id = idTemp;
                temp->next->marks = marksTemp;
                strcpy(temp->next->name, nameTemp);
                strcpy(temp->next->specialization, specTemp);

                swapped = 1;
            }
            temp = temp->next;
        }
    } while (swapped);

    printf("Students sorted by name (A to Z).\n");
}

// Free All Memory - called before exit

void freeAll() {
    struct Student* temp = head;
    while (temp != NULL) {
        struct Student* next = temp->next;
        free(temp);
        temp = next;
    }
    head = NULL;
}

// Main Function

int main() {
    int choice;

    printf("========================================\n");
    printf("     Student Management System (C)      \n");
    printf("========================================\n");

    while (1) {
        printf("\n========== MENU ==========\n");
        printf(" 1.  Insert Student\n");
        printf(" 2.  Display All\n");
        printf(" 3.  Search by ID\n");
        printf(" 4.  Update Student\n");
        printf(" 5.  Delete by ID\n");
        printf(" 6.  Sort by Marks\n");
        printf(" 7.  Highest / Lowest Marks\n");
        printf(" 8.  Count Students\n");
        printf(" 9.  Average Marks\n");
        printf(" 10. Sort by Name\n");
        printf(" 11. Pop (Delete Last Inserted)\n");
        printf(" 12. Peek (View Last Inserted)\n");
        printf(" 13. Search by Specialization\n");
        printf(" 14. Exit\n");
        printf("===========================\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer(); // clear buffer after menu choice

        switch (choice) {
            case 1:  insert(); break;
            case 2:  display(); break;
            case 3:  search(); break;
            case 4:  updateStudent(); break;
            case 5:  deleteStudent(); break;
            case 6:  sortByMarks(); break;
            case 7:  highestLowest(); break;
            case 8:  countStudents(); break;
            case 9:  averageMarks(); break;
            case 10: sortByName(); break;
            case 11: pop(); break;
            case 12: peek(); break;
            case 13: searchBySpecialization(); break;
            case 14:
                freeAll();
                printf("Exiting... All memory freed. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Enter a number between 1 and 14.\n");
        }
    }
}