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

int DistanceTracking::GetMarkerData( NumberArray & coords, SPointRect * rcMarkerRects, double * dMarkerHeights /*=NULL*/, double * dMarkerWidths /*=NULL*/ ) {

	try 
	{
		double dUpperCenterY;
		double dLowerCenterY;
		double dLeftCenterX;
		double dRightCenterX;

		int iNumRects = coords.size() / 8;
	
		// can't handle zer or anything greater than 4
		if (( iNumRects <= 0 ) || ( iNumRects > 4 ))
			return 0;

		// DriverStationLCD * pDriverStation = DriverStationLCD::GetInstance();
		// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line1, "0 = %.1lf,%.1lf", coords.get(POINT_UPPER_RIGHT_X),coords.get(POINT_UPPER_RIGHT_Y));
		// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line2, "1 = %.1lf,%.1lf", coords.get(POINT_UPPER_LEFT_X),coords.get(POINT_UPPER_LEFT_Y));
		// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line3, "2 = %.1lf,%.1lf", coords.get(POINT_LOWER_LEFT_X),coords.get(POINT_LOWER_LEFT_Y));
		// pDriverStation->PrintfLine(DriverStationLCD::kUser_Line4, "3 = %.1lf,%.1lf", coords.get(POINT_LOWER_RIGHT_X),coords.get(POINT_LOWER_RIGHT_Y));

		SCoordSort * coordOffsets = new SCoordSort[iNumRects];

		for ( int i=0; i<iNumRects; i++ ) {
			coordOffsets[i].dULX = coords.get((i*8)+POINT_UPPER_LEFT_X); coordOffsets[i].iIndex = i*8;
		}

		SortCoords( coordOffsets, iNumRects );

		// iterate for all four rects
		for ( int i=0; i<iNumRects; i++ ) {

			rcMarkerRects[i].ptUR.x = coords.get( coordOffsets[i].iIndex + POINT_UPPER_RIGHT_X );
			rcMarkerRects[i].ptUR.y = coords.get( coordOffsets[i].iIndex + POINT_UPPER_RIGHT_Y );
			rcMarkerRects[i].ptUL.x = coords.get( coordOffsets[i].iIndex + POINT_UPPER_LEFT_X  );
			rcMarkerRects[i].ptUL.y = coords.get( coordOffsets[i].iIndex + POINT_UPPER_LEFT_Y  );
			rcMarkerRects[i].ptLL.x = coords.get( coordOffsets[i].iIndex + POINT_LOWER_LEFT_X  );
			rcMarkerRects[i].ptLL.y = coords.get( coordOffsets[i].iIndex + POINT_LOWER_LEFT_Y  );
			rcMarkerRects[i].ptLR.x = coords.get( coordOffsets[i].iIndex + POINT_LOWER_RIGHT_X );
			rcMarkerRects[i].ptLR.y = coords.get( coordOffsets[i].iIndex + POINT_LOWER_RIGHT_Y );

			if ( dMarkerHeights ) {
				// get the average Y values for the top and bottom of the rect
				dUpperCenterY = (rcMarkerRects[i].ptUL.y + rcMarkerRects[i].ptUR.y) / 2.0;
				dLowerCenterY = (rcMarkerRects[i].ptLL.y + rcMarkerRects[i].ptLR.y) / 2.0;

				// calculate the height, in pixels, of the rect
				dMarkerHeights[i] = dUpperCenterY - dLowerCenterY;
			}

			if ( dMarkerWidths ) {
				// get the average X values for the top and bottom of the rect
				dLeftCenterX = (rcMarkerRects[i].ptUL.x + rcMarkerRects[i].ptLL.x) / 2.0;
				dRightCenterX = (rcMarkerRects[i].ptUR.x + rcMarkerRects[i].ptLR.x) / 2.0;

				// calculate the height, in pixels, of the rect
				dMarkerWidths[i] = dRightCenterX - dLeftCenterX;
			}
		}

		delete coordOffsets;
		coordOffsets = NULL;
	
		return iNumRects;
	}
	catch(...)
	{
	}
	return 0;
}

