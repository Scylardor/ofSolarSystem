#include "solarSystemApp.h"

//--------------------------------------------------------------
void solarSystemApp::setup()
{
    ofMaterial sun_mat;
    ofMaterial planets_mat;

    // Defining materials for lighting to work properly
    sun_mat.setEmissiveColor( ofColor(250.0, 200.0, 0.0) );
    planets_mat.setSpecularColor(ofColor(0.0, 0.0, 0.0));
    materials.push_back(sun_mat);
    materials.push_back(planets_mat);
    ofBackground(0,0,0); // black background
    ofEnableDepthTest(); // enable depth test
    ofSetSmoothLighting(true);
    ofSetVerticalSync(true);
    bDrawOrbits = true;
    bInfoText = true;
    bMousePicking = false;
    bFullStop = false; //trolo
    bSaturnRing = false;
    rotationTarget = -1; // the object targetted by rotation operations, default -1 means "all at once"
    n_cams = 1; // Number of cameras
    targetCam = 0; // the cam targetted by camera operations, 0 (Main) by default
    setupViewports(); // Initializing camera's point of view
    // At first cameras have no targets
    for (int i = 0; i < 4; i++)
    {
        camTargetIds[i] = -1; // no target
    }

    // CREATING THE ASTRONOMICAL OBJECTS
    // with hard-coded values of name, revolution (angle around axis), radius, texture name
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
    objects.push_back(new AstrObject("Callisto", ofQuaternion(0.036, ofVec3f(0.0, 1.0, 0.0)), 0.3, "callisto.jpg"));
    objects.push_back(new AstrObject("Europa", ofQuaternion(0.036, ofVec3f(0.0, 1.0, 0.0)), 0.2, "europa.jpg"));
    objects.push_back(new AstrObject("Ganymede", ofQuaternion(0.036, ofVec3f(0.0, 1.0, 0.0)), 0.4, "ganymede.jpg"));
    objects.push_back(new AstrObject("Io", ofQuaternion(0.036, ofVec3f(0.0, 1.0, 0.0)), 0.2, "io.jpg"));

    // Incline a bit the rotations
    objects[MERCURY]->addRotation(ofQuaternion(0.001, ofVec3f(0, 0.0, 1.0)));
    objects[VENUS]->addRotation(ofQuaternion(1.77, ofVec3f(0, 0.0, 1.0)));
    objects[EARTH]->addRotation(ofQuaternion(0.23, ofVec3f(0, 0.0, 1.0)));
    objects[EARTH]->addRotation(ofQuaternion(0.3, ofVec3f(0, 0.0, 1.0)));
    objects[MARS]->addRotation(ofQuaternion(0.25, ofVec3f(0, 0.0, 1.0)));
    objects[JUPITER]->addRotation(ofQuaternion(0.03, ofVec3f(0, 0.0, 1.0)));
    objects[SATURN]->addRotation(ofQuaternion(0.27, ofVec3f(0, 0.0, 1.0)));
    objects[URANUS]->addRotation(ofQuaternion(0.98, ofVec3f(0, 0.0, 1.0)));
    objects[CALLISTO]->addRotation(ofQuaternion(0.98, ofVec3f(1.0, 0.0, 0.0)));
    objects[EUROPA]->addRotation(ofQuaternion(0.98, ofVec3f(0, 1.0, 0.0)));
    objects[GANYMEDE]->addRotation(ofQuaternion(0.98, ofVec3f(0, 0.0, 1.0)));
    objects[IO]->addRotation(ofQuaternion(0.98, ofVec3f(0, 1.0, 1.0)));
    // Define a point of reference for every planet (basically nearly everything revolves around the Sun)
    // using hard-coded values divisions to simulate different orbiting speeds
    objects[MERCURY]->setParent(objects[SUN], ofVec3f(13.9, 0, 0), objects[MERCURY]->orbitSpeedFactor()/88);
    objects[VENUS]->setParent(objects[SUN], ofVec3f(17.9, 0, 0), objects[VENUS]->orbitSpeedFactor()/225);
    objects[EARTH]->setParent(objects[SUN], ofVec3f(22.0, 0, 0), objects[EARTH]->orbitSpeedFactor()/365);
    objects[MARS]->setParent(objects[SUN], ofVec3f(27.0, 0, 0), objects[MARS]->orbitSpeedFactor()/687);
    objects[JUPITER]->setParent(objects[SUN], ofVec3f(62.9, 0, 0), objects[JUPITER]->orbitSpeedFactor()/4331);
    objects[SATURN]->setParent(objects[SUN], ofVec3f(100.0, 0, 0), objects[SATURN]->orbitSpeedFactor()/10759);
    objects[URANUS]->setParent(objects[SUN], ofVec3f(200.0, 0, 0), objects[URANUS]->orbitSpeedFactor()/60190);
    objects[NEPTUNE]->setParent(objects[SUN], ofVec3f(300.0, 0, 0), objects[NEPTUNE]->orbitSpeedFactor()/30799);
    objects[MOON]->setParent(objects[EARTH], ofVec3f(23.6, 0, 0), objects[MOON]->orbitSpeedFactor()/27.29, true);
    objects[CALLISTO]->setParent(objects[JUPITER], ofVec3f(77.99, 2, 2), (objects[CALLISTO]->orbitSpeedFactor()/1669), true);
    objects[EUROPA]->setParent(objects[JUPITER], ofVec3f(75.99, 4, 4), objects[EUROPA]->orbitSpeedFactor()/355, true);
    objects[GANYMEDE]->setParent(objects[JUPITER], ofVec3f(77.99, -2, 8), objects[GANYMEDE]->orbitSpeedFactor()/715, true);
    objects[IO]->setParent(objects[JUPITER], ofVec3f(74.99, -4, 10), objects[IO]->orbitSpeedFactor()/177, true);
    // Say which material to use for the objects
    for (unsigned obj = SUN; obj < objects.size(); obj++)
    {
        objects[obj]->setMaterialId(obj != SUN); // 0 if sun (emissive material), 1 for others
        objects[obj]->object().setResolution(30);
    }
    // Creating the stars background
    stars.setPosition(0, 0, 0);
    stars.setRadius(2500);
    starTex.loadImage("starField.png");
    // Initialize user interactions functions
    dialogFunc = &solarSystemApp::defaultText;
    defaultText(-1);
    buttonPressedFunc = NULL;

    // Initialize special effects to be ready when needed
    bDrawBorgs = false;


}

