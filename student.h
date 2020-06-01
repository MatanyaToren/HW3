/*

  File: student.h

  Abstract:

    linked list of students user functions - header file.

*/

#ifndef _STUDENT_H_
#define _STUDENT_H_

/*includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*typedefs*/
typedef struct Student_ Student, *PStudent;

 /* user functions - student */

PStudent StudentCreate(char* pName, int AGE, int ID, char* pFaculty);

void printStudent(PElem pStudent);
void destroyStudent(PElem StudentToDestroy);
BOOL compareStudents(PElem Student1, PElem Student2);
PElem cloneStudent(PElem StudentToBeCloned);

#endif
