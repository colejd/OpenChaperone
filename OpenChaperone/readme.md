# OpenChaperone

#### Open-source AR for your VR headset

Team:
- [Jonathan Cole](joncole.me)
- Sam Gates

at the [VEMILab](vemilab.org), University of Maine.

OpenChaperone provides an AR experience for your VR headset using a pair of Playstation 3 Eye cameras
and a custom-designed 3D-printable mount. As of now this is being used at the VEMILab as a platform 
for research into the efficacy of various AR techniques for aiding human spatial navigation.

This can be used with either Playstation 3 Eye cameras or anything your computer recognizes as a
webcam. As of now if you wish to use different cameras you'll need to change your settings and
recompile.


## Setup Instructions
This project goes into the "apps" folder at the root of your OpenFrameworks folder.
To build this project, you will need:
- Visual Studio 2015
- OpenFrameworks 0.9.3
- OpenFrameworks addon for Visual Studio (optional, recommended)
- In the addons folder at the root of your OpenFrameworks folder:
	* [ofxImGui](https://github.com/jvcleave/ofxImGui)
	* [ofxFontStash](https://github.com/armadillu/ofxFontStash)
	* [ofxTimeMeasurements](https://github.com/armadillu/ofxTimeMeasurements)

You will also need opencv_world310.dll and opencv_world310_d.dll in the same directory as your executable.

For the PS3 Eye cameras to be properly used, you'll need to use [Zadig](http://zadig.akeo.ie/) and set their
drivers to "libusb-win32 (v1.2.6.0)" (as of this writing). Other drivers will cause the camera driver to lock 
up after a few seconds of use. You may have to do this again after restarting your computer. If it isn't
working, try rebooting. Zadig will likely list the cameras as using "libusb0" after changing the drivers;
this is fine.


## Contribution
See the [style guide](style_guide.md).


## Credits
This project uses:
- [ofxImGui](https://github.com/jvcleave/ofxImGui)
- [ofxFontStash](https://github.com/armadillu/ofxFontStash)
- [ofxTimeMeasurements](https://github.com/armadillu/ofxTimeMeasurements)
- [OpenCV](http://opencv.org/)
- [PS3EyeDriver](https://github.com/inspirit/PS3EYEDriver)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [ProggyClean font](http://www.proggyfonts.net/)
