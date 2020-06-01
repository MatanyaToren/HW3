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
#include "defs.h"

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
    strcat(NewStudent->name,pName);
    NewStudent->id = ID;
    NewStudent->age = AGE;
    strcat(NewStudent->faculty,pFaculty);

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

void printStudent(PStudent pStudent){
    if (pStudent == NULL){
        return;
    }
    printf("Name: %s, Age: %d, ID: %d, Faculty: %s\n",
            pStudent->name, pStudent->age, pStudent->id, pStudent->faculty);
}

/*

  Function: destroyStudent

  Abstract:

    Destroy Student data and free memory

  Parameters:

    StudentToDestroy - pointer to student we want to destroy

  Returns: --

*/

void destroyStudent(PStudent StudentToDestroy){
    if (StudentToDestroy == NULL){
        return;
    }
    free(StudentToDestroy);
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

BOOL compareStudents(PStudent Student1, PStudent Student2){
    if (Student1 == NULL || Student2 == NULL ){
        return FALSE;
    }
    return (Student1->id == Student2->id);
}
