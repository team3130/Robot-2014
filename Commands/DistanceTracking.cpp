//#include "stdafx.h"

#include "DistanceTracking.h"
#include "math.h"

// constants
const double kCalibratedHeight_px			= 100.0;
const double kCalibratedDistance_ft			= 10.0;
const double kdDistanceBetweenReference_ft	= 1.2;
const double k90DegreesInRadians			= 1.57079633;

// defines
#define MARKER_ONE				0
#define MARKER_TWO				1
#define MARKER_THREE			2
#define MARKER_FOUR				3

#define POINT_UPPER_RIGHT_X		0
#define POINT_UPPER_RIGHT_Y		1
#define POINT_UPPER_LEFT_X		2
#define POINT_UPPER_LEFT_Y		3
#define POINT_LOWER_LEFT_X		4
#define POINT_LOWER_LEFT_Y		5
#define POINT_LOWER_RIGHT_X		6
#define POINT_LOWER_RIGHT_Y		7

// constructor
DistanceTracking::DistanceTracking() {
}

double DistanceTracking::findRectangleHeight(const SPointRect & rect) 
{
	// get the average Y values for the top and bottom of the rect
	double dUpperCenterY = (rect.ptUL.y + rect.ptUR.y) / 2.0;
	double dLowerCenterY = (rect.ptLL.y + rect.ptLR.y) / 2.0;

	// calculate the height, in pixels, of the rect
	return (dUpperCenterY - dLowerCenterY);
}

double DistanceTracking::findRectangleWidth(const SPointRect & rect) 
{
	// get the average X values for the top and bottom of the rect
	double dRightCenterX = (rect.ptUR.x + rect.ptLR.x) / 2.0;
	double dLeftCenterX = (rect.ptUL.x + rect.ptLL.x) / 2.0;

	// calculate the width, in pixels, of the rect
	return (dRightCenterX - dLeftCenterX);
}

// find the height of a triangle based on the three side lengths
double DistanceTracking::findTriangleHeight(const double & dSideA, const double & dSideB, const double & dTotalBase){
	double s = (dSideA+dSideB + dTotalBase) / 2.0; //Herons area sd
	double area = sqrt(s * (s - dSideA)*(s - dSideB) * (s - dTotalBase)); // Herons area
	double height = ((2.0 * area) / dTotalBase); //area = base * height /2, thus height = 2 * area / base
	return height;
}

// sort an array of SCoordSort structs based on the x coordinate
void DistanceTracking::SortCoords( SCoordSort * coords, int size )
{
	SCoordSort temp;

    for ( int i=0; i<size; i++ )
    {
		for ( int j=i+1; j<size; j++ )
        {
			if ( coords[j].dULX < coords[i].dULX )
            {   
                temp = coords[i];
                coords[i] = coords[j];
                coords[j] = temp;
            }
        }
    }
}

double DistanceTracking::LawOfCosines(const double & dA, const double & dB, const double & dC) {
	return acos((dA * dA + dB * dB - dC * dC) / (2.0 * dA * dB));
}

