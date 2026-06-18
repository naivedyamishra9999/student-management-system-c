#include <stdio.h>      // input-output functions ke liye
#include <stdlib.h>     // malloc, free ke liye
#include <string.h>     // strcpy, strcmp ke liye

// Structure definition
struct Student {
    int id;                 // student ID store karega
    char name[50];          // student ka naam store karega
    float marks;            // student ke marks
    char specialization[50]; // student ka specialization store karega
    struct Student* next;   // next node ka address store karega
};

struct Student* head = NULL;   // linked list ka starting pointer (initially empty)

// Duplicate ID check
int isDuplicate(int id) {
    struct Student* temp = head;   // start se check karenge

    while (temp != NULL) {         
        if (temp->id == id)       
            return 1;    // agar duplicate milta hai to 1 return karega   
        temp = temp->next;         
    }
    return 0;                      
}

// Insert student
void insert() {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student)); 

    printf("Enter ID: ");
    scanf("%d", &newNode->id);// ID input le rahe hain

    if (isDuplicate(newNode->id)) {// duplicate check kar rahe hain
        printf("ID already exists!\n");// agar duplicate milta hai to error message print karenge
        free(newNode);// memory free karenge
        return;// function se return karenge
    }

    // buffer clear (VERY IMPORTANT)
    while (getchar() != '\n');

    printf("Enter Name: ");
    scanf(" %[^\n]", newNode->name); // full name allow karega (space ke sath)

    printf("Enter Marks: ");
    if (scanf("%f", &newNode->marks) != 1) {// input validation
        printf("Invalid input! Marks set to 0.\n");
        newNode->marks = 0;
    }

    while (getchar() != '\n'); // buffer clear

    printf("Enter Specialization: ");
    scanf(" %[^\n]", newNode->specialization); // full specialization allow karega

    newNode->next = head;
    head = newNode;

    printf("Student added successfully!\n");
}

//pop(delete from head)
void pop() {
    if (head == NULL) {
        printf("No records to delete.\n");
        return;
    }

    struct Student* temp = head;

    head = head->next;
    free(temp);

    printf("Last student record deleted successfully.\n");
}

//peek(see the top record)
void peek() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("ID: %d | Name: %s | Marks: %.2f | Spec: %s\n",
           head->id, head->name, head->marks, head->specialization);
}

// Display students
void display() {
    struct Student* temp = head;

    if (temp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (temp != NULL) {
        printf("ID: %d | Name: %s | Marks: %.2f | Spec: %s\n",
               temp->id, temp->name, temp->marks, temp->specialization);
        temp = temp->next;
    }
}

// Search student by ID
void search() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    struct Student* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("Found: %s (Marks: %.2f | Spec: %s)\n",
                   temp->name, temp->marks, temp->specialization);
            return;
        }
        temp = temp->next;
    }

    printf("Student not found.\n");
}

// Search by specialization
void searchBySpecialization() {
    char spec[50];
    int found = 0;

    while (getchar() != '\n'); // buffer clear

    printf("Enter Specialization to search: ");
    scanf(" %[^\n]", spec);

    struct Student* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->specialization, spec) == 0) {
            printf("ID: %d | Name: %s | Marks: %.2f | Spec: %s\n",
                   temp->id, temp->name, temp->marks, temp->specialization);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No students found with this specialization.\n");
    }
}

// Update student
void updateStudent() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    struct Student* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {

            while (getchar() != '\n');

            printf("Enter new name: ");
            scanf(" %[^\n]", temp->name);

            printf("Enter new marks: ");
            scanf("%f", &temp->marks);

            while (getchar() != '\n');

            printf("Enter new specialization: ");
            scanf(" %[^\n]", temp->specialization);

            printf("Record updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Student not found.\n");
}

// Delete student
void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    struct Student *temp = head, *prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("Deleted successfully.\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Deleted successfully.\n");
}

// Highest & Lowest marks
void highestLowest() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    struct Student *temp = head;
    struct Student *max = head, *min = head;

    while (temp != NULL) {
        if (temp->marks > max->marks)
            max = temp;

        if (temp->marks < min->marks)
            min = temp;

        temp = temp->next;
    }

    printf("Topper: %s (%.2f)\n", max->name, max->marks);
    printf("Lowest: %s (%.2f)\n", min->name, min->marks);
}

// Count students
void countStudents() {
    int count = 0;
    struct Student* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("Total Students: %d\n", count);
}

// Average marks
void averageMarks() {
    float sum = 0;
    int count = 0;
    struct Student* temp = head;

    while (temp != NULL) {
        sum += temp->marks;
        count++;
        temp = temp->next;
    }

    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("Average Marks: %.2f\n", sum / count);
}

//bubble sort for sorting students by marks
void sort() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    struct Student *temp1;
    int swapped;

    do {
        swapped = 0;
        temp1 = head;

        while (temp1->next != NULL) {
            if (temp1->marks < temp1->next->marks) {
                int idTemp = temp1->id;
                char nameTemp[50];
                char specTemp[50];
                float marksTemp = temp1->marks;

                strcpy(nameTemp, temp1->name);
                strcpy(specTemp, temp1->specialization);

                temp1->id = temp1->next->id;
                strcpy(temp1->name, temp1->next->name);
                strcpy(temp1->specialization, temp1->next->specialization);
                temp1->marks = temp1->next->marks;

                temp1->next->id = idTemp;
                strcpy(temp1->next->name, nameTemp);
                strcpy(temp1->next->specialization, specTemp);
                temp1->next->marks = marksTemp;

                swapped = 1;
            }
            temp1 = temp1->next;
        }
    } while (swapped);

    printf("Students sorted by marks in descending order.\n");
}

//alfabetical sort by name
void bubblesort() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    struct Student *temp1;
    int swapped;

    do {
        swapped = 0;
        temp1 = head;

        while (temp1->next != NULL) {
            if (strcmp(temp1->name, temp1->next->name) > 0) {
                int idTemp = temp1->id;
                char nameTemp[50];
                char specTemp[50];
                float marksTemp = temp1->marks;

                strcpy(nameTemp, temp1->name);
                strcpy(specTemp, temp1->specialization);

                temp1->id = temp1->next->id;
                strcpy(temp1->name, temp1->next->name);
                strcpy(temp1->specialization, temp1->next->specialization);
                temp1->marks = temp1->next->marks;

                temp1->next->id = idTemp;
                strcpy(temp1->next->name, nameTemp);
                strcpy(temp1->next->specialization, specTemp);
                temp1->next->marks = marksTemp;

                swapped = 1;
            }
            temp1 = temp1->next;
        }
    } while (swapped);

    printf("Students sorted by name in alphabetical order.\n");
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n1.Insert\n2.Display\n3.Search by ID\n4.Update\n5.Delete\n6.Sort by Marks\n7.Highest/Lowest\n8.Count\n9.Average\n10.Sort by Name\n11.Pop\n12.Peek\n13.Search by Specialization\n14.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sort(); break;
            case 7: highestLowest(); break;
            case 8: countStudents(); break;
            case 9: averageMarks(); break;
            case 10: bubblesort(); break;
            case 11: pop(); break;
            case 12: peek(); break;
            case 13: searchBySpecialization(); break;
            case 14: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}