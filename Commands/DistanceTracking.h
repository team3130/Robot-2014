#ifndef DISTANCE_TRACKING_H
#define DISTANCE_TRACKING_H

#include "WPILib.h"

class DistanceTracking {

typedef struct SDoublePoint {
	double x;
	double y;
} SDoublePoint;

typedef struct SPointRect {
	SDoublePoint ptUL;
	SDoublePoint ptUR;
	SDoublePoint ptLR;
	SDoublePoint ptLL;
} SPointRect;

typedef struct SCoordSort {
	double	dULX;
	int		iIndex;
} SCoordSort;

private:
	double 		findTriangleHeight(const double & dSideA, const double & dSideB, const double & dTotalBase);
	double		findRectangleHeight(const SPointRect & rect);
	double		findRectangleWidth(const SPointRect & rect);
	void		SortCoords( SCoordSort * coords, int size );
	double		LawOfCosines(const double & dA, const double & dB, const double & dC);
	int 		GetMarkerData( NumberArray & coords, SPointRect * rcMarkerRects, double * dMarkerHeights=NULL, double * dMarkerWidths=NULL );
	int 		GetMarkerSizes( NumberArray & coords, double * dMarkerHeights, double * dMarkerWidths, double * dMarkerCenterX );

public:
				DistanceTracking();
	double 		GetDistanceToTarget();
	bool 		IsClosestTargetHot();
	bool		IsAimedTargetHot();
	int			countNoTable;
	int			countZeroRectangles;
	int			countTooMany;
};

#endif
