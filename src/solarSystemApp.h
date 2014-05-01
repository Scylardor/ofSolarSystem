#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "AstrObject.hh"

// Defining names to use as indexes to be more understandable
typedef enum Astres
{
    SUN = 0,
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    MOON,
    CALLISTO,
    EUROPA,
    GANYMEDE,
    IO
} Astres;

class solarSystemApp : public ofBaseApp{
	public:
		void setup();
		void update();
		// Drawing functions
		//------------------
		void draw();
		void drawScene(unsigned camNbr);
		void drawSaturnRing();
		void drawStars();
		void drawBorgFleet();
        //------------------
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Dialog functions
		//------------------
        void manageDialog();
        void resetDialog(void (solarSystemApp::*newDialogFunc)(int));
        void defaultText(int code);
        void cameraText(int code);
        void changeCamTargetText(int code);
        void rotationText(int code);
        void scalingText(int code);
        void effectsText(int code);

        // Camera functions
        //-----------------
        void setupViewports();

        // Mouse picking functions
        //-------------------------
        int mousePickPlanet();
        void mousePickCamTarget(int x, int y, int button);
        void mousePickRotationTarget(int x, int y, int button);
        void mousePickScalingTarget(int x, int y, int button);


        // Objects
        vector<AstrObject *>  objects;
        ofSpherePrimitive stars;
        ofImage starTex;
        vector<ofMaterial> materials;
        ofLight pointLight;
        // Display configuration booleans & dialog
        bool bInfoText;
        bool bDrawOrbits;
        bool bMousePicking;
        bool bFullStop;
        bool bSaturnRing;
        stringstream dialog;
        // Callback functions
        void (solarSystemApp::*dialogFunc)(int);
        void (solarSystemApp::*buttonPressedFunc)(int, int, int);
        // Camera stuff
        ofEasyCam cams[4];
        int camTargetIds[4];
        ofRectangle viewports[4];
        unsigned n_cams;
        // Targets of operations
        unsigned targetCam;
        int mousePickedPlanet;
        int rotationTarget;
        // Special effects variables
        ofBoxPrimitive borgFleet[10];
        ofxAssimpModelLoader enterprise;
        ofImage borgImg;
        bool bDrawBorgs;
        ofSoundPlayer player;
        ofVideoPlayer vplayer;
};
