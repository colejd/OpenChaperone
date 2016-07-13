#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>

#include "OpenChaperoneGlobals.hpp"

#include "gui/UsesGUI.hpp"

#include "modules/edge_detector/EdgeDetectorModule.hpp"
#include "modules/face_detector/FaceDetectorModule.hpp"

#include "camera/CameraCapture.hpp"

#include "ofxTimeMeasurements.h"

/* 
Holds the code for grabbing images from a camera and performing 
OpenCV operations on them. Should not have any engine-specific code
(i.e. OpenFrameworks or Cinder code).
*/
class OpenChaperoneCore: public UsesGUI {
public:

	OpenChaperoneCore();
	~OpenChaperoneCore();

	void Setup();
	void Update();

	void PrintCVDebugInfo();

	void DrawGUI();
	void DrawAllGUIs();

	EdgeDetectorModule edgeDetector;
	FaceDetectorModule faceDetector;

	cv::UMat leftMat = cv::UMat();
	cv::UMat rightMat = cv::UMat();

	CameraCapture* capture1;
	CameraCapture* capture2;

	void ProcessCapture(CameraCapture *cap, cv::OutputArray output, string id);

private:

};