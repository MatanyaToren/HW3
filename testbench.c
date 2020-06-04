#include "list.h"
#include "point.h"
#include "cluster.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
	PPoint x = PointCreate(5);
	for (int i = 0; i < 5; i++) {
		PointAddCoordinate(x, i);
	}

	PPoint y = PointCreate(5);
	for (int i = 0; i < 5; i++) {
		PointAddCoordinate(y, i+1);
	}

	PPoint z = PointCpy(y);

	PointPrint(x);
	PointPrint(y);
	PointPrint(z);

	PCluster cluster = ClusterCreate(5);
	Result x_result = ClusterAddPoint(cluster, x);
	Result y_result = ClusterAddPoint(cluster, y);

	printf("min distance is: %d\n", ClusterGetMinDistance(cluster, x));
	ClusterPrint(cluster);
	ClusterDestroy(cluster);

	PointDestroy(y);
	PointDestroy(x);

	return 0;
}