int DistanceTracking::GetMarkerSizes( NumberArray & coords, double * dMarkerHeights, double * dMarkerWidths, double * dMarkerCenterX ) {

	try 
	{
		int iNumRects = coords.size() / 8;
	
		// can't handle zer or anything greater than 4
		if (( iNumRects <= 0 ) || ( iNumRects > 4 ))
			return 0;

		double dMinX = 100000;
		double dMaxX = -1;
		double dMinY = 100000;
		double dMaxY = -1;
		
		// iterate for all four rects
		for ( int i=0; i<iNumRects; i++ ) {			
			for ( int j=0; j<4; j++ ) {
				dMinX = min( dMinX, coords.get( 8*i + j*2 ));
				dMaxX = max( dMaxX, coords.get( 8*i + j*2 ));	
				dMinY = min( dMinY, coords.get( 8*i + j*2 + 1));
				dMaxY = max( dMaxY, coords.get( 8*i + j*2 + 1));
			}
			dMarkerWidths[i] = dMaxX - dMinX;
			dMarkerHeights[i] = dMaxY - dMinY;
			dMarkerCenterX[i] = (dMinX + dMaxX) / 2.0;
		}
		return iNumRects;
	}
	catch(...)
	{
	}
	return 0;
}

// get the distance to the wall on the line being aimed at
double DistanceTracking::GetDistanceToTarget() {

	try
	{
		NetworkTable * pNetworkTable		= NetworkTable::GetTable("RoboRealm");
		// DriverStationLCD * pDriverStation 	= DriverStationLCD::GetInstance();
		
		double dDistance_ft = 0.0;
	
		if ( pNetworkTable && pNetworkTable->IsConnected()) {
	
			if ( !pNetworkTable->ContainsKey("MEQ_COORDINATES") ||
				 !pNetworkTable->ContainsKey("IMAGE_WIDTH")) {
				return 0.0;
			}

			double		dMarkerHeights[4];
			double		dMarkerWidths[4];
			SPointRect	rcMarkerRects[4];
			double		dDistanceBase_ft = 0.0;
			NumberArray coords;

			pNetworkTable->RetrieveValue("MEQ_COORDINATES", coords);
			double dImageWidth = pNetworkTable->GetNumber("IMAGE_WIDTH");

			// gets marker data from the coords data, sorted from left to right
			int iNumRects = GetMarkerData( coords, rcMarkerRects, dMarkerHeights, dMarkerWidths );

			if (( iNumRects < 2 ) || ( iNumRects > 4 ))
				return 0.0;

			int iLeftVerticalMarker=MARKER_ONE;

			// two rects.  Could be...
			//
			// - a vertical and a horizontal rectangle
			// - two vertical rectangles - clipping off the horizontal rects on both side
			if ( iNumRects == 2 ) {
				// need to figure out which of the above we're dealing with
				// we should be able to tell if one is vertical and the other is horizontal
				// by the fact that one rect is wider than the other but also shorter than
				// the other

				// one rect is wider and shorter than the other - must be a mix of H & V rects
				if ((( dMarkerHeights[MARKER_ONE] < dMarkerHeights[MARKER_TWO] ) &&
					 ( dMarkerWidths[MARKER_ONE]  > dMarkerWidths[MARKER_TWO] )) ||					
					(( dMarkerHeights[MARKER_TWO] < dMarkerHeights[MARKER_ONE] ) &&
					 ( dMarkerWidths[MARKER_TWO]  > dMarkerWidths[MARKER_ONE] )))
				{		
					// this is the upside down L shape case, need to figure out how to calculate distance
					return 0.0; // TODO
				} else {
					// two verticals - code below will work
					iLeftVerticalMarker = MARKER_ONE;
				}
			}

			else if ( iNumRects == 3 ) {

				// one of the horizontal rects is cut off

				// three is shorter, assume its a horizontal marker
				if ( dMarkerHeights[MARKER_THREE] < dMarkerHeights[MARKER_ONE] ) {

					iLeftVerticalMarker = MARKER_ONE;

				// one is shorter, assume its a horizontal marker
				} else {

					iLeftVerticalMarker = MARKER_TWO;

				}
			}

			else if ( iNumRects == 4 ) {

				iLeftVerticalMarker = MARKER_TWO;
			}

			int iRightVerticalMarker = iLeftVerticalMarker + 1;

			// calculate the center point of the image
			double dImageCenterX = dImageWidth / 2.0;
		

			// Left Rectangle Calculations

			// calculate the distance from the camera to the center of the rect based on calibrarated data and rectangle height
			double dDistanceLeft_ft = (kCalibratedHeight_px / dMarkerHeights[iLeftVerticalMarker]) * kCalibratedDistance_ft;
		
			// calculate the base in pixels (center of rect to the center of the image)
			double dLeftCenterX = (rcMarkerRects[iLeftVerticalMarker].ptUR.x + rcMarkerRects[iLeftVerticalMarker].ptUL.x) / 2.0;
			double dLeftBase = (dImageCenterX - dLeftCenterX);
	

			// Right Rectangle Calculations

			// calculate the distance from the camera to the center of the rect based on calibrarated data and rectangle height
			double dDistanceRight_ft = (kCalibratedHeight_px / dMarkerHeights[iRightVerticalMarker]) * kCalibratedDistance_ft;

			// calculate the base in pixels (center of rect to the center of the image)
			double dRightCenterX = (rcMarkerRects[iRightVerticalMarker].ptUR.x + rcMarkerRects[iRightVerticalMarker].ptUL.x) / 2.0;
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
	catch(...)
	{
	}
	return 0.0;
}

bool DistanceTracking::IsClosestTargetHot() {

	try
	{
		NetworkTable * pNetworkTable = NetworkTable::GetTable("RoboRealm");
	
		// we'll have three rectangles.  One of the outside rectangles will be the horizontal
		// hot goal indicator.  We'll have to sort them out, and we won't make any assumptions
		// about the order sent from robo-realm.
		// lets find the widest rectangle and assume that it's the target rectangle
	
		if ( pNetworkTable && pNetworkTable->IsConnected()) {

			if ( !pNetworkTable->ContainsKey("MEQ_COORDINATES")) {
				return false;
			}

			double			dMarkerHeights[4];
			double			dMarkerWidths[4];
			SPointRect		rcMarkerRects[4];
			NumberArray		coords;
		
			pNetworkTable->RetrieveValue("MEQ_COORDINATES", coords);

			// call routine to get marker heights (always returns three rect heights)
			int iNumRects = GetMarkerData( coords, rcMarkerRects, dMarkerHeights, dMarkerWidths );
			if (( iNumRects <= 0 ) || ( iNumRects > 3 ))
				return false;

			// the horizontal marker is either ONE or THREE, compare heights to see which

			// a single rect.  we'll assume that this means that a single vertical rectangle is in the
			// image, return false
			if ( iNumRects == 1 ) {
				return false;
			}

			// two rects.  Could be...
			//
			// - a vertical and a horizontal rectangle
			// - two vertical rectangles - clipping off the horizontal rect on one side
			if ( iNumRects == 2 ) {
				// need to figure out which of the above we're dealing with
				// we should be able to tell if one is vertical and the other is horizontal
				// by the fact that one rect is wider than the other but also shorter than
				// the other
	
				// one rect is wider and shorter than the other - must be a mix of H & V rects
				if ((( dMarkerHeights[MARKER_ONE] < dMarkerHeights[MARKER_TWO] ) &&
					 ( dMarkerWidths[MARKER_ONE]  > dMarkerWidths[MARKER_TWO] )) ||					
					(( dMarkerHeights[MARKER_TWO] < dMarkerHeights[MARKER_ONE] ) &&
					 ( dMarkerWidths[MARKER_TWO]  > dMarkerWidths[MARKER_ONE] )))
				{
					return true;
				} else {
					return false;
				}
			}
	
			// thre rectangles - two verticals and a horizontal
			else if ( iNumRects == 3 ) { 
				
				// if THREE is shorter than ONE, THREE (right) is the hot marker, ONE and TWO are the vertical markers
				if ( dMarkerHeights[MARKER_THREE] < dMarkerHeights[MARKER_ONE] ) {

					// if TWO is larger than ONE then it's closer to the robot, hot is true since TWO is next to THREE
					if ( dMarkerHeights[MARKER_TWO] > dMarkerHeights[MARKER_ONE] )
						return true;
					else
						return false;

				// if TWO is larger than ONE then it's closer to the robot, hot is true since TWO is next to ONE
				} else {
					// larger height is closer, if TWO is larger then closer to it and the hot marker
					if ( dMarkerHeights[MARKER_TWO] > dMarkerHeights[MARKER_THREE] )
						return true;
					else
						return false;
				}
			}
		}
	}
	catch(...)
	{
	}
	return false;
}

bool DistanceTracking::IsAimedTargetHot() {

	try 
	{
		NetworkTable * pNetworkTable = NetworkTable::GetTable("RoboRealm");
	
		// we're assuming that this routine is only called while in autonomous mode, which means that
		// there's a maximum of three rectangles on screen at a time.
		
		if ( pNetworkTable && pNetworkTable->IsConnected()) {
	
			if ( !pNetworkTable->ContainsKey("MEQ_COORDINATES") ||
				 !pNetworkTable->ContainsKey("IMAGE_WIDTH")) {
				return false;
			}
				
			double			dMarkerHeights[4];
			double			dMarkerWidths[4];
			double 			dMarkerCenterX[4];
			NumberArray		coords;
			
			pNetworkTable->RetrieveValue("MEQ_COORDINATES", coords); // *targetNum);
			double dImageWidth = pNetworkTable->GetNumber("IMAGE_WIDTH");
	
			double dImageCenterX = dImageWidth / 2.0;
	
			// call routine to get marker heights (always returns three rect heights)
			int iNumRects = GetMarkerSizes( coords, dMarkerHeights, dMarkerWidths, dMarkerCenterX );
	
			// no rectangles on screen, facing other direction or something blocking, return false
			if (( iNumRects <= 0 ) || ( iNumRects > 3 ))
				return false;

			// a single rect.  we'll assume that this means that a single vertical rectangle is in the
			// image, return false
			if ( iNumRects == 1 ) {
				return false;
			}

			// two rects.  Could be...
			//
			// - a vertical and a horizontal rectangle
			// - two vertical rectangles - clipping off the horizontal rect on one side
			if ( iNumRects == 2 ) {
				// need to figure out which of the above we're dealing with
				// we should be able to tell if one is vertical and the other is horizontal
				// by the fact that one rect is wider than the other but also shorter than
				// the other
	
				// one rect is wider and shorter than the other - must be a mix of H & V rects
				if ((( dMarkerHeights[MARKER_ONE] < dMarkerHeights[MARKER_TWO] ) &&
					 ( dMarkerWidths[MARKER_ONE]  > dMarkerWidths[MARKER_TWO] )) ||				
					(( dMarkerHeights[MARKER_TWO] < dMarkerHeights[MARKER_ONE] ) &&
					 ( dMarkerWidths[MARKER_TWO]  > dMarkerWidths[MARKER_ONE] )))
				{
					return true;
				} else {
					return false;
				}
			}

			// three rects..  Must be that we have two verticals and a horizontal, just need to figure
			// out which side the horizontal is on
			if ( iNumRects == 3 ) {
				// if THREE height is less than ONE, THREE (right) is the hot marker, ONE and TWO are the vertical markers
				if ( dMarkerHeights[MARKER_THREE] < dMarkerHeights[MARKER_ONE] ) {
						
					// get distances from the image center to the inside edge of each vertical marker
					double dLeftDistance = dImageCenterX - dMarkerCenterX[MARKER_ONE];
					double dRightDistance = dMarkerCenterX[MARKER_TWO]- dImageCenterX;
	
					// if the camera is aimed more towards the right marker
					if ( fabs(dRightDistance) < fabs(dLeftDistance) )
						return true;
					else 
						return false;
	
				// else ONE (left) is hot, TWO and THREE are the vertical markers
				} else {
	
					// get distances from the image center to the inside edge of each vertical marker
					double dLeftDistance = dImageCenterX - dMarkerCenterX[MARKER_TWO];
					double dRightDistance = dMarkerCenterX[MARKER_THREE] - dImageCenterX;
	
					// if the camera is aimed more towards the left marker
					if ( fabs(dLeftDistance) < fabs(dRightDistance) )
						return true;
					else 
						return false;
				}
			}
		}
	}
	catch(...)
	{
		return false;
	}
	return false;
}
