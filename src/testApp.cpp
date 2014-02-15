#include "testApp.h"

//--------------------------------------------------------------
testApp::AstrObject::AstrObject(const string & p_name, const ofQuaternion & p_rot, double p_radius, const string & p_texturePath, unsigned p_orbit, const ofVec3f & p_pos)
{
    m_orbitSpeedFactor = 10.0;
    m_rotationSpeedFactor = 1.0;
    m_sizeFactor = 5.0;
    m_name = p_name;
    setOrbit(p_orbit);
    addRotation(p_rot);
    m_obj.setRadius(p_radius * m_sizeFactor);
    m_obj.setPosition(p_pos);
    m_parent = NULL;
    setTexture(p_texturePath);

}

testApp::AstrObject::~AstrObject()
{
}

void testApp::AstrObject::setRadius(double p_rad)
{
    m_obj.setRadius(p_rad);
}

void testApp::AstrObject::setRotations(const vector<ofQuaternion> & p_rots)
{
    m_rotations = p_rots;
}

void testApp::AstrObject::addRotation(const ofQuaternion & p_rot)
{
    m_rotations.push_back(p_rot);
}

void testApp::AstrObject::setOrbit(double p_orb)
{
    m_orbit = p_orb;
}

void testApp::AstrObject::setTexture(const string & p_imgPath)
{
    m_texture.loadImage(p_imgPath);
}

void testApp::AstrObject::setPosition(const ofVec3f & p_newPos)
{
    m_obj.setPosition(p_newPos);
}

void testApp::AstrObject::setMaterialId(unsigned p_matId)
{
    m_matId = p_matId;
}

void testApp::AstrObject::setParent(AstrObject * p_parent, const ofVec3f & p_orbitCoords, double p_orbitPeriod, bool p_objParent)
{
    p_parent->m_sats.push_back(this);
    m_parent = p_parent;
    if (p_objParent)
    {
        m_obj.setParent(p_parent->object());
    }
    m_obj.setGlobalPosition(p_orbitCoords * m_sizeFactor);
    m_orbit = p_orbitPeriod;
    m_orbitRadius = p_orbitCoords[0] * m_sizeFactor;
}


void testApp::AstrObject::setOrbitSpeedFactor(double p_newOSF)
{
    m_orbitSpeedFactor = p_newOSF;
}

void testApp::AstrObject::setRotationSpeedFactor(double p_newRSF)
{
    m_rotationSpeedFactor = p_newRSF;
}

void testApp::AstrObject::setOrbitRadius(double p_orbitRadius)
{
    m_orbitRadius = p_orbitRadius;
}


