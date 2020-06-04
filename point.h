#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"

typedef struct Point_* PPoint;

/*Interface functions*/

PPoint PointCreate(int dimSize);

void PointDestroy(PPoint);

Result PointAddCoordinate(PPoint, int coordinate);

int PointGetFirstCoordinate(PPoint);

int PointGetNextCoordinate(PPoint);

void PointPrint(PPoint);

/*copies Point and returns pointer to the new Point*/
PPoint PointCpy(PPoint curPoint);

BOOL PointCompare(PPoint Point1, PPoint Point2);

int PointGetDimension(PPoint);

int PointSquareDistance(PPoint Point1, PPoint Point2);

/*Auxilary functions*/

PElem CloneCoordinate(PElem Elem);

void DestroyCoordinate(PElem ElemToDestroy);

BOOL CompareCoordinate(PElem Elem1, PElem Elem2);

void PrintCoordinate(PElem Elem);

#endif
