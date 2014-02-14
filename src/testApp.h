#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void drawScene(unsigned camNbr);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void updateDisplayedText(unsigned code);
        void defaultText(int code);
        void cameraText(int code);
        void changeCamTargetText(int code);
        void rotationText(int code);
        void scalingText(int code);
        void resetDialog(void (testApp::*newDialogFunc)(int));
        void setupViewports();
        int mousePickPlanet();
        void mousePickCamTarget(int x, int y, int button);
        void mousePickRotationTarget(int x, int y, int button);
        void mousePickScalingTarget(int x, int y, int button);
        void manageDialog();
        void drawSaturnRing();

        // Class of an astronomical object
        class AstrObject {
        public:
            AstrObject(const string & name, const ofQuaternion & rot, double radius, const string & texture, unsigned orbit=0, const ofVec3f & p_pos=ofVec3f(0,0,0));
            ~AstrObject();

            // Getters
            const string &name() { return m_name; }
            double orbit() { return m_orbit; }
            double orbitRadius() { return m_orbitRadius; }
            const vector<ofQuaternion> & rotations() { return m_rotations; }
            double radius() { return m_obj.getRadius(); }
            const ofVec3f position() { return m_obj.getPosition(); } // doesn't return reference because would return temporary
            ofImage &texture() { return m_texture; }
            ofSpherePrimitive & object() { return m_obj; }
            unsigned materialId() { return m_matId; }
            AstrObject *parent() { return m_parent; }
            bool    isSatellite() { return (m_parent != NULL); }
            bool    rotates() { return (m_rotations.size() != 0); }
            double  orbitSpeedFactor() { return m_orbitSpeedFactor; }
            double  rotationSpeedFactor() { return m_rotationSpeedFactor; }
            double  sizeFactor() { return m_sizeFactor; }

            // Setters
            void setRadius(double radius);
            void setRotations(const vector<ofQuaternion> & rots);
            void addRotation(const ofQuaternion & rot);
            void setOrbit(double orbit);
            void setOrbitRadius(double orbitRadius);
            void setTexture(const string & imagePath);
            void setPosition(const ofVec3f & pos);
            void setParent(AstrObject * parent, const ofVec3f & orbitCoords, double orbitPeriod=0, bool objParent=false);
            void setMaterialId(unsigned id);
            void setOrbitSpeedFactor(double newOSF);
            void setRotationSpeedFactor(double newRSF);

        private:
            string m_name;
            double m_orbit;
            double m_orbitRadius;
            vector<ofQuaternion> m_rotations;
            double m_radius;
            ofImage m_texture;
            ofVec3f m_pos;
            ofSpherePrimitive m_obj;
            AstrObject *m_parent;
            vector<AstrObject *> m_sats;
            unsigned m_matId;
            double m_orbitSpeedFactor;
            double m_rotationSpeedFactor;
            double m_sizeFactor;
        };

        typedef enum Astres {
            SUN = 0,
            MERCURY,
            VENUS,
            EARTH,
            MARS,
            JUPITER,
            SATURN,
            URANUS,
            NEPTUNE,
            MOON
        } Astres;

        vector<AstrObject *>  objects;
        ofSpherePrimitive stars;
        ofImage starTex;
        vector<ofMaterial> materials;
        ofLight pointLight;
        bool bInfoText;
        bool bDrawOrbits;
        bool bMousePicking;
        bool bFullStop;
        double sizeFactor;
        stringstream dialog;
        void (testApp::*dialogFunc)(int);
        void (testApp::*buttonPressedFunc)(int, int, int);
        ofEasyCam cams[4];
        int camTargetIds[4];
        ofRectangle viewports[4];
        unsigned n_cams;
        int mousePickedPlanet;
        unsigned targetCam;
        int rotationTarget;
        ofBoxPrimitive borgFleet[10];
        ofImage borgImg;

};