//--------------------------------------------------------------
void testApp::setup()
{

    glEnable(GL_DEPTH_TEST); //enable depth comparisons and update the depth buffer
    ofSetSmoothLighting(true);
    ofSetVerticalSync(true);
    bDrawOrbits = true;
    bInfoText = true;
    bMousePicking = false;
    bFullStop = false;
    targetCam = 0;
    rotationTarget = -1;

    sizeFactor = 5.0;
    // cams[0].setVFlip(true);

    objects.push_back(new AstrObject("Sun", ofQuaternion(0.01, ofVec3f(0.0, 1.0, 0.0)), 10.9, "sunTexture2.png"));
    objects.push_back(new AstrObject("Mercury", ofQuaternion(0.017, ofVec3f(0.0, 1.0, 0.0)), 0.383, "mercurymap.jpg"));
    objects.push_back(new AstrObject("Venus", ofQuaternion(-0.004, ofVec3f(0.0, 1.0, 0.0)), 0.949, "VenusTexture.jpg"));
    objects.push_back(new AstrObject("Earth", ofQuaternion(1, ofVec3f(0, 1.0, 0.0)), 1.0, "EarthTexture.jpg"));
    objects.push_back(new AstrObject("Mars", ofQuaternion(0.98, ofVec3f(0.0, 1.0, 0.0)), 0.533, "MarsTexture.jpg"));
    objects.push_back(new AstrObject("Jupiter", ofQuaternion(2.44, ofVec3f(0.0, 1.0, 0.0)), 10.09, "JupiterTexture.jpg"));
    objects.push_back(new AstrObject("Saturn", ofQuaternion(2.35, ofVec3f(0.0, 1.0, 0.0)), 9.049, "SaturnTexture.jpg"));
    objects.push_back(new AstrObject("Uranus", ofQuaternion(-1.39, ofVec3f(0.0, 1.0, 0.0)), 4.007, "UranusTexture.jpg"));
    objects.push_back(new AstrObject("Neptune", ofQuaternion(1.49, ofVec3f(0.0, 1.0, 0.0)), 3.883, "NeptuneTexture.jpg"));
    objects.push_back(new AstrObject("Moon", ofQuaternion(0.036, ofVec3f(0.0, 1.0, 0.0)), 0.2, "MoonTexture.jpg"));

    objects[MERCURY]->addRotation(ofQuaternion(0.001, ofVec3f(0, 0.0, 1.0)));
    objects[VENUS]->addRotation(ofQuaternion(1.77, ofVec3f(0, 0.0, 1.0)));
    objects[EARTH]->addRotation(ofQuaternion(0.23, ofVec3f(0, 0.0, 1.0)));
    objects[MARS]->addRotation(ofQuaternion(0.25, ofVec3f(0, 0.0, 1.0)));
    objects[JUPITER]->addRotation(ofQuaternion(0.03, ofVec3f(0, 0.0, 1.0)));
    objects[SATURN]->addRotation(ofQuaternion(0.27, ofVec3f(0, 0.0, 1.0)));
    objects[URANUS]->addRotation(ofQuaternion(0.98, ofVec3f(0, 0.0, 1.0)));
    objects[EARTH]->addRotation(ofQuaternion(0.3, ofVec3f(0, 0.0, 1.0)));

    objects[MERCURY]->setParent(objects[SUN], ofVec3f(13.9, 0, 0), objects[MERCURY]->orbitSpeedFactor()/88);
    objects[VENUS]->setParent(objects[SUN], ofVec3f(17.9, 0, 0), objects[VENUS]->orbitSpeedFactor()/225);
    objects[EARTH]->setParent(objects[SUN], ofVec3f(22.0, 0, 0), objects[EARTH]->orbitSpeedFactor()/365);
    objects[MARS]->setParent(objects[SUN], ofVec3f(27.0, 0, 0), objects[MARS]->orbitSpeedFactor()/687);
    objects[JUPITER]->setParent(objects[SUN], ofVec3f(62.9, 0, 0), objects[JUPITER]->orbitSpeedFactor()/4331);
    objects[SATURN]->setParent(objects[SUN], ofVec3f(100.0, 0, 0), objects[SATURN]->orbitSpeedFactor()/10759);
    objects[URANUS]->setParent(objects[SUN], ofVec3f(200.0, 0, 0), objects[URANUS]->orbitSpeedFactor()/60190);
    objects[NEPTUNE]->setParent(objects[SUN], ofVec3f(300.0, 0, 0), objects[NEPTUNE]->orbitSpeedFactor()/30799);
    objects[MOON]->setParent(objects[EARTH], ofVec3f(23.6, 0, 0), objects[MOON]->orbitSpeedFactor()/30799, true);

    stars.setPosition(0, 0, 0);
    stars.setRadius(4000);
    starTex.loadImage("starField.png");
    dialogFunc = &testApp::defaultText;
    defaultText(-1); // initializes default text
    buttonPressedFunc = NULL;
    for (int i = 0; i < 4; i++)
    {
        camTargetIds[i] = -1; // no target
    }
    ofBackground(0,0,0);
    n_cams = 1;
    setupViewports();
    ofMaterial sun_mat;
    ofMaterial planets_mat;

    sun_mat.setEmissiveColor( ofColor(250.0, 200.0, 0.0) );
    planets_mat.setSpecularColor(ofColor(0.0, 0.0, 0.0));
    materials.push_back(sun_mat);
    materials.push_back(planets_mat);
    for (unsigned obj = SUN; obj < objects.size(); obj++)
    {
        objects[obj]->setMaterialId(obj != SUN); // 0 if sun (emissive material), 1 for others
        objects[obj]->object().setResolution(30);
    }


    borgImg.loadImage("Borg.jpg");
    player.loadSound("WeAreTheBorg.wav");
   // vplayer.loadMovie("tng2.mp4");
   // vplayer.play();
    bDrawBorgs = false;
}

