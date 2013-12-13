//
//  Hero.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-22.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__Hero__
#define __GAM_1514_OSX_Game__Hero__
/*#include "Player.h"

class Hero : public Player
{
public:
    Hero(Level * level);
    ~Hero();
    
    void update(double delta);
    void paint();
    
    const char* getType();
    void mouseLeftClickUpEvent(float positioX, float positionY);
    void mouseMovementEvent(float deltaX, float deltaY, float PositionsX, float PositionY);
    void keyUpEvent(int keyCode);
    
    int getScore();
    
protected:
    void handlePlayerCollision(Projectile* projectile);
    float m_FiringRadius;
    double m_FireSpeed;
    float m_FiringRate;
    float m_TimeToUpgrade;
    double m_ElapsedTime;
    float m_Health;
    
};*/
#include "Player.h"

class Hero : public Player
{
public:
    Hero(Level* level);
    ~Hero();
    
    const char* getType();
    void paint();
    
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void keyUpEvent(int keyCode);
    
protected:
    void handlePlayerCollision(Projectile* projectile);
    
    OpenGLTexture* m_Texture;
};


#endif /* defined(__GAM_1514_OSX_Game__Hero__) */
