#include "DistanceTracking.h"
#include "math.h"
#include "WPILib.h"
const double kCalibratedHeight_px = 100.0;
const double kCalibratedDistance_ft = 10.0;
const double kdDistanceBetweenReference_ft = 1.2;

#define POINT_UPPER_RIGHT_X		0
#define POINT_UPPER_RIGHT_Y		1
#define POINT_UPPER_LEFT_X		2
#define POINT_UPPER_LEFT_Y		3
#define POINT_LOWER_LEFT_X		4
#define POINT_LOWER_LEFT_Y		5
#define POINT_LOWER_RIGHT_X		6
#define POINT_LOWER_RIGHT_Y		7

DistanceTracking::DistanceTracking() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	
	/*pLEDRelay = new DigitalOutput(5);
	pLEDRelay->Set(1);*/
}

// Called just before this Command runs the first time
void DistanceTracking::Initialize() {	
}
double DistanceTracking::findTriangleHeight(const double & dSideA, const double & dSideB, const double & dTotalBase){
	double s = (dSideA+dSideB+dTotalBase)/2; //Herons area sd
	double area = sqrt(s*(s - dSideA)*(s - dSideB)*(s + dTotalBase)); // Herons area
	double height = (dTotalBase/(2 * area));
	return height;
}

void DistanceTracking::Execute() {
	NetworkTable*table = NetworkTable::GetTable("RoboRealm");
	DriverStationLCD *ds = DriverStationLCD::GetInstance();
	
	
	if (table && ds) {
		double dDistanceBase_ft = 0.0;
		NumberArray coords; // *targetNum = new NumberArray();
		table->RetrieveValue("MEQ_COORDINATES", coords); // *targetNum);
		double dImageWidth = table->GetNumber("IMAGE_WIDTH");

		// ds->PrintfLine(DriverStationLCD::kUser_Line1, "0 = %.1lf,%.1lf", coords.get(POINT_UPPER_RIGHT_X),coords.get(POINT_UPPER_RIGHT_Y));
		// ds->PrintfLine(DriverStationLCD::kUser_Line2, "1 = %.1lf,%.1lf", coords.get(POINT_UPPER_LEFT_X),coords.get(POINT_UPPER_LEFT_Y));
		// ds->PrintfLine(DriverStationLCD::kUser_Line3, "2 = %.1lf,%.1lf", coords.get(POINT_LOWER_LEFT_X),coords.get(POINT_LOWER_LEFT_Y));
		// ds->PrintfLine(DriverStationLCD::kUser_Line4, "3 = %.1lf,%.1lf", coords.get(POINT_LOWER_RIGHT_X),coords.get(POINT_LOWER_RIGHT_Y));

		if ( coords.size() != 16 )
			return;

		int iLeftRect = 0;
		int iRightRect = 8;
		//int iMiddleRect = 0;

/*		if ( coords.get(2) < coords.get(10) ) {
			if ( coords.get(2) < coords.get(18)) {
				iLeftRect = 0;
				if ( coords.get(10) < coords.get(18) ) {
					iMiddleRect = 8; iRightRect = 16;  // 0, 1, 2
				} else {
					iMiddleRect = 16; iRightRect = 8;  // 0, 2, 1
				}
			} else {
				iLeftRect = 16; iMiddleRect = 0; iRightRect = 8; // 2, 0, 1
			}
		} else {
			if ( coords.get(10) < coords.get(18)) {
				iLeftRect = 10;
				if ( coords.get(2) < coords.get(18)) {
					iMiddleRect = 0; iRightRect = 16; // 1, 0, 2
				}
				else {
					iMiddleRect = 16; iRightRect = 0; // 1, 2, 0
				}
			} else {
				iLeftRect = 16; iMiddleRect = 10; iRightRect = 0; // 2, 1, 0
			}
		}
	*/
		// Center Point of Image
		double dImageCenterX = dImageWidth/2.0;
		
		// Left Rectangle Calculations (Everything in Pixels)
		double dLeftUpperRightX = coords.get(iLeftRect+POINT_UPPER_RIGHT_X);
		double dLeftUpperRightY = coords.get(iLeftRect+POINT_UPPER_RIGHT_Y);
		double dLeftUpperLeftX = coords.get(iLeftRect+POINT_UPPER_LEFT_X);
		double dLeftUpperLeftY = coords.get(iLeftRect+POINT_UPPER_LEFT_Y);
		double dLeftLowerLeftY = coords.get(iLeftRect+POINT_LOWER_LEFT_Y);
		double dLeftLowerRightY = coords.get(iLeftRect+POINT_LOWER_RIGHT_Y);
	
		// get the average Y values for the top and bottom of the rect
		double dLeftUpperCenterY = (dLeftUpperLeftY + dLeftUpperRightY) / 2.0;
		double dLeftLowerCenterY = (dLeftLowerLeftY + dLeftLowerRightY) / 2.0;

		// calculate the height, in pixels, of the rect
		double dHeightLeft = dLeftUpperCenterY - dLeftLowerCenterY;
			
		// calculate the distance from the camera to the center of the rect based on calibrarated data and rectangle height
		double dDistanceLeft_ft = (kCalibratedHeight_px/dHeightLeft)* kCalibratedDistance_ft;
		
		// calculate the base in pixels (center of rect to the center of the image)
		double dLeftCenterX = (dLeftUpperRightX + dLeftUpperLeftX) / 2.0;
		double dLeftBase = (dImageCenterX - dLeftCenterX);
	

		// Right Rectangle Calculations
		double dRightUpperRightX = coords.get(iRightRect+POINT_UPPER_RIGHT_X);
		double dRightUpperRightY = coords.get(iRightRect+POINT_UPPER_RIGHT_Y);
		double dRightUpperLeftX = coords.get(iRightRect+POINT_UPPER_LEFT_X);
		double dRightUpperLeftY = coords.get(iRightRect+POINT_UPPER_LEFT_Y);
		double dRightLowerLeftY = coords.get(iRightRect+POINT_LOWER_LEFT_Y);
		double dRightLowerRightY = coords.get(iRightRect+POINT_LOWER_RIGHT_Y);
		
		// get the average Y values for the top and bottom of the rect
		double dRightUpperCenterY = (dRightUpperLeftY + dRightUpperRightY) / 2.0;
		double dRightLowerCenterY = (dRightLowerLeftY + dRightLowerRightY) / 2.0;
		
		// calculate the height, in pixels, of the rect
		double dHeightRight = (dRightUpperCenterY - dRightLowerCenterY);
		
		// calculate the distance from the camera to the center of the rect based on calibrarated data and rectangle height
		double dDistanceRight_ft = (kCalibratedHeight_px/dHeightRight)* kCalibratedDistance_ft;

		// calculate the base in pixels (center of rect to the center of the image)
		double dRightCenterX = (dRightUpperRightX + dRightUpperLeftX) / 2.0;
		double dRightBase = (dRightCenterX- dImageCenterX);


		// Distance calculations

		// calculate our trianble base length (center of left rect to center of right rect) 
		double dBaseWidth = dRightCenterX - dLeftCenterX;

		// calculate the height of our triangle
		double dHeight_ft = findTriangleHeight(dDistanceLeft_ft, dDistanceRight_ft, kdDistanceBetweenReference_ft);

		if ( dRightBase > dLeftBase) {
			// convert right base from pixels to feet
			double dRightBase_ft = (dRightBase * kdDistanceBetweenReference_ft) / dBaseWidth;

			// calculate the base of the right rectangle, based on other two sides
			double dRightTriangleBase_ft = sqrt((pow(dDistanceRight_ft, 2.0)) - (pow(dHeight_ft ,2.0)));

			// calculate the base of the distance rectangle
			dDistanceBase_ft = dRightBase_ft - dRightTriangleBase_ft;
		} 
		
		else {
			// convert left base from pixels to feet
			double dLeftBase_ft = (dLeftBase * kdDistanceBetweenReference_ft) / dBaseWidth;

			// calculate the base of the left rectangle, based on other two sides
			double dLeftTriangleBase_ft = sqrt(pow(dDistanceLeft_ft, 2.0) - pow(dHeight_ft,22.0));

			// calculate the base of the distance rectangle
			dDistanceBase_ft = dLeftBase_ft - dLeftTriangleBase_ft;
		}

		// calculate the distance, based on other two sides
		double dDistance_ft = sqrt(pow(dDistanceBase_ft, 2.0) + pow(dHeight_ft, 2.0));
					
		ds->PrintfLine(DriverStationLCD::kUser_Line5, "DL, DR, = %.1lf,%.1lf", dDistanceLeft_ft, dDistanceRight_ft);
		ds->PrintfLine(DriverStationLCD::kUser_Line6, "D = %.1lf",  dDistance_ft);
		ds->UpdateLCD();
	}

}
// Called repeatedly when this Command is scheduled to run
/*void DistanceTracking::Execute() {
	NetworkTable *table = NetworkTable::GetTable("RoboRealm");
	DriverStationLCD *ds = DriverStationLCD::GetInstance();
	if (table && ds) {
		NumberArray coords; // *targetNum = new NumberArray();
		table->RetrieveValue("MEQ_COORDINATES", coords); // *targetNum);
		double dImageWidth = table->GetNumber("IMAGE_WIDTH");

		// ds->PrintfLine(DriverStationLCD::kUser_Line1, "0 = %.1lf,%.1lf", coords.get(0),coords.get(1));
		// ds->PrintfLine(DriverStationLCD::kUser_Line2, "1 = %.1lf,%.1lf", coords.get(2),coords.get(3));
		// ds->PrintfLine(DriverStationLCD::kUser_Line3, "2 = %.1lf,%.1lf", coords.get(4),coords.get(5));
		// ds->PrintfLine(DriverStationLCD::kUser_Line4, "3 = %.1lf,%.1lf", coords.get(6),coords.get(7));

		//Center Point of Image
		double dImageCenterX = dImageWidth/2.0;
		
		//Left Rectangle Calculations (Everything in Pixels)
		double dLeftUpperRightX = coords.get(0);
		double dLeftUpperRightY = coords.get(1);
		double dLeftUpperLeftX = coords.get(2);
		double dLeftUpperLeftY = coords.get(3);

		double dLeftLowerLeftY = coords.get(5);
		double dLeftLowerRightY = coords.get(7);

		
		double dLeftUpperCenterY = (dLeftUpperLeftY + dLeftUpperRightY) / 2.0;
		double dLeftLowerCenterY = (dLeftLowerLeftY + dLeftLowerRightY) / 2.0;
		
		double dLeftCenterX = (dLeftUpperRightX + dLeftUpperLeftX) / 2.0;
		double dHeightLeft = dLeftUpperCenterY - dLeftLowerCenterY;
			
		double dDistanceLeft_ft = (kCalibratedHeight_px/dHeightLeft)* kCalibratedDistance_ft;
		double dLeftBase = (dImageCenterX - dXLeftCenter);
	
		//Right Rectangle Calculations
		double dXRightUpperRight = coords.get(8); 
		double dYRightUpperRight = coords.get(9);
		double dXRightUpperLeft = coords.get(10); 
		double dYRightUpperLeft = coords.get(11);
		
		double dYRightLowerLeft = coords.get(13);
		double dYRightLowerRight = coords.get(15);
		
		double dYRightUpperCenter = (dYRightUpperLeft + dYRightUpperRight) / 2.0;
		double dYRightLowerCenter = (dYRightLowerLeft + dYRightLowerRight) / 2.0;
		
		double dXRightCenter = (dXRightUpperRight + dXRightUpperLeft)/2.0;
		double dHeightRight = (dYRightUpperCenter - dYRightLowerCenter);
		
		double dDistanceRight_ft = (kCalibratedHeight_px/dHeightRight)* kCalibratedDistance_ft;

		double dRightBase = (dXRightCenter- dImageCenterX);

		double dBaseWidth = dXRightCenter - dXLeftCenter;

		double dHeight_ft = findTriangleHeight(dDistanceLeft_ft, dDistanceRight_ft, kDistanceBetweenReference);
		double dDistanceBase_ft = 0.0;
		if ( dRightBase < dLeftBase) {
			double dRightBase_ft = (dRightBase * kDistanceBetweenReference) / dBaseWidth;				
			double dRightTriangleBase_ft = sqrt((pow(dDistanceRight_ft, 2.0)) - (pow(dHeight_ft ,2.0)));
			dDistanceBase_ft = dRightBase_ft - dRightTriangleBase_ft;
		} 
		
		else {
			double dLeftBase_ft = (dLeftBase * kDistanceBetweenReference) / dBaseWidth;
			double dLeftTriangleBase_ft = sqrt(pow(dDistanceLeft_ft, 2.0) - pow(dHeight_ft,22.0));
			dDistanceBase_ft = dLeftBase_ft - dLeftTriangleBase_ft;
		}
	
		double dDistance_ft = sqrt(pow(dDistanceBase_ft, 2.0) + pow(dHeight_ft, 2.0));
					
		//Numbers Not Checked (constants)
		
		ds->PrintfLine(DriverStationLCD::kUser_Line5, "DL, DR, D = %.1lf,%.1lf,%.1lf", dDistanceLeft_ft,dDistanceRight_ft, dDistance_ft);

		ds->UpdateLCD();
	}
}
*/
// Make this return true when this Command no longer needs to run execute()
bool DistanceTracking::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DistanceTracking::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DistanceTracking::Interrupted() {
}
