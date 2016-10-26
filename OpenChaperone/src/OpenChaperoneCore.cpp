#include "OpenChaperoneCore.hpp"

using namespace cv;

OpenChaperoneCore::OpenChaperoneCore()
{
	Setup();
}

OpenChaperoneCore::~OpenChaperoneCore()
{
	delete capture1;
	delete capture2;
}

void OpenChaperoneCore::Setup()
{
	cv::ocl::setUseOpenCL(ConfigHandler::GetValue("USE_OPENCL", false).asBool());

	PrintCVDebugInfo();

	edgeDetector = EdgeDetectorModule();
	faceDetector = FaceDetectorModule();

	bool demoMode = ConfigHandler::GetValue("WEBCAM_DEMO_MODE", false).asBool();
	if (demoMode == false) {
		capture1 = new CameraCapture();
		capture1->StartCapturing(0, CameraCapture::DEVICE_TYPE::PS3EYE, true);

		capture2 = new CameraCapture();
		capture2->StartCapturing(1, CameraCapture::DEVICE_TYPE::PS3EYE, true);
	}
	else {
		//Demo mode: show only input from the webcam and make full screen
		capture1 = new CameraCapture();
		capture1->StartCapturing(0, CameraCapture::DEVICE_TYPE::GENERIC, true);

		capture2 = new CameraCapture();
		capture2->StartCapturing(1, CameraCapture::DEVICE_TYPE::PS3EYE, true);
	}

}

void OpenChaperoneCore::Update()
{
	ProcessCapture(capture1, leftMat, "Left");
	ProcessCapture(capture2, rightMat, "Right");
}

/**
Runs the latest frame from the capture through each module when there is
a new frame and returns the result as a cv::Mat.
*/
void OpenChaperoneCore::ProcessCapture(CameraCapture *cap, cv::OutputArray output, string id)
{
	if (cap->IsInitialized()) {

		string capTimerID = "Capture " + id + " Update";
		TS_START_NIF(capTimerID);

		if (cap->IsThreaded() == false) {
			//If the capture isn't threaded, we need to manually update it before querying it here.
			TS_START_NIF("Update");
			cap->UpdateCapture();
			TS_STOP_NIF("Update");
		}
		if (cap->FrameIsReady()) {
			//cv::Mat rawFrame(cap->GetWidth(), cap->GetHeight(), CV_8UC3, cap->GetLatestFrame().data);

			TS_START_NIF("Frame Grab");
			cv::Mat rawFrame = cap->RetrieveCapture().clone();
			TS_STOP_NIF("Frame Grab");

			//cv::UMat rawFrameGPU;
			//rawFrame.copyTo(rawFrameGPU);

			TS_START_NIF("Edge Detector");
			edgeDetector.ProcessFrame(rawFrame, rawFrame);
			TS_STOP_NIF("Edge Detector");
			TS_START_NIF("Face Detector");
			faceDetector.ProcessFrame(rawFrame, rawFrame);
			TS_STOP_NIF("Face Detector");

			TS_START_NIF("Frame Copy");
			//output = rawFrame.clone();
			rawFrame.copyTo(output);
			TS_STOP_NIF("Frame Copy");

			//leftMat = rawFrameGPU.getMat(0).clone();

			//More or less a mutex unlock for capture->GetLatestFrame()
			//capture1->MarkFrameUsed();
			rawFrame.release();
			//rawFrameGPU.release();
		}
		TS_STOP_NIF(capTimerID);
	}
}

/**
Prints OpenCV debug information.
*/
void OpenChaperoneCore::PrintCVDebugInfo()
{
	ocg::app_log.AddLog("--- BEGIN DEBUG INFO ---\n");

#ifdef _DEBUG
	ocg::app_log.AddLog("Debug build\n");
	//std::cout << cv::getBuildInformation();
#else
	ocg::app_log.AddLog("Release build\n");
#endif

	bool openCLSupport = ocl::useOpenCL();
	ocg::app_log.AddLog("OpenCL acceleration is %s\n", cv::ocl::haveOpenCL() ? "available" : "not available");
	ocg::app_log.AddLog("OpenCL used: %s\n", openCLSupport ? "true" : "false");
	//#ifdef DEBUG
	if (openCLSupport) {
		std::vector<cv::ocl::PlatformInfo> platforms;
		cv::ocl::getPlatfomsInfo(platforms);
		for (int i = 0; i<platforms.size(); i++) {
			ocg::app_log.AddLog("  Platform %i of %lu\n", i + 1, platforms.size());
			ocg::app_log.AddLog("    Name:     %s\n", platforms[i].name().c_str());
			ocg::app_log.AddLog("    Vendor:   %s\n", platforms[i].vendor().c_str());
			ocg::app_log.AddLog("    Device:   %i\n", platforms[i].deviceNumber());
			ocg::app_log.AddLog("    Version:  %s\n", platforms[i].version().c_str());
		}
	}
	//#endif
	ocg::app_log.AddLog("Optimized code support: %s\n", useOptimized() ? "true" : "false");
	ocg::app_log.AddLog("IPP support: %s\n", cv::ipp::useIPP() ? "true" : "false");
	ocg::app_log.AddLog("Threads used by OpenCV: %i\n", getNumThreads());
	ocg::app_log.AddLog("CPUs available: %2.i\n", cv::getNumberOfCPUs());

	ocg::app_log.AddLog("--- END DEBUG INFO ---\n");
}

/**
Draw the ImGui windows and controls for this class and all the modules it manages.
*/
void OpenChaperoneCore::DrawAllGUIs() {
	DrawGUI();
	faceDetector.DrawGUI();
	edgeDetector.DrawGUI();
}

void OpenChaperoneCore::DrawGUI() {
}
