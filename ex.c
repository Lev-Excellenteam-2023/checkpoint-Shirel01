#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h> // Include this header for using bool data type
#define NAME_LENGTH 50
#define PHONE_LENGTH 11
#define MAXSTUDENT 100000
#define LEVELS 12
#define CLASS 10
#define MAXCOURSES 10


// Define the Student struct and its typedef as before...

#define NUM_OF_DATA 15 // The number of data fields in each line
struct Student {
    char studentFirstName[50];
    char studentLastName[50];
    char phone[11];
    int grades[10];
    //int class;
    
    struct Student* next;
} typedef Student;

Student* school[LEVELS][CLASS];
// Function to parse a line and add the student to the database
void parseLine(char* line);

// Function to read from file and add data to the database
void readFromFileAndAddToDatabase(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        parseLine(line);
    }

    fclose(file);
}
void freeStudents() {
    for (int level = 0; level < LEVELS; level++) {
        for (int classNum = 0; classNum < CLASS; classNum++) {
            Student* currentStudent = school[level][classNum];
            while (currentStudent != NULL) {
                Student* temp = currentStudent;
                currentStudent = currentStudent->next;
                free(temp);
            }
        }
    }
}
// Function to add the student to the database
void add_student(int level, int class, Student*  student) {
    if (school[level-1][class-1] == NULL) {
        school[level-1][class-1] = student;
    } else {
        // Find the last node in the linked list
        Student* current = school[level-1][class-1];
        while (current->next != NULL) {
            current = current->next;
        }

        // Append the new student to the end of the list
        current->next = student;
    }
}
Student* create_student(char* first_name, char* last_name, char* phone, int* grades);
void parseLine(char* line) {
    char firstName[50] ; // Initialize with an empty string
    char lastName[50] ;  // Initialize with an empty string
    char tel[11] ; 
    int level;
    int class;
    int grades[10];
    
    if (!sscanf(line, "%s %s %s %d %d %d %d %d %d %d %d %d %d %d %d",
               firstName, lastName, tel, &level, &class, &grades[0], &grades[1], &grades[2], &grades[3],
               &grades[4], &grades[5], &grades[6], &grades[7], &grades[8], &grades[9])) {
        printf("Error parsing line: %s\n", line);
        return;
    }
    Student* new_student = create_student(firstName, lastName, tel, grades);
    
    add_student(level, class, new_student);
    }


Student* create_student(char* first_name, char* last_name, char* phone, int* grades) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    if (new_student != NULL) {
        strncpy(new_student->studentFirstName, first_name, NAME_LENGTH - 1);
        new_student->studentFirstName[NAME_LENGTH]='\0';
        strncpy(new_student->studentLastName, last_name, NAME_LENGTH - 1);
        new_student->studentLastName[NAME_LENGTH]='\0';
        strncpy(new_student->phone, phone, PHONE_LENGTH - 1);
        new_student->phone[PHONE_LENGTH]='\0';
        for (int i = 0; i < 10; i++) {
            new_student->grades[i] = grades[i];
        }
        new_student->next = NULL;
    }
    return new_student;
}
void printAllStudents() {
    for (int level = 0; level < LEVELS; ++level) {
        for (int classNum = 0; classNum < CLASS; ++classNum) {
            Student* currentStudent = school[level][classNum];
            while (currentStudent != NULL) {
                printf("Name: %s %s\n", currentStudent->studentFirstName, currentStudent->studentLastName);
                //printf("Level: %d\n", currentStudent->level);
                printf("Marks: ");
                for (int i = 0; i < 10; ++i) {
                    printf("%d ", currentStudent->grades[i]);
                }
                printf("Phone Number: %s\n", currentStudent->phone);
                
                printf("\n\n");
                currentStudent = currentStudent->next;
            }
        }
    }
}
//int main1() {
    // Example usage of readFromFileAndAddToDatabase function
  //  const char* filename = "studentswithclass.txt";
    
    //for (int i = 0; i < LEVELS; i++) {
      //  for (int j = 0; j < CLASS; j++) {
        //    school[i][j] = NULL;
        //}
    //}

    //readFromFileAndAddToDatabase(filename);
    //printAllStudents();
    //freeStudents();
   
    //return 0;

//}


