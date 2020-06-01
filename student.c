//
// Created by Shlomi Shitrit on 28/05/2020.
//

/*

  File: student.c

  Abstract:

    linked list of students user functions

*/

/* includes */
#include "student.h"

/* typedefs */
typedef struct Student_{char* name;
                        int age, id;
                        char* faculty;} Student;


/*

  Function: StudentCreate

  Abstract:

    Create a new student struct.

  Parameters: fields of Student

    pName   - Student's name
    ID - Student's ID;
    AGE - Student's age;
    pFaculty   -  Student's faculty;

  Returns:

    Pointer to head of a new Student

*/
PStudent StudentCreate(char* pName, int AGE, int ID, char* pFaculty){
    if (pName == NULL || pFaculty == NULL){
        return NULL;
    }
    /* allocating memory */
    PStudent NewStudent = (PStudent)malloc(sizeof(Student));
    if (NewStudent == NULL){
        return NULL;
    }
    NewStudent->name = (char*)malloc(strlen(pName)+1);
    if (NewStudent->name == NULL){
        free(NewStudent);
        return NULL;
    }
    NewStudent->faculty = (char*)malloc(strlen(pFaculty)+1);
    if (NewStudent->faculty == NULL){
        free(NewStudent);
        return NULL;
    }

    /* insert student data */
    strcpy(NewStudent->name,pName);
    NewStudent->id = ID;
    NewStudent->age = AGE;
    strcpy(NewStudent->faculty,pFaculty);

    return NewStudent;
}

/*

  Function: printStudent

  Abstract:

    Print Student data

  Parameters:

    pStudent - pointer to student we want to print

  Returns: --

*/

void printStudent(PElem pStudent){
    if (pStudent == NULL){
        return;
    }
    PStudent StudentToPrint = (PStudent)(pStudent);
    printf("Name: %s, Age: %d, ID: %d, Faculty: %s\n",
           StudentToPrint->name, StudentToPrint->age, StudentToPrint->id, StudentToPrint->faculty);
}

/*

  Function: destroyStudent

  Abstract:

    Destroy Student data and free memory

  Parameters:

    StudentToDestroy - pointer to student we want to destroy

  Returns: --

*/

void destroyStudent(PElem StudentToDestroy){
    if (StudentToDestroy == NULL){
        return;
    }
    PStudent StudentToFree = (PStudent)(StudentToDestroy);
    free(StudentToFree->name);
    free(StudentToFree->faculty);
    free(StudentToFree);
}

/*

  Function: compareStudents

  Abstract:

    Compare between two students by ID

  Parameters:

    Student1 - pointer to the 1st student we want to compare with
    Student2 - pointer to the 2nd student we want to compare

  Returns:

    BOOL - TRUE if identical or FALSE if not

*/

BOOL compareStudents(PElem Student1, PElem Student2){
    if (Student1 == NULL || Student2 == NULL ){
        return FALSE;
    }
    /* casting */
    PStudent Stud1 = (PStudent)(Student1);
    PStudent Stud2 = (PStudent)(Student2);
    /* comparing */
    return (Stud1->id == Stud2->id);
}

/*

  Function: cloneStudent

  Abstract:

    clone student

  Parameters:

    StudentToBeCloned - pointer to a student we want to clone

  Returns:

    ClonedStudent - a pointer to the copy of the student we gave;

*/

PElem cloneStudent(PElem StudentToBeCloned){
    if (StudentToBeCloned == NULL){
        return NULL;
    }
    /* casting */
    PStudent StudentToCopy = (PStudent)(StudentToBeCloned);

    /* allocating new memory */
    PStudent ClonedStudent = (PStudent)malloc(sizeof(Student));
    if (ClonedStudent == NULL){
        return NULL;
    }
    ClonedStudent->name = (char*)malloc(strlen(StudentToCopy->name)+1);
    if (ClonedStudent->name == NULL){
        free(ClonedStudent);
        return NULL;
    }
    ClonedStudent->faculty = (char*)malloc(strlen(StudentToCopy->faculty)+1);
    if (ClonedStudent->faculty == NULL){
        free(ClonedStudent);
        return NULL;
    }

    /* cloning */
    strcpy(ClonedStudent->name,StudentToCopy->name);
    ClonedStudent->id = StudentToCopy->id;
    ClonedStudent->age = StudentToCopy->age;
    strcpy(ClonedStudent->faculty,StudentToCopy->faculty);

    return (PElem)ClonedStudent;
}
