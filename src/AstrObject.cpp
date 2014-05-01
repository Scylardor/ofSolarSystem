#include "AstrObject.hh"

//--------------------------------------------------------------
AstrObject::AstrObject(const string & p_name, const ofQuaternion & p_rot, double p_radius, const string & p_texturePath, unsigned p_orbit, const ofVec3f & p_pos)
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

AstrObject::~AstrObject()
{
}

void AstrObject::setRadius(double p_rad)
{
    m_obj.setRadius(p_rad);
}

void AstrObject::setRotations(const vector<ofQuaternion> & p_rots)
{
    m_rotations = p_rots;
}

void AstrObject::addRotation(const ofQuaternion & p_rot)
{
    m_rotations.push_back(p_rot);
}

void AstrObject::setOrbit(double p_orb)
{
    m_orbit = p_orb;
}

void AstrObject::setTexture(const string & p_imgPath)
{
    m_texture.loadImage(p_imgPath);
}

void AstrObject::setPosition(const ofVec3f & p_newPos)
{
    m_obj.setPosition(p_newPos);
}

void AstrObject::setMaterialId(unsigned p_matId)
{
    m_matId = p_matId;
}

void AstrObject::setParent(AstrObject * p_parent, const ofVec3f & p_orbitCoords, double p_orbitPeriod, bool p_objParent)
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


void AstrObject::setOrbitSpeedFactor(double p_newOSF)
{
    m_orbitSpeedFactor = p_newOSF;
}

void AstrObject::setRotationSpeedFactor(double p_newRSF)
{
    m_rotationSpeedFactor = p_newRSF;
}

void AstrObject::setOrbitRadius(double p_orbitRadius)
{
    m_orbitRadius = p_orbitRadius;
}

