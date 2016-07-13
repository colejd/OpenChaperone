#include "ofMain.h"
#include "ofApp.h"

#include "OpenChaperoneGlobals.hpp"
#include "config/ConfigHandler.hpp"

//Disable the console
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW); // Can be OF_WINDOW, OF_FULLSCREEN, or OF_GAME_MODE

	//Disable the console if requested from the config
	if (ConfigHandler::GetValue("ENABLE_CONSOLE", true).asBool() == false) {
		FreeConsole();
	}

	ofRunApp(new ofApp());

	std::cout << "OpenChaperone has finished running." << std::endl;
	return 0;
}