//--------------------------------------------------------------
void testApp::update()
{
    vplayer.update();
    if (bDrawBorgs) {
        // number of borgs out of the soalr system
        unsigned borgsOut = 0;

        for (unsigned i = 0; i < 10; i++) {
            borgFleet[i].setPosition(borgFleet[i].getPosition()[0], borgFleet[i].getPosition()[1], borgFleet[i].getPosition()[2] + 5);
            borgsOut += (borgFleet[i].getPosition()[2] > 4000); // if this borg is now out of the system, increment the number of borgs out
        }
        // if all borgs have got out of the system, stop to draw them
        if (borgsOut == 10) {
            bDrawBorgs = false;
        }
    }

}

//--------------------------------------------------------------
void testApp::draw()
{
    for (unsigned camNbr = 0; camNbr < n_cams; camNbr++)
    {
        if (camTargetIds[camNbr] >= SUN)
        {
            cams[camNbr].setTarget(objects[camTargetIds[camNbr]]->position());
        }
        cams[camNbr].begin(viewports[camNbr]);
    //    drawSaturnRing();
        ofEnableLighting();
        pointLight.enable(); // mandatory
        drawScene(camNbr);
        drawStars();
        if (bDrawBorgs) {
            drawBorgFleet();
        }
        pointLight.disable();
        ofDisableLighting();
        cams[camNbr].end();
    }
    for (unsigned camNbr = 1; camNbr < n_cams; camNbr++)
    {
        if (camTargetIds[camNbr] != -1)
        {
            ofDrawBitmapString(objects[camTargetIds[camNbr]]->name(), viewports[camNbr].x + 20, viewports[camNbr].y + 30);
        }

    }

//     draw outlines on views
    ofPushStyle();
    ofSetLineWidth(2);
    ofNoFill();
    ofSetColor(255, 255, 255);
    for (unsigned i = 1; i < n_cams; i++)
    {
        ofRect(viewports[i]);
    }
    ofPopStyle();

    manageDialog();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    (this->*dialogFunc)(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
    if (bMousePicking)
    {
        mousePickedPlanet = mousePickPlanet();
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    if (buttonPressedFunc != NULL)
    {
        (this->*buttonPressedFunc)(x, y, button);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    setupViewports();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}


void testApp::drawStars()
{
    starTex.getTextureReference().bind();
    stars.mapTexCoordsFromTexture( starTex.getTextureReference() );
    stars.draw();
    starTex.getTextureReference().unbind();
}


void testApp::drawSaturnRing()
{
  //  ofEnableAlphaBlending();

    unsigned ringsNumber = 100;
    float multRad = 1.2;

    for (unsigned ring = 0; ring < ringsNumber; ring++)
    {
        ofMesh mesh;
        float cx = 0, cy = 0, zx = 0;
        int max = 50;
        float r = (objects[SATURN]->radius()*multRad);

        ofPushMatrix();
        multRad += 0.005;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for(int ii = 0; ii < max; ii++)
        {
            float step = 2*PI/max; // step size around circle
            float theta = ofMap(ii, 0, max-1, 0, 2*PI); //map i as circle divisions to actual radian values around the circle (note we don't go quite all the way around by one step, because it will be the same as where we started, so we'll just index that starting vertex when we make faces)
            float prevTheta = theta - step; //one step back
            float nextTheta = theta + step; // one step forward

            float x = r * cosf(theta);//calculate the x component
            float y = r * sinf(theta);//calculate the y component
            ofVec3f p(x + cx, y + cy, zx);
            mesh.addColor(ofColor(247-(ring*2), 235-(ring*2), 168-(ring*2)));
            mesh.addVertex(p);//output vertex
            mesh.addTexCoord(ofVec2f((cosf(theta)+1.0)*0.5, (sinf(theta)+1.0)*0.5));
        }
        ofTranslate(objects[SATURN]->position()[0], objects[SATURN]->position()[1], objects[SATURN]->position()[2]);
        ofRotate(45, 1, 0, 0);
        mesh.draw();
        ofPopMatrix();
    }
}

void testApp::drawBorgFleet() {
    for (unsigned i = 0; i < 10; i++) {
        borgImg.getTextureReference().bind();
        borgFleet[i].mapTexCoordsFromTexture( borgImg.getTextureReference() );
        borgFleet[i].draw();
        borgImg.getTextureReference().unbind();
    }
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}

void testApp::manageDialog()
{
    static int alphaText = 0;
    static int alpha = 0;

    if (bInfoText == false)
    {
        if (alpha || alphaText)
        {
            alpha -= 5;
            alphaText -= 5;
        }
        if (alpha < 0)
        {
            alpha = 0;
        }
        if (alphaText < 0)
            alphaText = 0;
    }
    else
    {
        if (alpha < 100)
        {
            alpha += 5;
        }
        if (alphaText < 255)
        {
            alphaText += 5;
        }
        if (alpha > 100)
        {
            alpha = 100;
        }
        if (alphaText > 255)
        {
            alphaText = 255;
        }
    }
    ofDrawBitmapStringHighlight(dialog.str().c_str(), 20, 20, ofColor(196,196,196, alpha), ofColor(255, 255,255, alphaText));
}

void testApp::drawScene(unsigned camNbr)
{
    // draw orbits, start at MERCURY because no orbit for the SUN
    for (int plnt = MERCURY; plnt <= NEPTUNE && bDrawOrbits; plnt ++)
    {
        ofPushMatrix();
        ofRotateX(90);
        ofSetColor(222, 222, 222);
        ofNoFill();
        ofSetCircleResolution(100);
        ofCircle(objects[SUN]->position()[0], objects[SUN]->position()[1], objects[plnt]->position().distance(objects[SUN]->position()));
        ofPopMatrix();
    }
    // drawing sun, planets, make them rotate and orbit around
    for (unsigned o = SUN; o < objects.size(); o ++)
    {
        objects[o]->texture().getTextureReference().bind();
        objects[o]->object().mapTexCoordsFromTexture(objects[o]->texture().getTextureReference());
        materials[objects[o]->materialId()].begin();
        if (objects[o]->rotates() && !bFullStop)
        {
            const vector<ofQuaternion> & rotations = objects[o]->rotations();

            for (unsigned rot = 0; rot < rotations.size(); rot++)
            {
                float angle;
                ofVec3f axis;

                rotations[rot].getRotate(angle, axis);
                if (camNbr == 0)
                {
                    objects[o]->object().rotate(angle*objects[o]->rotationSpeedFactor(), axis);
                }
            }
        }
        if (objects[o]->isSatellite() && camNbr == 0 && !bFullStop)
        {
            objects[o]->object().rotateAround(objects[o]->orbit()*objects[o]->orbitSpeedFactor(), ofVec3f(0.0, 1.0, 0.0), objects[o]->parent()->position());
        }
        // If mouse picking is enabled and that's the planet the cursor is on, color it with green
        if (bMousePicking && mousePickedPlanet == o)
        {
            ofSetColor(ofColor::green);
        }
        else
        {
            ofSetColor(ofColor::white);
        }
        objects[o]->object().draw();
        materials[objects[o]->materialId()].end();
        objects[o]->texture().getTextureReference().unbind();
    }


}

void testApp::mousePickScalingTarget(int x, int y, int button)
{
    if (bMousePicking && button == OF_MOUSE_BUTTON_1)
    {
        mousePickedPlanet = mousePickPlanet();
        resetDialog(&testApp::scalingText);
    }
}

void testApp::mousePickRotationTarget(int x, int y, int button)
{
    if (bMousePicking && button == OF_MOUSE_BUTTON_1)
    {
        int mousePickedPlanet = mousePickPlanet();

        rotationTarget = mousePickedPlanet;
        resetDialog(&testApp::rotationText);
    }
}

void testApp::mousePickCamTarget(int x, int y, int button)
{
    if (bMousePicking && button == OF_MOUSE_BUTTON_1)
    {
        int mousePickedPlanet = mousePickPlanet();

        camTargetIds[targetCam] = mousePickedPlanet;
        resetDialog(&testApp::changeCamTargetText);
    }
}


int testApp::mousePickPlanet()
{
    float nearestDistance = 0.0;
    int nearestIndex = -1;
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

    for (unsigned i = SUN; i <= NEPTUNE; i++)
    {
        ofVec3f pos = cams[0].worldToScreen(objects[i]->position(), viewports[0]);
        float distance = pos.distance(mouse);

        if ((i == SUN || distance < nearestDistance))
        {
            nearestDistance = distance;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}

void testApp::defaultText(int code)
{
    switch (code)
    {
    case -1:
        dialog << "MAIN MENU" << endl;
        dialog << "(C): Camera"<< endl;
        dialog << "(R): Rotations" << endl;
        dialog << "(S): Scaling" << endl;
        dialog << "(I): Insert" << endl;
        dialog << "(E): Effects" << endl;
        dialog << "(F): Fullscreen"<< endl;
        dialog << "(O): Draw Orbits"<< endl;
        dialog << "(T): Take Snapshot" << endl;
        dialog << "(H): Hide this text"<<endl;
        dialog << "ESC: Quit";
        break;
    case 'c':
        resetDialog(&testApp::cameraText);
        break;
    case 'r':
        resetDialog(&testApp::rotationText);
        break;
    case 's':
        resetDialog(&testApp::scalingText);
        break;
    case 'e':
        resetDialog(&testApp::effectsText);
        break;
    case 'f':
        ofToggleFullscreen();
        break;

    case 'o':
        bDrawOrbits = !bDrawOrbits;
        break;
    case 't':
        {
            ofFileDialogResult saveFileResult = ofSystemSaveDialog("SolarSystem.png", "Save a screenshot");

            if (saveFileResult.bSuccess)
            {
                ofSaveScreen(saveFileResult.filePath);
            }
        }
        break;
    case 'h':
        bInfoText = !bInfoText;
        break;
    }

}

void testApp::changeCamTargetText(int code)
{
    switch (code)
    {
    case -1:
        buttonPressedFunc = &testApp::mousePickCamTarget;
        dialog << "CHANGING CAMERA TARGETS" << endl;
        dialog << "(M) = Toggle mouse picking (" << (bMousePicking ? "enabled" : "disabled") << ")" << endl;
        dialog << "Left click on planet (if mouse picking) or LEFT/RIGHT = Change target" << endl;
        dialog << "UP/LEFT = Change camera" << endl;
        dialog << "Current target: " << objects[mousePickedPlanet]->name() << endl;
        if (camTargetIds[0] >= SUN)   // if there's a target, print its name
        {
            dialog << objects[camTargetIds[0]]->name();
        }
        else
        {
            dialog << "None";
        }
        dialog << endl;
        dialog << "Current camera: " << targetCam << " ";
        switch (targetCam)
        {
        case 0:
            dialog << "(Main)";
            break;
        case 1:
            dialog << "(Top)";
            break;
        case 2:
            dialog << "(Middle)";
            break;
        case 3:
            dialog << "(Bottom)";
            break;
        }
        dialog << endl;
        dialog << "(TAB): Back" << endl;
        break;
    case 'm':
        bMousePicking = !bMousePicking;
        resetDialog(&testApp::changeCamTargetText);
        break;
    case OF_KEY_RIGHT:
        camTargetIds[targetCam] = camTargetIds[targetCam] == NEPTUNE ? -1 : camTargetIds[targetCam]+1; // if the index goes beyond neptune, make it loop back to no target
        resetDialog(&testApp::changeCamTargetText);
        break;
    case OF_KEY_LEFT:
        camTargetIds[targetCam] = camTargetIds[targetCam] == -1 ? NEPTUNE : camTargetIds[targetCam]-1; // if the index becomes negative, make it loop back to Neptune
        resetDialog(&testApp::changeCamTargetText);
        break;
    case OF_KEY_UP:
        targetCam = (targetCam+1) % n_cams;
        resetDialog(&testApp::changeCamTargetText);
        break;
    case OF_KEY_DOWN:
        if (targetCam == 0)
        {
            targetCam = n_cams-1;
        }
        else
        {
            targetCam--;
        }
        resetDialog(&testApp::changeCamTargetText);
        break;
    case OF_KEY_TAB:
        bMousePicking = false;
        buttonPressedFunc = NULL;
        resetDialog(&testApp::cameraText);
        break;
    }
}

void testApp::cameraText(int code)
{
    static int newCamTarget = MERCURY;

    switch (code)
    {
    case -1:
        dialog << "CAMERA CONTROLS" << endl;
        dialog << "Left click drag = XY rotation" << endl;
        dialog << "Left click drag in corners of the screen (without target) = Z rotation (roll)" << endl;
        dialog << "Left click drag + (m) OR Middle click drag = move over XY axes (truck and boom)" << endl;
        dialog << "Right click drag = move over Z axis (dolly in and out)" << endl;
        dialog << "Double click (without target) = reset camera position" << endl;
        dialog << "(T): Change camera target" << endl;
        dialog << "(LEFT/RIGHT): Remove/Add one camera (4 max)" << endl;
        dialog << "(TAB): Return to main text" << endl;
        break;
    case 't':
        resetDialog(&testApp::changeCamTargetText);
        break;
    case OF_KEY_LEFT:
        n_cams--;
        if (n_cams == 0)
        {
            n_cams = 4;
        }
        setupViewports();
        resetDialog(&testApp::cameraText);
        break;

    case OF_KEY_RIGHT:
        if (n_cams == 4)
        {
            n_cams = 1;
        }
        else
        {
            camTargetIds[n_cams] = newCamTarget++;
            if (newCamTarget > NEPTUNE)
            {
                newCamTarget = MERCURY;
            }
            n_cams++;
        }
        setupViewports();
        resetDialog(&testApp::cameraText);
        break;
    case OF_KEY_TAB:
        resetDialog(&testApp::defaultText);
        break;
    }

}


void testApp::rotationText(int code)
{
    static bool changeOrbit = true; // do we want to change the orbit or the rotation ?

    switch (code)
    {
    case -1:
        buttonPressedFunc = &testApp::mousePickRotationTarget;
        dialog << "ROTATIONS CONTROLS" << endl;
        dialog << "(M) = Toggle mouse picking (" << (bMousePicking ? "enabled" : "disabled") << ")" << endl;
        dialog << "Left click on planet (if mouse picking) or LEFT/RIGHT = Change target" << endl;
        dialog << "(C) = Toggle orbit/rotation speed change (current: " << (changeOrbit == true ? "Orbit" : "Rotation") << ")" << endl;
        dialog << "(I/D) = Increase/Decrease the speed" << endl;
        dialog << "(F) = Toggle full stop" << endl;
        dialog << "(R) = Re-initialize to default values" << endl;
        dialog << "Current target: " << (rotationTarget == -1 ? "All" : objects[rotationTarget]->name()) << endl;
        dialog << "(TAB): Back to main menu" << endl;
        break;
    case 'c':
        changeOrbit = !changeOrbit;
        resetDialog(&testApp::rotationText);
        break;
    case 'f':
        bFullStop = !bFullStop;
        break;
    case 'm':
        bMousePicking = !bMousePicking;
        resetDialog(&testApp::rotationText);
        break;
    case 'i':
        if (changeOrbit == true)
        {
            if (rotationTarget == -1)
            {
                for (int plnt = SUN; plnt <= MOON; plnt++)
                {
                    objects[plnt]->setOrbitSpeedFactor(objects[plnt]->orbitSpeedFactor() + 1.0);
                }
            }
            else
            {
                objects[rotationTarget]->setOrbitSpeedFactor(objects[rotationTarget]->orbitSpeedFactor() + 1.0);
            }
        }
        else
        {
            if (rotationTarget == -1)
            {
                for (int plnt = SUN; plnt <= MOON; plnt++)
                {
                    objects[plnt]->setRotationSpeedFactor(objects[plnt]->rotationSpeedFactor() + 0.5);
                }
            }
            else
            {
                objects[rotationTarget]->setRotationSpeedFactor(objects[rotationTarget]->rotationSpeedFactor() + 0.5);
            }
        }
        break;
    case 'd':
        if (changeOrbit == true)
        {
            if (rotationTarget == -1)
            {
                for (int plnt = SUN; plnt <= MOON; plnt++)
                {
                    objects[plnt]->setOrbitSpeedFactor(objects[plnt]->orbitSpeedFactor() - 1.0);
                    objects[plnt]->setOrbitSpeedFactor(std::max(objects[plnt]->orbitSpeedFactor(), 0.0));
                }
            }
            else
            {
                objects[rotationTarget]->setOrbitSpeedFactor(objects[rotationTarget]->orbitSpeedFactor() - 1.0);
                objects[rotationTarget]->setOrbitSpeedFactor(std::max(objects[rotationTarget]->orbitSpeedFactor(), 0.0));
            }
        }
        else
        {
            if (rotationTarget == -1)
            {
                for (int plnt = SUN; plnt <= MOON; plnt++)
                {
                    objects[plnt]->setRotationSpeedFactor(objects[plnt]->rotationSpeedFactor() - 0.5);
                    objects[plnt]->setRotationSpeedFactor(std::max(objects[plnt]->rotationSpeedFactor(), 0.0));
                }
            }
            else
            {
                objects[rotationTarget]->setRotationSpeedFactor(objects[rotationTarget]->rotationSpeedFactor() - 0.5);
                objects[rotationTarget]->setRotationSpeedFactor(std::max(objects[rotationTarget]->rotationSpeedFactor(), 0.0));
            }
        }
        break;
    case 'r':
        for (int plnt = SUN; plnt <= MOON; plnt++)
        {
            objects[plnt]->setOrbitSpeedFactor(10.0);
            objects[plnt]->setRotationSpeedFactor(1.0);
        }
        break;
    case OF_KEY_LEFT:
        if (rotationTarget == -1)
        {
            rotationTarget = MOON;
        }
        else
        {
            rotationTarget--;
        }
        resetDialog(&testApp::rotationText);
        break;
    case OF_KEY_RIGHT:
        if (rotationTarget == MOON)
        {
            rotationTarget = -1;
        }
        else
        {
            rotationTarget++;
        }
        resetDialog(&testApp::rotationText);
        break;
    case OF_KEY_TAB:
        bMousePicking = false;
        buttonPressedFunc = NULL;
        resetDialog(&testApp::defaultText);
        break;
    }
}


void testApp::scalingText(int code)
{
    static bool orbitRadius = true; // do we want to change the orbit's radius or the planet's radius ?
    int startScaling;
    int endScaling;

    switch (code)
    {
    case -1:
        buttonPressedFunc = &testApp::mousePickScalingTarget;
        dialog << "SCALING OPERATIONS" << endl;
        dialog << "(M) = Toggle mouse picking (" << (bMousePicking ? "enabled" : "disabled") << ")" << endl;
        dialog << "Left click on planet (if mouse picking) or LEFT/RIGHT = Change target" << endl;
        dialog << "(R) = Change radius of planet" << endl;
        dialog << "(O) = Change radius of planet's orbit" << endl;
        dialog << "(I/D) = Increase/Decrease the radius" << endl;
        dialog << "(S) = Show solar system to scale" << endl;
        dialog << "Current target: " << (mousePickedPlanet == -1 ? "All" : objects[mousePickedPlanet]->name()) << endl;
        dialog << "(TAB): Back to main menu" << endl;
        break;
    case 'r':
        orbitRadius = false;
        break;
    case 'o':
        orbitRadius = true;
        break;
    case 'm':
        bMousePicking = !bMousePicking;
        resetDialog(&testApp::scalingText);
        break;
    case 'i':
        endScaling = (mousePickedPlanet == -1 ? MOON : mousePickedPlanet);
        if (orbitRadius)
        {
            startScaling = (mousePickedPlanet == -1 ? MERCURY : mousePickedPlanet);

            for (int target = startScaling; target <= endScaling; target++)
            {
                ofVec3f gpos = objects[target]->object().getGlobalPosition();

                objects[target]->object().setGlobalPosition(gpos*1.1);
            }
        }
        else
        {
            startScaling = (mousePickedPlanet == -1 ? SUN : mousePickedPlanet);
            for (int target = startScaling; target <= endScaling; target++)
            {
                objects[target]->setRadius(objects[target]->radius()*1.2);
            }
        }
        break;
    case 'd':
        endScaling = (mousePickedPlanet == -1 ? MOON : mousePickedPlanet);
        if (orbitRadius)
        {
            startScaling = (mousePickedPlanet == -1 ? MERCURY : mousePickedPlanet);

            for (int target = startScaling; target <= endScaling; target++)
            {
                ofVec3f gpos = objects[target]->position();
                objects[target]->object().setGlobalPosition(gpos*0.9);
            }
        }
        else
        {
            startScaling = (mousePickedPlanet == -1 ? SUN : mousePickedPlanet);
            for (int target = startScaling; target <= endScaling; target++)
            {
                objects[target]->setRadius(objects[target]->radius()*0.8);
            }
        }
        break;
    case 's':
        objects[EARTH]->setRadius(1.0);
        objects[EARTH]->object().setGlobalPosition(ofVec3f(209, 0, 0));
        objects[SUN]->setRadius(109.0);
        objects[MERCURY]->setRadius(0.383);
        objects[MERCURY]->object().setGlobalPosition(ofVec3f(149, 0, 0));
        objects[VENUS]->setRadius(0.949);
        objects[VENUS]->object().setGlobalPosition(ofVec3f(179, 0, 0));
        objects[MARS]->setRadius(0.533);
        objects[MARS]->object().setGlobalPosition(ofVec3f(259, 0, 0));
        objects[JUPITER]->setRadius(11.209);
        objects[JUPITER]->object().setGlobalPosition(ofVec3f(629, 0, 0));
        objects[SATURN]->setRadius(9.449);
        objects[SATURN]->object().setGlobalPosition(ofVec3f(1059, 0, 0));
        objects[URANUS]->setRadius(4.007);
        objects[URANUS]->object().setGlobalPosition(ofVec3f(2069, 0, 0));
        objects[NEPTUNE]->setRadius(3.883);
        objects[NEPTUNE]->object().setGlobalPosition(ofVec3f(3109, 0, 0));
        objects[MOON]->setRadius(0.374);
        objects[MOON]->object().setPosition(ofVec3f(3.0, 0, 0));
        stars.setRadius(4000);
        // 214,833904461
        break;
    case OF_KEY_LEFT:
        mousePickedPlanet--;
        if (mousePickedPlanet < -1)
        {
            mousePickedPlanet = MOON;
        }
        resetDialog(&testApp::scalingText);
        break;
    case OF_KEY_RIGHT:
        if (mousePickedPlanet == MOON)
        {
            mousePickedPlanet = -1;
        }
        else
        {
            mousePickedPlanet++;
        }
        resetDialog(&testApp::scalingText);
        break;
    case OF_KEY_TAB:
        buttonPressedFunc = NULL;
        bMousePicking = false;
        resetDialog(&testApp::defaultText);
        break;
    }
}


void testApp::effectsText(int code)
{
    switch (code)
    {
    case -1:
        dialog << "SPECIAL EFFECTS" << endl;
        dialog << "(B): Call the Borgs" << endl;
        break;
    case 'b':
        {
            long x = -2000;
            for (unsigned i = 0; i < 10; i++) {
                long y = ofRandom(500, 1000);
                long z = ofRandom(-4000, -4500);

                borgFleet[i].setPosition(x, y, z);
                x += 400;
            }
            bDrawBorgs = true;
            player.play();
            break;
        }
    case OF_KEY_TAB:
        resetDialog(&testApp::defaultText);
        break;
    }

}



//--------------------------------------------------------------
void testApp::resetDialog(void (testApp::*newDialogFunc)(int))
{
    dialog.flush();
    dialog.str("");
    dialogFunc = newDialogFunc;
    (this->*newDialogFunc)(-1);
}


void testApp::setupViewports()
{
    if (n_cams == 1)
    {
        viewports[0].x = 0;
        viewports[0].y = 0;
        viewports[0].width = ofGetWidth();
        viewports[0].height = ofGetHeight();
    }
    else
    {
        float xOffset = ofGetWidth() / 3;
        float yOffset = ofGetHeight() / 3;

        viewports[0].x = 0;
        viewports[0].y = 0;
        viewports[0].width = xOffset * 2;
        viewports[0].height = ofGetHeight();
        for (unsigned i = 1; i < n_cams; i++)
        {
            viewports[i].x = xOffset * 2;
            viewports[i].y = yOffset * (i-1);
            viewports[i].width = xOffset;
            viewports[i].height = yOffset;
        }
    }
}
