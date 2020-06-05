#include "cluster.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

#define MINIMUM(X,Y) ((X < Y) ? X : Y)


struct Cluster_ {
	PList pointList;			// List of Points
	int dimSize;				// Dimension of Cluster
	int minDist;				// minimal distance between two points in Cluster
};



/*
	internal functions to initialize the Lists
*/

PElem ClonePoint(PElem Elem) {
	return (PElem)PointCpy((PPoint)Elem);
}

void DestroyPoint(PElem PointToDestroy) { PointDestroy((PPoint)PointToDestroy); }

BOOL ComparePoint(PElem Elem1, PElem Elem2) {
	return PointCompare((PPoint)Elem1, (PPoint)Elem2);
}

void PrintPoint(PElem Elem) { PointPrint((PPoint)Elem); }



/*
  Function: ClusterCreate
  Abstract:
	Creates new empty Cluster
  Parameters:
	dimSize - the dimension of the new Cluster
  Returns:
	pointer to the new Cluster
*/

PCluster ClusterCreate(int dimSize)
{
	PCluster newCluster = (PCluster)malloc(sizeof(struct Cluster_));
	PList pointList = ListCreate(ClonePoint, DestroyPoint, ComparePoint, PrintPoint);
	if (!newCluster || !pointList || dimSize < 0) {
		free(newCluster);
		ListDestroy(pointList);
		return NULL;
	}

	newCluster->dimSize = dimSize;
	newCluster->pointList = pointList;
	newCluster->minDist = -1;

	return newCluster;
}



/*
  Function: ClusterDestroy
  Abstract:
	Destroys Cluster
  Parameters:
	curCluster - pointer to the Cluster to be Destroyed
  Returns: --
*/

void ClusterDestroy(PCluster curCluster)
{
	if (!curCluster)
		return;

	ListDestroy(curCluster->pointList);
	free(curCluster);
}


/*
  Function: ClusterAddPoint
  Abstract:
	Adds point to the Cluster
  Parameters:
	curCluster - Cluster to add a point to
	curPoint  - point to be added
  Returns:
	SUCCES or FAIL accordind to the result of addition
*/

Result ClusterAddPoint(PCluster curCluster, PPoint curPoint)
{
	int minDist;
	if (!curCluster || !curPoint ||
		PointGetDimension(curPoint) != curCluster->dimSize ||
		!(minDist = ClusterGetMinDistance(curCluster, curPoint))) {			// if minDist is zero, the is already in the cluster
		return FAIL;
	}

	curCluster->minDist = (curCluster->minDist == -1) ? minDist : curCluster->minDist;
	curCluster->minDist = MINIMUM(minDist, curCluster->minDist);

	return ListAdd(curCluster->pointList, (PElem)curPoint);
}


/*
  Function: ClusterGetMinDistance
  Abstract:
	Finds minimal distance between a Cluster to a point
  Parameters:
	curCluster, curPoint  - Cluster and point to find minimal ditance between
  Returns:
	minimal Distance, -1 in case of failure
*/

int ClusterGetMinDistance(PCluster curCluster, PPoint curPoint)
{
	if (!curCluster || !curPoint ||
		PointGetDimension(curPoint) != curCluster->dimSize) {
		return -1;
	}

	PPoint tmpPoint = (PPoint)ListGetFirst(curCluster->pointList);
	int minDist = PointSquareDistance(tmpPoint, curPoint);
	while (( tmpPoint = (PPoint)ListGetNext(curCluster->pointList) )) {
		int tmpDist = PointSquareDistance(tmpPoint, curPoint);
		minDist = MINIMUM(minDist, tmpDist);
	}

	return minDist;
}


/*
  Function: ClusterPrint
  Abstract:
	Prints a Cluster
  Parameters:
	curCluster - Cluster to print
  Returns: --
*/

void ClusterPrint(PCluster curCluster)
{
	if (!curCluster)
		return;

	printf("Cluster's dimension: %d\n[", curCluster->dimSize);
	PPoint tmpPoint = (PPoint)ListGetFirst(curCluster->pointList);
	PointPrint(tmpPoint);
	while (( tmpPoint = (PPoint)ListGetNext(curCluster->pointList) )) {
		PointPrint(tmpPoint);
	}
	printf("]\n");
	printf("Minimum Square Distance: %d\n", curCluster->minDist);
}