//--------------------------------------------------------------
void solarSystemApp::update()
{
    if (vplayer.isPlaying()) { // if user has called Enterprise and the video isn't finished
        ofPoint epos = enterprise.getPosition();

        vplayer.update(); // show the rest of the video
        // Update the position of the Enterprise model based on where we are in the video
        if (vplayer.getPosition() < 0.4) {
            // beginning of video, rising Enterprise in the Y
            enterprise.setPosition(epos[0], epos[1] + 0.5, epos[2]);
        } else if (vplayer.getPosition() < 0.85) {
            // end : start to make it advance in Z
            enterprise.setPosition(epos[0], epos[1], epos[2] + 0.2);
        } else {
            // very end : super acceleration to simulate warp drive effect
            enterprise.setPosition(epos[0], epos[1], epos[2]*1.5);
        }
        if (vplayer.getIsMovieDone() == true) { // don't forget to close the frame if it's over
            vplayer.close();
        }
    }

    if (bDrawBorgs) { // if the user has called the borgs
        unsigned borgsOut = 0; // number of borgs out of the solar system

        for (unsigned i = 0; i < 10; i++) { // make them advance
            borgFleet[i].setPosition(borgFleet[i].getPosition()[0], borgFleet[i].getPosition()[1], borgFleet[i].getPosition()[2] + 5);
            borgsOut += (borgFleet[i].getPosition()[2] > stars.getRadius()); // if this borg is now out of the system, increment the number of borgs out
        }
        // if all borgs have got out of the system, stop to draw them
        if (borgsOut == 10) {
            bDrawBorgs = false;
        }
    }

}

