/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef MOVIE_VIDEO_H
#define MOVIE_VIDEO_H

#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "../CommandBase.h"
#include "WPILib.h"
#include <time.h>
#include <list>
#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>

typedef struct DPstruct {
	clock_t	clk;
	int		x;
	int 	size;
} DataPoint;
typedef std::list<DataPoint>::iterator DataPointer;

class JoystickVideo: public CommandBase {
private:
	const double PERIOD = 3;
	cv::CascadeClassifier logo_cascade;
	std::list<DataPoint> tracker;
	cv::VideoCapture capture;
	std::string cameraIP;
	bool cascade_ok;
public:
	JoystickVideo(const char* name);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	int trackTarget( cv::Mat frame, DataPoint dp );
	void detectAndDisplay( cv::Mat frame, DataPoint* dp );
};

#endif
