#include "list.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

struct Point_ {
	PList coordinates;		// List of coordinates
	int dimSize;			// Dimension of Point
	int inSoFar;			// number of coordinats added to point
} POINT;



/*
	internal functions to initialize the coordinates Lists
*/
PElem CloneCoordinate(PElem Elem) { 
	int* newElem = (int *)malloc(sizeof(int));
	if (newElem) *newElem = *(int *)Elem;
	return (PElem)newElem;
}
void DestroyCoordinate(PElem ElemToDestroy) { free(ElemToDestroy); }
BOOL CompareCoordinate(PElem Elem1, PElem Elem2) { return (*(int*)Elem1 == *(int*)Elem2); }
void PrintCoordinate(PElem Elem) { printf("%d ", *(int *)Elem); }


/*
  Function: PointCreate
  Abstract:
	Creates new empty point
  Parameters:
	dimSize - the dimension of the new point
  Returns:
	pointer to the new point
*/

PPoint PointCreate(int dimSize)
{
	PPoint newPoint = (PPoint)malloc(sizeof(POINT));
	PList coordinates = ListCreate(CloneCoordinate, DestroyCoordinate, CompareCoordinate, PrintCoordinate);
	if (!newPoint || !coordinates || dimSize < 0) {
		free(newPoint);
		ListDestroy(coordinates);
		return NULL;
	}

	newPoint->dimSize = dimSize;
	newPoint->inSoFar = 0;
	newPoint->coordinates = coordinates;

	return newPoint;
}



/*
  Function: PointDestroy
  Abstract:
	Destroys point
  Parameters:
	curPoint - pointer to the point to be Destroyed
  Returns: --
*/

void PointDestroy(PPoint curPoint)
{
	if (!curPoint)
		return;

	ListDestroy(curPoint->coordinates);
	free(curPoint);
}





/*
  Function: PointAddCoordinate
  Abstract:
	Adds coordinate to a point
  Parameters:
	curPoint - pointer to the point to be added to a coordinate
	coordinate - coordinate to be added
  Returns:
	SUCCES or FAIL accordind to the result of addition 
*/

Result PointAddCoordinate(PPoint curPoint, int coordinate)
{
	if (!curPoint || curPoint->dimSize <= curPoint->inSoFar)
		return FAIL;

	Result return_val = ListAdd(curPoint->coordinates, &coordinate);
	curPoint->inSoFar += return_val;
	return return_val;
}



/*
  Function: PointGetFirstCoordinate
  Abstract:
	Gets the first coordinate of a point
  Parameters:
	curPoint - point to get the first coordinate of
  Returns:
	first coordinate of the point
*/

int PointGetFirstCoordinate(PPoint curPoint)
{
	PElem FirstElem;
	if (!curPoint || !(FirstElem = ListGetFirst(curPoint->coordinates)))
		return 0;
	else
		return *(int*)FirstElem;

}


/*
  Function: PointGetNextCoordinate
  Abstract:
	Gets the next coordinate of a point
  Parameters:
	curPoint - point to get the next coordinate of
  Returns:
	next coordinate of the point
*/

int PointGetNextCoordinate(PPoint curPoint)
{
	PElem NextElem;
	if (!curPoint || !(NextElem = ListGetNext(curPoint->coordinates)))
		return 0;
	else
		return *(int*)NextElem;

}



/*
  Function: PointPrint
  Abstract:
	Prints a point
  Parameters:
	curPoint - point to print
  Returns: --
*/

void PointPrint(PPoint curPoint)
{
	if (!curPoint)
		return;

	printf("Point Dimension: %d, Size: %d, Coordinates: ", curPoint->dimSize, curPoint->inSoFar);
	ListPrint(curPoint->coordinates);
}



/*
  Function: PointCpy
  Abstract:
	Copies a point
  Parameters:
	curPoint - point to copy
  Returns:
	a copy of the received point
*/

PPoint PointCpy(PPoint curPoint) 
{
	if (!curPoint)
		return NULL;

	PPoint newPoint = PointCreate(curPoint->dimSize);
	PList newCoordinates = ListCpy(curPoint->coordinates);
	if (!newPoint || !newCoordinates) {
		PointDestroy(newPoint);
		ListDestroy(newCoordinates);
		return NULL;
	}

	ListDestroy(newPoint->coordinates);
	newPoint->inSoFar = curPoint->inSoFar;
	newPoint->coordinates = newCoordinates;

	return newPoint;
}


/*
  Function: PointCompare
  Abstract:
	Compares two points
  Parameters:
	Point1, Point2 - points to compare
  Returns:
	TRUE if identical, FALSE is not
*/

BOOL PointCompare(PPoint Point1, PPoint Point2) 
{
	if (!Point1 || !Point2 || Point1->dimSize != Point2->dimSize ||
		Point1->inSoFar != Point2->inSoFar ||
		!ListCompare(Point1->coordinates, Point2->coordinates)) {
		return FALSE;
	}
	else
		return TRUE;	
}


/*
  Function: PointGetDimension
  Abstract:
	Gets the point dimension
  Parameters:
	curPoint - point to Get its dimension
  Returns:
	the point's dimension
*/

int PointGetDimension(PPoint curPoint)
{
	if (!curPoint)
		return -1;
	else
		return curPoint->dimSize;
}



/*
  Function: PointSquareDistance
  Abstract:
	Calculates the spuare of L2 distance between two points of the same dimension
  Parameters:
	Point1, Point2 - points to find distance between
  Returns:
	the square distance, -1 in case of failure
*/

int PointSquareDistance(PPoint Point1, PPoint Point2)
{
	if (!Point1 || !Point2 || Point1->dimSize != Point2->dimSize ||
		Point1->inSoFar != Point2->inSoFar) {
		return -1;
	}
	int Distance, tmp1, tmp2;
	tmp1 = PointGetFirstCoordinate(Point1);
	tmp2 = PointGetFirstCoordinate(Point2);
	Distance = (tmp1 - tmp2) * (tmp1 - tmp2);
	
	int i;
	for (i = 1; i < Point1->inSoFar; i++) {
		tmp1 = PointGetNextCoordinate(Point1);
		tmp2 = PointGetNextCoordinate(Point2);
		Distance += (tmp1 - tmp2) * (tmp1 - tmp2);
	}

	return Distance;
}