//--------------------------------------------------------------
void solarSystemApp::draw()
{
    for (unsigned camNbr = 0; camNbr < n_cams; camNbr++)
    {
        // point this camera to its target (if any)
        if (camTargetIds[camNbr] >= SUN)
        {
            cams[camNbr].setTarget(objects[camTargetIds[camNbr]]->position());
        }
        cams[camNbr].begin(viewports[camNbr]);
        if (bSaturnRing) {
            drawSaturnRing();
        }
        ofEnableLighting();
        pointLight.enable(); // mandatory
        drawScene(camNbr);
        drawStars();
        // if Borgs have been called, draw them
        if (bDrawBorgs) {
            drawBorgFleet();
        }
        // if the Enterprise has been called, a complex camera movement is done
        // but do it only on the main camera
        if (vplayer.isPlaying() && camNbr == 0) {
            ofPoint e_pos = enterprise.getPosition();

            if (vplayer.getPosition() < 0.4) {
                // beginning of video : the camera is placed above the ship
                cams[camNbr].setPosition(ofVec3f(e_pos[0]+5, e_pos[1]+8, e_pos[2]+5));
            } else if (vplayer.getPosition() > 0.4 && vplayer.getPosition() < 0.6) {
                // on the side
                cams[camNbr].setPosition(ofVec3f(e_pos[0]+10, e_pos[1]+10, e_pos[2]));
            }
            if (vplayer.getPosition() < 0.8) {
                // stop to follow the ship : just look at it go away
                cams[camNbr].lookAt(ofVec3f(e_pos[0], e_pos[1], e_pos[2]));
            }
            // at first the model is spawned upside down : make it rotate properly to obtain the effect we want
            // and draw it
            enterprise.setRotation(0, 180, 1.0, 0.0, 0.0);
            enterprise.setRotation(1, 180, 0.0, 1.0, 0.0);
            enterprise.drawFaces();
        }
        pointLight.disable();
        ofDisableLighting();
        cams[camNbr].end();
    }
    // Draw the name of the camera target, if any
    for (unsigned camNbr = 1; camNbr < n_cams; camNbr++)
    {
        if (camTargetIds[camNbr] != -1)
        {
            ofDrawBitmapString(objects[camTargetIds[camNbr]]->name(), viewports[camNbr].x + 20, viewports[camNbr].y + 30);
        }

    }
    // Draw outline of viewports
    ofPushStyle();
    ofSetLineWidth(2);
    ofNoFill();
    ofSetColor(255, 255, 255);
    for (unsigned i = 1; i < n_cams; i++)
    {
        ofRect(viewports[i]);
    }
    ofPopStyle();
    // Show the dialog
    manageDialog();
    // At last : play the video if Enterprise is here
    // play it in the right corner of the screen (just like camera 4)
    if (vplayer.isPlaying()) {
        vplayer.draw(ofGetWidth()*2/3, ofGetHeight()*2/3, ofGetWidth()/3, ofGetHeight()/3);
    }
}

//--------------------------------------------------------------
void solarSystemApp::keyPressed(int key)
{
    (this->*dialogFunc)(key);
}

//--------------------------------------------------------------
void solarSystemApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void solarSystemApp::mouseMoved(int x, int y)
{
    if (bMousePicking)
    {
        mousePickedPlanet = mousePickPlanet();
    }
}

//--------------------------------------------------------------
void solarSystemApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void solarSystemApp::mousePressed(int x, int y, int button)
{
    if (buttonPressedFunc != NULL)
    {
        (this->*buttonPressedFunc)(x, y, button);
    }
}

//--------------------------------------------------------------
void solarSystemApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void solarSystemApp::windowResized(int w, int h)
{
    setupViewports();
}

//--------------------------------------------------------------
void solarSystemApp::gotMessage(ofMessage msg)
{

}


void solarSystemApp::drawStars()
{
    starTex.getTextureReference().bind();
    stars.mapTexCoordsFromTexture( starTex.getTextureReference() );
    stars.draw();
    starTex.getTextureReference().unbind();
}


