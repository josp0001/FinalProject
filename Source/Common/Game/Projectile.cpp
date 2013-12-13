//
//  Projectile.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-29.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Projectile.h"
#include "../Utils/Utils.h"
#include <math.h>
#include "../OpenGL/OpenGL.h"

Projectile::Projectile(ProjectileListener* listener, int damage, float velocity) : GameObject(),
    m_Listener(listener),
    m_Damage(damage),
    m_Velocity(velocity),
    m_Angle(0.0f),
    m_TargetX(0.0f),
    m_TargetY(0.0f)
{
    m_Gunz = new OpenGLTexture("Projectiles");
}
Projectile::~Projectile()
{
    if(m_Gunz != NULL)
	{
		delete m_Gunz;
		m_Gunz = NULL;
	}
    
}
void Projectile::update(double delta)
{
    //calculate the position of the projectile base on the velocity and angle
    float x = getX() + m_Velocity * delta * cosf(m_Angle);
    float y = getY() + m_Velocity * delta * sinf(m_Angle);
    setPosition(x,y);
    //handle the player and bounds collision
    if(m_Listener != NULL)
    {
        m_Listener->handleBoundsCollision(this);
        m_Listener->handlePlayerCollision(this);
    }
}
void Projectile::paint()
{
    OpenGLRenderer::getInstance()->drawTexture(m_Gunz, getX(), getY());
   // OpenGLRenderer::getInstance()->setPointSize(5.0f);
    //OpenGLRenderer::getInstance()->drawPoint(getX(),getY());
   // OpenGLRenderer::getInstance()->setPointSize(10.0f);
}
void Projectile::reset()
{
    
}
const char* Projectile::getType()
{
    return "Projectile";
}
void Projectile::setTarget(float x, float y)
{
    //set the target
    m_TargetX = x;
    m_TargetY = y; 
    //calculate the angle(in radians)
    float deltaX = m_TargetX - getX();
    float deltaY = m_TargetY - getY();
    float angleInDegrees = atan2f(deltaY, deltaX) * 180 / M_PI;
    m_Angle = MathUtils::degreesToRadians(angleInDegrees);
}
int Projectile::getDamage()
{
    return m_Damage;
}