void insertNewStudent(){
    char first_name[NAME_LENGTH];
    char last_name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    int level, class_num;
    int grades[10];

    printf("\n| Insert New Student |\n");
    printf("---------------------------------------------------\n");

    // Get the student's information from the user
    printf("Enter First Name: ");
    fgets(first_name, NAME_LENGTH, stdin);
    first_name[strcspn(first_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Last Name: ");
    fgets(last_name, NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Phone Number (max %d characters): ", PHONE_LENGTH - 1);
    fgets(phone, PHONE_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Level (1-12): ");
    scanf("%d", &level);
    fflush(stdin);

    printf("Enter Class Number (1-10): ");
    scanf("%d", &class_num);
    fflush(stdin);

    printf("Enter Grades for 10 Courses:\n");
    for (int i = 0; i < 10; i++) {
        printf("Course %d: ", i + 1);
        scanf("%d", &grades[i]);
        fflush(stdin);
    }

    // Create a new student object
    Student* new_student = create_student(first_name, last_name, phone, grades);

    if (new_student != NULL && level > 0 && level <= LEVELS && class_num > 0 && class_num <= CLASS) {
        // Add the new student to the appropriate class in the school data structure
        add_student(level, class_num, new_student);
        printf("\nStudent %s %s added successfully to Level %d, Class %d.\n", first_name, last_name, level, class_num);
    } else {
        printf("\nError: Failed to add the student. Please check the input.\n");
    }
}

// Function to get input for student details to be deleted
void getStudentDetailsForDelete(int* level, int* class_num, char* first_name, char* last_name) {
    printf("\n| Delete Student |\n");
    printf("---------------------------------------------------\n");

    // Get input for student details to be deleted
    printf("Enter First Name: ");
    fgets(first_name, NAME_LENGTH, stdin);
    first_name[strcspn(first_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Last Name: ");
    fgets(last_name, NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Level (1-12): ");
    scanf("%d", level);
    fflush(stdin);

    printf("Enter Class Number (1-10): ");
    scanf("%d", class_num);
    fflush(stdin);
}
// Function to delete the student from the database
bool delete_student(int level, int class_num, const char* first_name, const char* last_name) {
    if (level <= 0 || level > LEVELS || class_num <= 0 || class_num > CLASS) {
        printf("Error: Invalid level or class number.\n");
        return false;
    }

    Student* previous = NULL;
    Student* currentStudent = school[level - 1][class_num - 1];

    while (currentStudent != NULL) {
        if (strcmp(currentStudent->studentFirstName, first_name) == 0 &&
            strcmp(currentStudent->studentLastName, last_name) == 0) {
            // Found the student to delete

            if (previous == NULL) {
                // The student to delete is the first node in the linked list
                school[level - 1][class_num - 1] = currentStudent->next;
            } else {
                // The student to delete is not the first node in the linked list
                previous->next = currentStudent->next;
            }

            // Free the memory allocated for the student node
            free(currentStudent);

            printf("Student %s %s has been deleted from Level %d, Class %d.\n", first_name, last_name, level, class_num);
            return true;
        }

        previous = currentStudent;
        currentStudent = currentStudent->next;
    }

    printf("Error: Student %s %s not found in Level %d, Class %d.\n", first_name, last_name, level, class_num);
    return false;
} 

// Define the Student struct and its typedef as before...
// ...

void editStudentGrade() {
    char first_name[NAME_LENGTH];
    char last_name[NAME_LENGTH];
    int level, class_num;

    printf("\n| Edit Student Grade |\n");
    printf("----------------------------------------\n");

    // Get the student's information from the user
    printf("Enter First Name: ");
    fgets(first_name, NAME_LENGTH, stdin);
    first_name[strcspn(first_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Last Name: ");
    fgets(last_name, NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Level (1-12): ");
    scanf("%d", &level);
    fflush(stdin);

    printf("Enter Class Number (1-10): ");
    scanf("%d", &class_num);
    fflush(stdin);

    // Search for the student in the specified class
    if (level > 0 && level <= LEVELS && class_num > 0 && class_num <= CLASS) {
        Student* current = school[level - 1][class_num - 1];
        while (current != NULL) {
            if (strcmp(current->studentFirstName, first_name) == 0 && strcmp(current->studentLastName, last_name) == 0) {
                // Found the student, edit their grades
                printf("Enter New Grades for 10 Courses:\n");
                for (int i = 0; i < 10; i++) {
                    printf("New Grade for Course %d: ", i + 1);
                    scanf("%d", &current->grades[i]);
                    fflush(stdin);
                }
                printf("\nStudent %s %s grades have been updated.\n", first_name, last_name);
                return; // Exit the function after editing the student's grades
            }
            current = current->next;
        }
        printf("\nStudent %s %s not found in Level %d, Class %d.\n", first_name, last_name, level, class_num);
    } else {
        printf("\nError: Invalid Level or Class Number. Please enter valid values.\n");
    }
}

// Function to search and print student details by first name and last name


void searchStudent() {
    char first_name[50];
    char last_name[50];
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);

    int found = 0;
    for (int level = 0; level < LEVELS; level++) {
        for (int class = 0; class < CLASS; class++) {
            Student* current = school[level][class];
            while (current != NULL) {
                if (strcmp(current->studentFirstName, first_name) == 0 &&
                    strcmp(current->studentLastName, last_name) == 0) {
                    printf("Student Found:\n");
                    printf("Name: %s %s\n", current->studentFirstName, current->studentLastName);
                    printf("Level: %d\n", level + 1); // Add 1 to the level to convert from 0-based index to 1-based index
                    printf("Class: %d\n", class + 1); // Add 1 to the class to convert from 0-based index to 1-based index
                    printf("Grades: ");
                    for (int i = 0; i < 10; i++) {
                        printf("%d ", current->grades[i]);
                    }
                    printf("\n");
                    found = 1;
                    break; // Exit the loop since we found the student
                }
                current = current->next;
            }
            if (found) {
                break; // Exit the outer loop as well since we found the student
            }
        }
        if (found) {
            break; // Exit the outer loop as well since we found the student
        }
    }
    if (!found) {
        printf("Student Not Found\n");
    }
}

void swapWithMin(Student* arr[10], Student* newElement, int size, int subject) {
    for (int i = 0; i < size; i++) {
        if(arr[i]==NULL){
            arr[i]=newElement;
            return;
        }
    }
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i]->grades[subject] < arr[minIndex]->grades[subject]) {
            minIndex = i;
        }
    }

    if (arr[minIndex]->grades[subject] < newElement->grades[subject]) {
        arr[minIndex] = newElement;
    }
}

void printTopNStudentsPerCourse() {
    printf("Choose a subject (0-9) in which you want the top 10 students:\n");
    int num;
    scanf("%d", &num);
    int size = 10;

    for (int level = 0; level < LEVELS; level++) {
        Student* top_grade[size];
        for (int i = 0; i < size; i++) {
            top_grade[i] = NULL;
        }

        for (int class_num = 0; class_num < CLASS; class_num++) {
            Student* current = school[level][class_num];
            while (current != NULL) {
                swapWithMin(top_grade, current, size, num);
                current = current->next;
            }
        }

        printf("Top 10 students in Level %d for subject %d:\n", level, num);
        for (int i = 0; i < size; i++) {
            if (top_grade[i] != NULL) {
                print_details_student(top_grade[i]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
  
void printAverage() {
    int numCourses;

    printf("Enter the number of THE course: ");
    scanf("%d", &numCourses);

    if (numCourses <= 0 || numCourses > MAXCOURSES) {
        printf("Invalid number of courses. Please enter a value between 1 and %d.\n", MAXCOURSES);
        return;
    }

    for (int level = 0; level < LEVELS; level++) {
        float totalAverages[MAXCOURSES] = {0};
        int numStudentsPerCourse[MAXCOURSES] = {0};

        for (int class_num = 0; class_num < CLASS; class_num++) {
            Student* current = school[level][class_num];
            while (current != NULL) {
                int total = 0;
                for (int course = 0; course < numCourses; course++) {
                    total += current->grades[course];
                }

                for (int course = 0; course < numCourses; course++) {
                    totalAverages[course] += (float)current->grades[course] / numCourses;
                }

                numStudentsPerCourse[numCourses]++;
                current = current->next;
            }
        }

        printf("Level %d:\n", level + 1);
        for (int course = 0; course < numCourses; course++) {
            float average = totalAverages[course] / numStudentsPerCourse[course];
            printf("Average for Course %d: %.2f\n", course + 1, average);
        }
        printf("\n");
    }
}






enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

void menu() {
    const char* filename = "studentswithclass.txt";
    int level, class_num;
    char first_name[NAME_LENGTH];
    char last_name[NAME_LENGTH];
    for (int i = 0; i < LEVELS; i++) {
        for (int j = 0; j < CLASS; j++) {
            school[i][j] = NULL;
        }
    }

    readFromFileAndAddToDatabase(filename);
    
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        //fflush(stdin);
        getc(stdin);
        switch (input) {
            case Insert:
                insertNewStudent();
                break;
            case Delete:
                getStudentDetailsForDelete(&level, &class_num, first_name, last_name);
                delete_student(level, class_num, first_name, last_name);
                break;
            case Edit:
                editStudentGrade();
                break;
            case Search:
                searchStudent(first_name, last_name);
                break;
            case Showall:
                
                printAllStudents() ;
                break;
            case Top10:
                printTopNStudentsPerCourse();
                break;
            case UnderperformedStudents:
                //printUnderperformedStudents();
                break;
            case Average:
                //printAverage();
                break;
            case Export:
                //exportDatabase();
                break;
            case Exit:
                //handleClosing();
                break;
            default:
                printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                       input);
                getc(stdin);
                getc(stdin);
                break;
        }
    } while (input != Exit);
}


int main() {
    menu();
    freeStudents();
    return 0;
}