void solarSystemApp::drawSaturnRing()
{
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
            float theta = ofMap(ii, 0, max-1, 0, 2*PI); //map i as circle divisions to actual radian values around the circle (note we don't go quite all the way around by one step, because it will be the same as where we started, so we'll just index that starting vertex when we make faces)
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

void solarSystemApp::drawBorgFleet() {
    for (unsigned i = 0; i < 10; i++) {
        borgImg.getTextureReference().bind();
        borgFleet[i].mapTexCoordsFromTexture( borgImg.getTextureReference() );
        borgFleet[i].draw();
        borgImg.getTextureReference().unbind();
    }
}

//--------------------------------------------------------------
void solarSystemApp::dragEvent(ofDragInfo dragInfo)
{

}

void solarSystemApp::manageDialog()
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

void solarSystemApp::drawScene(unsigned camNbr)
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

void solarSystemApp::mousePickScalingTarget(int x, int y, int button)
{
    if (bMousePicking && button == OF_MOUSE_BUTTON_1)
    {
        mousePickedPlanet = mousePickPlanet();
        resetDialog(&solarSystemApp::scalingText);
    }
}

void solarSystemApp::mousePickRotationTarget(int x, int y, int button)
{
    if (bMousePicking && button == OF_MOUSE_BUTTON_1)
    {
        int mousePickedPlanet = mousePickPlanet();

        rotationTarget = mousePickedPlanet;
        resetDialog(&solarSystemApp::rotationText);
    }
}

void solarSystemApp::mousePickCamTarget(int x, int y, int button)
{
    if (bMousePicking && button == OF_MOUSE_BUTTON_1)
    {
        int mousePickedPlanet = mousePickPlanet();

        camTargetIds[targetCam] = mousePickedPlanet;
        resetDialog(&solarSystemApp::changeCamTargetText);
    }
}


int solarSystemApp::mousePickPlanet()
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

void solarSystemApp::defaultText(int code)
{
    switch (code)
    {
    case -1:
        dialog << "MAIN MENU" << endl;
        dialog << "(C): Camera"<< endl;
        dialog << "(R): Rotations" << endl;
        dialog << "(S): Scaling" << endl;
        dialog << "(E): Effects" << endl;
        dialog << "(F): Fullscreen"<< endl;
        dialog << "(O): Draw Orbits"<< endl;
        dialog << "(T): Take Snapshot" << endl;
        dialog << "(H): Hide this text"<<endl;
        dialog << "ESC: Quit";
        break;
    case 'c':
        resetDialog(&solarSystemApp::cameraText);
        break;
    case 'r':
        resetDialog(&solarSystemApp::rotationText);
        break;
    case 's':
        resetDialog(&solarSystemApp::scalingText);
        break;
    case 'e':
        resetDialog(&solarSystemApp::effectsText);
        break;
    case 'f':
        ofToggleFullscreen();
        break;

    case 'o':
        bDrawOrbits = !bDrawOrbits;
        break;
    case 't':
        // CAUTION !! Taking a snapshot during of after the Enterprise has been called makes the application crash
        // for an unknown reason (probably due to OpenGL)
        if (!enterprise.hasMeshes()) {

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

void solarSystemApp::changeCamTargetText(int code)
{
    switch (code)
    {
    case -1:
        buttonPressedFunc = &solarSystemApp::mousePickCamTarget;
        dialog << "CHANGING CAMERA TARGETS" << endl;
        dialog << "(M): Toggle mouse picking (" << (bMousePicking ? "enabled" : "disabled") << ")" << endl;
        dialog << "(LEFT/RIGHT) | Left click (mouse picking): Change target" << endl;
        dialog << "UP/LEFT: Change camera" << endl;
        // Print the camera we want to change the target of
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
        dialog << "Current target: ";
        // if there's a target, print its name
        if (camTargetIds[targetCam] >= SUN)
        {
            dialog << objects[camTargetIds[targetCam]]->name();
        }
        else
        {
            dialog << "None";
        }
        dialog << endl;
        dialog << "(TAB): Back" << endl;
        break;
    case 'm':
        bMousePicking = !bMousePicking;
        resetDialog(&solarSystemApp::changeCamTargetText);
        break;
    case OF_KEY_RIGHT:
        camTargetIds[targetCam] = camTargetIds[targetCam] == NEPTUNE ? -1 : camTargetIds[targetCam]+1; // if the index goes beyond neptune, make it loop back to no target
        resetDialog(&solarSystemApp::changeCamTargetText);
        break;
    case OF_KEY_LEFT:
        camTargetIds[targetCam] = camTargetIds[targetCam] == -1 ? NEPTUNE : camTargetIds[targetCam]-1; // if the index becomes negative, make it loop back to Neptune
        resetDialog(&solarSystemApp::changeCamTargetText);
        break;
    case OF_KEY_UP:
        targetCam = (targetCam+1) % n_cams;
        resetDialog(&solarSystemApp::changeCamTargetText);
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
        resetDialog(&solarSystemApp::changeCamTargetText);
        break;
    case OF_KEY_TAB:
        bMousePicking = false;
        buttonPressedFunc = NULL;
        resetDialog(&solarSystemApp::cameraText);
        break;
    }
}

void solarSystemApp::cameraText(int code)
{
    static int newCamTarget = MERCURY;

    switch (code)
    {
    case -1:
        dialog << "CAMERA CONTROLS" << endl;
        dialog << "Left click drag: XY rotation" << endl;
        dialog << "Left click drag in screen corner (without target): Z rotation (roll)" << endl;
        dialog << "Left click drag + (m) OR Middle click drag: move over XY axes (truck and boom)" << endl;
        dialog << "Right click drag: move over Z axis (dolly in and out)" << endl;
        dialog << "Double click (without target) = reset camera position" << endl;
        dialog << "(T): Change camera target" << endl;
        dialog << "(LEFT/RIGHT): Remove/Add one camera (4 max)" << endl;
        dialog << "(TAB): Return to main text" << endl;
        break;
    case 't':
        resetDialog(&solarSystemApp::changeCamTargetText);
        break;
    case OF_KEY_LEFT:
        n_cams--;
        if (n_cams == 0)
        {
            n_cams = 4;
        }
        setupViewports();
        resetDialog(&solarSystemApp::cameraText);
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
        resetDialog(&solarSystemApp::cameraText);
        break;
    case OF_KEY_TAB:
        resetDialog(&solarSystemApp::defaultText);
        break;
    }

}


void solarSystemApp::rotationText(int code)
{
    static bool changeOrbit = true; // do we want to change the orbit or the rotation ?

    switch (code)
    {
    case -1:
        buttonPressedFunc = &solarSystemApp::mousePickRotationTarget;
        dialog << "ROTATIONS CONTROLS" << endl;
        dialog << "(M) = Toggle mouse picking (" << (bMousePicking ? "enabled" : "disabled") << ")" << endl;
        dialog << "(LEFT/RIGHT) or left click (if mouse picking): Change target" << endl;
        dialog << "(C): Toggle orbit/rotation speed change (current: " << (changeOrbit == true ? "Orbit" : "Rotation") << ")" << endl;
        dialog << "(I/D): Increase/Decrease the speed" << endl;
        dialog << "(F): Toggle full stop" << endl;
        dialog << "(R): Re-initialize to default values" << endl;
        dialog << "Current target: " << (rotationTarget == -1 ? "All" : objects[rotationTarget]->name()) << endl;
        dialog << "(TAB): Back to main menu" << endl;
        break;
    case 'c':
        changeOrbit = !changeOrbit;
        resetDialog(&solarSystemApp::rotationText);
        break;
    case 'f':
        bFullStop = !bFullStop;
        break;
    case 'm':
        bMousePicking = !bMousePicking;
        resetDialog(&solarSystemApp::rotationText);
        break;
    case 'i':
        if (changeOrbit == true) // let's change orbit speed
        {
            if (rotationTarget == -1) // no target = apply the change to all objects
            {
                for (unsigned plnt = SUN; plnt < objects.size(); plnt++)
                {
                    objects[plnt]->setOrbitSpeedFactor(objects[plnt]->orbitSpeedFactor() + 1.0);
                }
            }
            else
            {
                objects[rotationTarget]->setOrbitSpeedFactor(objects[rotationTarget]->orbitSpeedFactor() + 1.0);
            }
        }
        else // let's change rotation speed around itself of the object
        {
            if (rotationTarget == -1)  // no target = apply the change to all objects
            {
                for (unsigned plnt = SUN; plnt < objects.size(); plnt++)
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
        if (changeOrbit == true)  // let's change orbit speed
        {
            if (rotationTarget == -1) // no target = apply the change to all objects
            {
                for (unsigned plnt = SUN; plnt < objects.size(); plnt++)
                {
                    objects[plnt]->setOrbitSpeedFactor(objects[plnt]->orbitSpeedFactor() - 1.0);
                    // do not allow it to go below zero (choose the max between the value and 0)
                    objects[plnt]->setOrbitSpeedFactor(std::max(objects[plnt]->orbitSpeedFactor(), 0.0));
                }
            }
            else
            {
                objects[rotationTarget]->setOrbitSpeedFactor(objects[rotationTarget]->orbitSpeedFactor() - 1.0);
                // do not allow it to go below zero (choose the max between the value and 0)
                objects[rotationTarget]->setOrbitSpeedFactor(std::max(objects[rotationTarget]->orbitSpeedFactor(), 0.0));
            }
        }
        else  // let's change rotation speed around itself of the object
        {
            if (rotationTarget == -1) // no target = apply the change to all objects
            {
                for (unsigned plnt = SUN; plnt < objects.size(); plnt++)
                {
                    objects[plnt]->setRotationSpeedFactor(objects[plnt]->rotationSpeedFactor() - 0.5);
                    // do not allow it to go below zero (choose the max between the value and 0)
                    objects[plnt]->setRotationSpeedFactor(std::max(objects[plnt]->rotationSpeedFactor(), 0.0));
                }
            }
            else
            {
                objects[rotationTarget]->setRotationSpeedFactor(objects[rotationTarget]->rotationSpeedFactor() - 0.5);
                // do not allow it to go below zero (choose the max between the value and 0)
                objects[rotationTarget]->setRotationSpeedFactor(std::max(objects[rotationTarget]->rotationSpeedFactor(), 0.0));
            }
        }
        break;
    case 'r':
        // Reinitialize multiplication factors of all objects
        for (unsigned plnt = SUN; plnt < objects.size(); plnt++)
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
        resetDialog(&solarSystemApp::rotationText);
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
        resetDialog(&solarSystemApp::rotationText);
        break;
    case OF_KEY_TAB:
        bMousePicking = false;
        buttonPressedFunc = NULL;
        resetDialog(&solarSystemApp::defaultText);
        break;
    }
}


void solarSystemApp::scalingText(int code)
{
    static bool orbitRadius = true; // do we want to change the orbit's radius or the planet's radius ?
    int startScaling;
    int endScaling;

    switch (code)
    {
    case -1:
        buttonPressedFunc = &solarSystemApp::mousePickScalingTarget;
        dialog << "SCALING OPERATIONS" << endl;
        dialog << "(M): Toggle mouse picking (" << (bMousePicking ? "enabled" : "disabled") << ")" << endl;
        dialog << "(LEFT/RIGHT) | Left click (if mouse picking): Change target" << endl;
        dialog << "Current target: " << (mousePickedPlanet == -1 ? "All" : objects[mousePickedPlanet]->name()) << endl;
        dialog << "(R): Change planet radius" << endl;
        dialog << "(O): Change planet's orbit's radius" << endl;
        dialog << "(I/D): Increase/Decrease the radius" << endl;
        dialog << "(S): Show solar system to scale" << endl;
        dialog << "(TAB): Back to main menu" << endl;
        break;
    case 'r':
        // we want to change the planet radius
        orbitRadius = false;
        break;
    case 'o':
        // we want to change the planet orbit radius
        orbitRadius = true;
        break;
    case 'm':
        bMousePicking = !bMousePicking;
        resetDialog(&solarSystemApp::scalingText);
        break;
    case 'i':
        // stop scaling objects at Moon included, or the object itself if there is a target
        endScaling = (mousePickedPlanet == -1 ? MOON : mousePickedPlanet);
        if (orbitRadius) // change the orbit radius
        {
            // do not scale the sun ...
            startScaling = (mousePickedPlanet == -1 ? MERCURY : mousePickedPlanet);

            for (int target = startScaling; target <= endScaling; target++)
            {
                ofVec3f gpos = objects[target]->object().getGlobalPosition();

                objects[target]->object().setGlobalPosition(gpos*1.1);
            }
        }
        else // change the planet radius
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
        // Puts the solar system to scale using hard coded values.
        // The positions are determined taking the radius of the parent into account,
        // which explains why the numbers seem a little funky.
        // Isn't reversible at the moment.
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
        objects[CALLISTO]->setRadius(0.377);
        objects[CALLISTO]->object().setPosition(ofVec3f(15.99, 2, 2));
        objects[EUROPA]->setRadius(0.245);
        objects[EUROPA]->object().setPosition(ofVec3f(13.99, 4, 4));
        objects[GANYMEDE]->setRadius(0.413);
        objects[GANYMEDE]->object().setPosition(ofVec3f(15.99, -2, 8));
        objects[IO]->setRadius(0.286);
        objects[IO]->object().setPosition(ofVec3f(12.99, -2, 8));
        stars.setRadius(4000);
        break;
    case OF_KEY_LEFT:
        mousePickedPlanet--;
        if (mousePickedPlanet < -1)
        {
            mousePickedPlanet = MOON;
        }
        resetDialog(&solarSystemApp::scalingText);
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
        resetDialog(&solarSystemApp::scalingText);
        break;
    case OF_KEY_TAB:
        buttonPressedFunc = NULL;
        bMousePicking = false;
        resetDialog(&solarSystemApp::defaultText);
        break;
    }
}


void solarSystemApp::effectsText(int code)
{
    switch (code)
    {
    case -1:
        dialog << "SPECIAL EFFECTS" << endl;
        dialog << "(B): The Borg Fleet" << endl;
        dialog << "(E): The Enterprise (disables snapshot taking)" << endl;
        dialog << "(S): Saturn Rings" << endl;
        dialog << "(TAB): Main menu" << endl;
        break;
    case 'b':
        {
            if (!player.isLoaded()) {
                player.loadSound("WeAreTheBorg.wav");
            }
            if (!borgImg.isAllocated()) {
                borgImg.loadImage("Borg.jpg");
            }
            // Define random spawning points beyond the solar system
            long x = -2000;
            for (unsigned i = 0; i < 10; i++) {
                long y = ofRandom(500, 1000);
                long z = ofRandom(-stars.getRadius(), -stars.getRadius()-500);

                borgFleet[i].setPosition(x, y, z);
                x += 400;
            }
            bDrawBorgs = true;
            if (player.isLoaded()) {
                // if sound is correctly loaded, play the Borgs sound
                player.play();
            }
            break;
        }
    case 'e':
        // start the video only if it isn't already playing
        if (vplayer.isPlaying() == false) {
            if (!enterprise.hasMeshes()) {
                // Load the model here to save setup time.
                // We don't want to load the model twice, hasMeshes returns true if we already loaded it
                enterprise.loadModel("enterprise/1701D3DS.3DS");
                enterprise.setScale(0.01, 0.01, 0.01);
            }
            enterprise.setPosition(objects[EARTH]->position()[0], objects[EARTH]->position()[1], objects[EARTH]->position()[2]);
            vplayer.loadMovie("engage.mp4");
            if (vplayer.isLoaded()) {
                // attempt to play only if loading was successful
                vplayer.play();
            }
            // If the main camera was targetting something, stop to target it to focus on the Enterprise
            camTargetIds[0] = -1;
        }
        break;
    case 's':
        bSaturnRing = !bSaturnRing;
        break;
    case OF_KEY_TAB:
        resetDialog(&solarSystemApp::defaultText);
        break;
    }

}



//--------------------------------------------------------------
void solarSystemApp::resetDialog(void (solarSystemApp::*newDialogFunc)(int))
{
    dialog.flush();
    dialog.str("");
    dialogFunc = newDialogFunc;
    (this->*newDialogFunc)(-1);
}


void solarSystemApp::setupViewports()
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
