/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/

#include "JoystickVideo.h"

#include <iostream>

std::string cascade_name = "cascade.xml";
std::string window_name = "Capture - Cascade detection";



int JoystickVideo::trackTarget( cv::Mat frame, DataPoint dp )
{
	const int max_noise = frame.cols / 5;
	int target = -1;
	tracker.push_back(dp);
	std::cout << "Debug: " << dp.clk << " " << dp.x << " " << dp.size;
	// Pop and drop all expired datapoints
	while( tracker.front().clk + PERIOD*CLOCKS_PER_SEC < dp.clk )
	{
		tracker.pop_front();
	}

	if( tracker.size() > 0 )
	{
		DataPoint avg = {dp.clk,0,0};
		double rough_x = 0;
		int n = 0;
		DataPointer idp;
		for( idp = tracker.begin(); idp != tracker.end(); idp++ )
		{
			rough_x += idp->x;
		}
		rough_x /= tracker.size();
		for( idp = tracker.begin(); idp != tracker.end(); idp++ )
		{
			if( abs(idp->x - rough_x) < max_noise )
			{
				avg.x += idp->x;
				avg.size += idp->size;
				n++;
			}
		}
		if(n > 0)
		{
			avg.x /= n;
			avg.size /= n;
			target = avg.x + avg.size/2;
			line( frame, cv::Point(target,0), cv::Point(target,frame.rows-1), cv::Scalar(0,240,240) );
		}
		//line( frame, Point(dp.x,0), Point(dp.x,frame.rows-1), Scalar(0,240,0) );
		//line( frame, Point(dp.x+dp.size,0), Point(dp.x+dp.size,frame.rows-1), Scalar(0,240,0) );
		std::cout << "|" << avg.x << " " << avg.size << "|" << tracker.size() << " " << n;
	}
	std::cout << "\n";
	return target;
}

void JoystickVideo::detectAndDisplay( cv::Mat frame, DataPoint* dp )
{
	std::vector<cv::Rect> found;
	cv::Mat frame_gray;
	static int iframe = 0;

	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect found
	logo_cascade.detectMultiScale(
			frame_gray, found,
			1.1,          // Scale factor
			2,            // Min neighbors
			0|CV_HAAR_SCALE_IMAGE |CV_HAAR_FIND_BIGGEST_OBJECT,
			cv::Size(16, 16)  // Min size
	);

	for( std::size_t i = 0; i < found.size(); i++ )
	{
		if(i==0)
		{
			dp->clk = clock();
			dp->x = found[i].x;
			dp->size = found[i].width;
		}
		cv::Point center( found[i].x + found[i].width*0.5, found[i].y + found[i].height*0.5 );
		cv::Size axes( found[i].width*0.5, found[i].height*0.5);
		cv::ellipse( frame, center, axes, 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
	}
	iframe++;

}





JoystickVideo::JoystickVideo(const char* name) : CommandBase(name) {
	Requires(chassis);
	cameraIP = "10.31.30.11";
	//-- 2. Read the video stream
	std::string videoStreamAddress = "http://" + cameraIP +"/mjpg/video.mjpg";
	if( !logo_cascade.load( cascade_name ) )
	{
		printf("--(!)Error loading\n");
		cascade_ok = false;
	}
	else if( capture.open(0, 640,480,7.5) )
	{

		std::cout<<capture.get(CV_CAP_PROP_FRAME_WIDTH)<<std::endl;
		std::cout<<capture.get(CV_CAP_PROP_FRAME_HEIGHT)<<std::endl;

		cascade_ok = true;
	}
	else
	{
		std::cout << "Error: can not connect to the camera\n";
		cascade_ok = false;
	}
}
// Called just before this Command runs the first time
void JoystickVideo::Initialize() {
	chassis->InitEncoders();
	chassis->SmartRobot();
	std::cout << "Entering the vision mode...\n";
	//After Opening Camera we need to configure the returned image setting
	//all opencv v4l2 camera controls scale from 0.0 - 1.0

	capture.set(CV_CAP_PROP_EXPOSURE_AUTO, 1);
	//capture.set(CV_CAP_PROP_EXPOSURE_ABSOLUTE, 0.8);
	capture.set(CV_CAP_PROP_BRIGHTNESS, 0.5);
	capture.set(CV_CAP_PROP_CONTRAST, 0.5);
}

// Called repeatedly when this Command is scheduled to run
void JoystickVideo::Execute() {
	double powerR = oi->rightJoystick->GetY();
	if(fabs(powerR)<0.1) powerR = 0;
	double powerL = oi->leftJoystick->GetY();
	if(fabs(powerL)<0.1) powerL = 0;
	double power = (powerL + powerR)/2;
	double turn = 0;

	int target;
	int cross;

	cv::Mat frame;
	capture.read(frame);
	DataPoint dp = {0,0,0};

	if( ! cascade_ok )
	{
		std::cout << "Warning: No cascade - no video processing\n";
	}
	else if( !frame.empty() )
	{
		cross = frame.cols / 2;
		//-- 3. Apply the classifier to the frame
		detectAndDisplay( frame, &dp );
		if( dp.clk != 0 ) {
			target = trackTarget( frame, dp );
			std::cout << "Debug: target=" << target << "\n";

			if( target > 0 )
			{
				turn = -0.001 * (cross-target);
				std::cout << "Debug: turn=" << turn << "\n";
				if(turn<-1) turn = -1;
				if(turn>1) turn = 1;
			}

		}
		//-- Show what you got
		//cv::imshow( window_name, frame );
		cv::imwrite("test.jpg",frame);
	}
	else
	{
		std::cout << "Weird.. no frame\n";
	}

	
	chassis->arcadeDrive(power,turn);
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickVideo::IsFinished() {
	return !oi->straightMode->Get();
}

// Called once after isFinished returns true
void JoystickVideo::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickVideo::Interrupted() {
	End();
}


