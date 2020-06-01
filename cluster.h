#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include "defs.h"
#include "point.h"

typedef struct Cluster_* PCluster;

/*Interface functions*/

PCluster ClusterCreate(int dimSize);

void ClusterDestroy(PCluster);

Result ClusterAddPoint(PCluster, PPoint);

int ClusterGetMinDistance(PCluster, PPoint);

void ClusterPrint(PCluster);

/*Auxilary functions*/

PElem ClonePoint(PElem Elem);

void DestroyPoint(PElem PointToDestroy);

BOOL ComparePoint(PElem Elem1, PElem Elem2);

void PrintPoint(PElem Elem);

#endif


