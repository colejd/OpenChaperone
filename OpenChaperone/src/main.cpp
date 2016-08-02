#include "ofMain.h"
#include "ofApp.h"

#include "OpenChaperoneGlobals.hpp"
#include "config/ConfigHandler.hpp"

//Disable the console
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//========================================================================
int main() {

	//Create the app window
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 640, 480, OF_WINDOW);
	//ofSetWindowPosition(0, 0);
	//ofSetupOpenGL(1024, 768, OF_WINDOW); // Can be OF_WINDOW, OF_FULLSCREEN, or OF_GAME_MODE

	//Apply config file settings
	int winWidth = ConfigHandler::GetValue("WINDOW_START_WIDTH", 640).asInt();
	int winHeight = ConfigHandler::GetValue("WINDOW_START_HEIGHT", 480).asInt();
	ofSetWindowShape(winWidth, winHeight);
	int winX = ConfigHandler::GetValue("WINDOW_START_X", 0).asInt();
	int winY = ConfigHandler::GetValue("WINDOW_START_Y", 0).asInt();
	ofSetWindowPosition(winX, winY);
	ofSetFullscreen(ConfigHandler::GetValue("WINDOW_START_FULLSCREEN", false).asBool());
	bool useVerticalSync = ConfigHandler::GetValue("USE_VERTICAL_SYNC", false).asBool();
	ofSetVerticalSync(useVerticalSync);

	//Disable the console if requested from the config
	if (ConfigHandler::GetValue("ENABLE_CONSOLE", true).asBool() == false) {
		FreeConsole();
	}

	//Kick off the app
	ofRunApp(new ofApp()); //Blocks until the app is told to exit
						   //If you reach this point, the app is in the process of exiting.

	std::cout << "OpenChaperone has finished running." << std::endl;
	return 0;
}
