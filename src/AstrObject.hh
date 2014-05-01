#ifndef ASTROBJECT_HH_INCLUDED
#define ASTROBJECT_HH_INCLUDED

#include "ofMain.h"

// Class of an astronomical object
class AstrObject
{
public:
    AstrObject(const string & name, const ofQuaternion & rot, double radius, const string & texture, unsigned orbit=0, const ofVec3f & p_pos=ofVec3f(0,0,0));
    ~AstrObject();

    // Getters
    const string &name()
    {
        return m_name;
    }
    double orbit()
    {
        return m_orbit;
    }
    double orbitRadius()
    {
        return m_orbitRadius;
    }
    const vector<ofQuaternion> & rotations()
    {
        return m_rotations;
    }
    double radius()
    {
        return m_obj.getRadius();
    }
    const ofVec3f position()
    {
        return m_obj.getPosition();    // doesn't return reference because would return temporary
    }
    ofImage &texture()
    {
        return m_texture;
    }
    ofSpherePrimitive & object()
    {
        return m_obj;
    }
    unsigned materialId()
    {
        return m_matId;
    }
    AstrObject *parent()
    {
        return m_parent;
    }
    bool    isSatellite()
    {
        return (m_parent != NULL);
    }
    bool    rotates()
    {
        return (m_rotations.size() != 0);
    }
    double  orbitSpeedFactor()
    {
        return m_orbitSpeedFactor;
    }
    double  rotationSpeedFactor()
    {
        return m_rotationSpeedFactor;
    }
    double  sizeFactor()
    {
        return m_sizeFactor;
    }

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


#endif // ASTROBJECT_HH_INCLUDED
