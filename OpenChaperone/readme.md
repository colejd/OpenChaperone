#OpenChaperone

#### Open-source AR for your VR headset

By 
- (Jonathan Cole)[joncole.me]
at the [VEMILab](vemilab.org), University of Maine.

OpenChaperone provides an AR experience for your VR headset using a pair of Playstation 3 Eye cameras
and a custom-designed 3D-printable mount. As of now this is being used at the VEMILab as a platform 
for research into the efficacy of various AR techniques for aiding human spatial navigation.

This can be used with either Playstation 3 Eye cameras or anything your computer recognizes as a
webcam. As of now if you wish to use different cameras you'll need to change your settings and
recompile.

## Requirements
=============================
To build this project, you will need:
- Visual Studio 2015
- OpenFrameworks 0.9.3
- OpenFrameworks addon for Visual Studio (optional, recommended)
- In the addons folder for OpenFrameworks:
	* [ofxImGui](https://github.com/jvcleave/ofxImGui)
	* [ofxFontStash](https://github.com/armadillu/ofxFontStash)
	* [ofxTimeMeasurements](https://github.com/armadillu/ofxTimeMeasurements)

You will also need opencv_world310.dll and opencv_world310_d.dll in the same directory as your executable.


## Contribution
=============================
See the [style guide](style_guide.md).


## Credits
=============================
This project uses:
- ofxImGui
- ofxFontStash
- ofxTimeMeasurements
- OpenCV
- PS3EyeDriver
- jsoncpp
- ProggyClean font