void DistanceTracking::GetMarkerData( NumberArray & coords, SPointRect * prcMarkerRects, double * pdMarkerHeights /*=NULL*/ ) {

	double dUpperCenterY;
	double dLowerCenterY;

	int iSize = coords.size() / 8;

	// DriverStationLCD * pDriverStation = DriverStationLCD::GetInstance();
	// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line1, "0 = %.1lf,%.1lf", coords.get(POINT_UPPER_RIGHT_X),coords.get(POINT_UPPER_RIGHT_Y));
	// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line2, "1 = %.1lf,%.1lf", coords.get(POINT_UPPER_LEFT_X),coords.get(POINT_UPPER_LEFT_Y));
	// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line3, "2 = %.1lf,%.1lf", coords.get(POINT_LOWER_LEFT_X),coords.get(POINT_LOWER_LEFT_Y));
	// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line4, "3 = %.1lf,%.1lf", coords.get(POINT_LOWER_RIGHT_X),coords.get(POINT_LOWER_RIGHT_Y));

	SCoordSort * coordOffsets = new SCoordSort[iSize];

	for ( int i=0; i<iSize; i++ ) {
		coordOffsets[0].dULX = coords.get((i*8)+POINT_UPPER_LEFT_X); coordOffsets[i].iIndex = i*8;
	}

	SortCoords( coordOffsets, iSize );

	// iterate for all four rects
	for ( int i=0; i<iSize; i++ ) {

		prcMarkerRects[i].ptUR.x = coords.get( coordOffsets[i].iIndex + POINT_UPPER_RIGHT_X );
		prcMarkerRects[i].ptUR.y = coords.get( coordOffsets[i].iIndex + POINT_UPPER_RIGHT_Y );
		prcMarkerRects[i].ptUL.x = coords.get( coordOffsets[i].iIndex + POINT_UPPER_LEFT_X  );
		prcMarkerRects[i].ptUL.y = coords.get( coordOffsets[i].iIndex + POINT_UPPER_LEFT_Y  );
		prcMarkerRects[i].ptLL.x = coords.get( coordOffsets[i].iIndex + POINT_LOWER_LEFT_X  );
		prcMarkerRects[i].ptLL.y = coords.get( coordOffsets[i].iIndex + POINT_LOWER_LEFT_Y  );
		prcMarkerRects[i].ptLR.x = coords.get( coordOffsets[i].iIndex + POINT_LOWER_RIGHT_X );
		prcMarkerRects[i].ptLR.y = coords.get( coordOffsets[i].iIndex + POINT_LOWER_RIGHT_Y );

		if ( pdMarkerHeights ) {
			// get the average Y values for the top and bottom of the rect
			dUpperCenterY = (prcMarkerRects[i].ptUL.y + prcMarkerRects[i].ptUR.y) / 2.0;
			dLowerCenterY = (prcMarkerRects[i].ptLL.y + prcMarkerRects[i].ptLR.y) / 2.0;

			// calculate the height, in pixels, of the rect
			pdMarkerHeights[i] = dUpperCenterY - dLowerCenterY;
		}
	}

	delete coordOffsets;
	coordOffsets = NULL;
}

// get the distance to the wall on the line being aimed at
double DistanceTracking::GetDistanceToTarget() {
	
	NetworkTable * pNetworkTable		= NetworkTable::GetTable("RoboRealm");
	// DriverStationLCD * pDriverStation 	= DriverStationLCD::GetInstance();
		
	double dDistance_ft = 0.0;
	
	if ( pNetworkTable ) { // && pDriverStation ) {

		double		dMarkerHeights[4];
		SPointRect	rcMarkerRects[4];
		double		dDistanceBase_ft = 0.0;
		NumberArray coords;

		pNetworkTable->RetrieveValue("MEQ_COORDINATES", coords);
		double dImageWidth = pNetworkTable->GetNumber("IMAGE_WIDTH");

		// we need three rectangles, otherwise something is wrong with the image
		if ( coords.size() < 24 )
			return 0.0;

		// gets marker data from the coords data, sorted from left to right
		GetMarkerData( coords, rcMarkerRects, dMarkerHeights );


		// calculate the center point of the image
		double dImageCenterX = dImageWidth / 2.0;
		

		// Left Rectangle Calculations

		// calculate the distance from the camera to the center of the rect based on calibrarated data and rectangle height
		double dDistanceLeft_ft = (kCalibratedHeight_px / dMarkerHeights[MARKER_TWO]) * kCalibratedDistance_ft;
		
		// calculate the base in pixels (center of rect to the center of the image)
		double dLeftCenterX = (rcMarkerRects[MARKER_TWO].ptUR.x + rcMarkerRects[MARKER_TWO].ptUL.x) / 2.0;
		double dLeftBase = (dImageCenterX - dLeftCenterX);
	

		// Right Rectangle Calculations

		// calculate the distance from the camera to the center of the rect based on calibrarated data and rectangle height
		double dDistanceRight_ft = (kCalibratedHeight_px / dMarkerHeights[MARKER_THREE]) * kCalibratedDistance_ft;

		// calculate the base in pixels (center of rect to the center of the image)
		double dRightCenterX = (rcMarkerRects[MARKER_THREE].ptUR.x + rcMarkerRects[MARKER_THREE].ptUL.x) / 2.0;
		// double dRightBase = (dRightCenterX - dImageCenterX);


		// Distance calculations

		// calculate our triangle base length (center of left rect to center of right rect) 
		double dBaseWidth = dRightCenterX - dLeftCenterX;

		// calculate the height of our triangle
		double dHeight_ft = findTriangleHeight(dDistanceLeft_ft, dDistanceRight_ft, kdDistanceBetweenReference_ft);

		// convert left base from pixels to feet
		double dLeftBase_ft = (dLeftBase * kdDistanceBetweenReference_ft) / dBaseWidth;

		// calculate the base of the left rectangle, based on other two sides
		double dLeftTriangleBase_ft = sqrt((dDistanceLeft_ft*dDistanceLeft_ft) - (dHeight_ft*dHeight_ft));

		// calculate angle C to decide whether to add or subtract values
		double dCAngle = LawOfCosines(dBaseWidth, dDistanceLeft_ft, dDistanceRight_ft );

		// calculate the base of the distance rectangle
		if ( dCAngle > k90DegreesInRadians )
			dDistanceBase_ft = fabs(dLeftBase_ft + dLeftTriangleBase_ft);
		else
			dDistanceBase_ft = fabs(dLeftBase_ft - dLeftTriangleBase_ft);

		// calculate the distance, based on other two sides
		dDistance_ft = sqrt((dDistanceBase_ft*dDistanceBase_ft) + (dHeight_ft*dHeight_ft));
					
		// pDriverStation->PrintfLine( DriverStationLCD::kUser_Line5, "DL, DR, = %.1lf,%.1lf", dDistanceLeft_ft, dDistanceRight_ft);
		// pDriverStation->PrintfLine( DriverStationLCD::kUser_Line6, "D = %.1lf",  dDistance_ft);
		// pDriverStation->UpdateLCD();
	}
	
	return dDistance_ft;
}

bool DistanceTracking::IsClosestTargetHot() {

	NetworkTable * pNetworkTable = NetworkTable::GetTable("RoboRealm");
	
	// we'll have three rectangles.  One of the outside rectangles will be the horizontal
	// hot goal indicator.  We'll have to sort them out, and we won't make any assumptions
	// about the order sent from robo-realm.
	// lets find the widest rectangle and assume that it's the target rectangle
	
	if ( pNetworkTable ) {

		double			dMarkerHeights[3];
		SPointRect		rcMarkerRects[3];
		NumberArray		coords;
		
		pNetworkTable->RetrieveValue("MEQ_COORDINATES", coords);

		if ( coords.size() != 24 )
			return false; // todo - return value?

		// call routine to get marker heights (always returns three rect heights)
		GetMarkerData( coords, rcMarkerRects, dMarkerHeights );

		// the horizontal marker is either ONE or THREE, compare heights to see which

		// if THREE is less than ONE, THREE (right) is the hot marker, ONE and TWO are the vertical markers
		if ( dMarkerHeights[MARKER_THREE] < dMarkerHeights[MARKER_ONE] ) {

			// larger height is closer, if TWO is larger then closer to it and the hot marker
			if ( dMarkerHeights[MARKER_TWO] > dMarkerHeights[MARKER_ONE] )
				return true;
			else
				return false;

		// else ONE is hot, TWO and THREE are the vertical markers
		} else {
			// larger height is closer, if TWO is larger then closer to it and the hot marker
			if ( dMarkerHeights[MARKER_TWO] > dMarkerHeights[MARKER_THREE] )
				return true;
			else
				return false;
		}
	}
	return false;
}

bool DistanceTracking::IsAimedTargetHot() {

	NetworkTable * pNetworkTable		= NetworkTable::GetTable("RoboRealm");
	
	if ( pNetworkTable ) {

		double			dMarkerHeights[3];
		SPointRect		rcMarkerRects[4];
		NumberArray		coords;
		
		pNetworkTable->RetrieveValue("MEQ_COORDINATES", coords); // *targetNum);
		double dImageWidth = pNetworkTable->GetNumber("IMAGE_WIDTH");

		if ( coords.size() != 24 )
			return false; // todo - return value?

		double dImageCenterX = dImageWidth / 2.0;

		// call routine to get marker heights (always returns three rect heights)
		GetMarkerData( coords, rcMarkerRects, dMarkerHeights );

		// if THREE is less than ONE, THREE (right) is the hot marker, ONE and TWO are the vertical markers
		if ( dMarkerHeights[MARKER_THREE] < dMarkerHeights[MARKER_ONE] ) {

			// get distances from the image center to the inside edge of each vertical marker
			double dLeftDistance = dImageCenterX - rcMarkerRects[MARKER_ONE].ptUR.x;
			double dRightDistance = rcMarkerRects[MARKER_TWO].ptUL.x - dImageCenterX;

			// if the camera is aimed more towards the right marker
			if ( dRightDistance < dLeftDistance  )
				return true;
			else 
				return false;

		// else ONE (left) is hot, TWO and THREE are the vertical markers
		} else {

			// get distances from the image center to the inside edge of each vertical marker
			double dLeftDistance = dImageCenterX - rcMarkerRects[MARKER_TWO].ptUR.x;
			double dRightDistance = rcMarkerRects[MARKER_THREE].ptUL.x - dImageCenterX;

			// if the camera is aimed more towards the left marker
			if ( dLeftDistance < dRightDistance )
				return true;
			else 
				return false;
		}
	}
	return false;
}
