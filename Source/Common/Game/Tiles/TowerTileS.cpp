//
//  TowerTileS.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "TowerTileS.h"
#include "../Level.h"
#include "../Projectile.h"
#include "../Enemy.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"
#include "../../Input/Input.h"
#include "../../Utils/Utils.h"

TowerTile::TowerTile(const char* textureName) : Tile(TileTypeTower, textureName, false)
{
    m_Ammo = 100;
    m_Health = 3;
    m_TowerSpeed = 3;
	i = 1;
    
    //Shot Delay
    m_Time = m_TowerSpeed;
}

void TowerTile::update(double aDelta)
{
    m_Time -= aDelta;
    for(int BigD = 0; BigD < m_Projectiles.size(); BigD++)
    {
        handleBoundsCollision(m_Projectiles.at(BigD));
    }
    //Fireing a shot for every Time the timer hits 0
    if(m_Time <= 0)
    {
        fireProjectile(0, 20);
        m_Time = m_TowerSpeed;
    }
    
    //Remove any "inactive" projectiles from the projectiles vector
    int index = 0;
    while(index != m_Projectiles.size())
    {
        if(m_Projectiles.at(index)->getIsActive() == false)
        {
            Log::debug("Deleting projectile");
            
            //delete the projectiles and remove it from the vector
            delete m_Projectiles.at(index);
            m_Projectiles.erase(m_Projectiles.begin() + index);
        }
        else
        {
            index++;
        }
    }
}

void TowerTile::fireProjectile(float x, float y)
{
    //safety chock that there is some ammo left
    if(m_Ammo > 0)
    {
        m_Ammo--;
        
        //create a new project object =
        Projectile* projectile = new Projectile(this, 1, 10.0f);
        projectile->setPosition(getX() + (getWidth() / 2.0f), getY() + (getHeight() / 2.0f));
        projectile->setTarget(x, y);
        m_Projectiles.push_back(projectile);
        
        Log::debug("Fired Projectile, %i ammo left", m_Ammo);
    }
    else
    {
        m_Ammo = 100;
    }
}

void TowerTile::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    m_Level->getTileForPosition(positionX, positionY);
}

void TowerTile::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_SPACE)
    {
        Tile* targetTile = m_Level->getTileForIndex(m_Level->getSelectedTileIndex());
        float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
        float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);
        
        //Fire the missles! I mean projectiles
        fireProjectile(centerX, centerY);
    }
}

void TowerTile::Speedup()
{
    if(m_Time != 0.5)
        m_TowerSpeed -= 0.5;
}


std::vector<Projectile*> TowerTile::getProjecticle()
{
    return m_Projectiles;
}

void TowerTile::handlePlayerCollision(Projectile* projectile)
{
    
}

void TowerTile::handleBoundsCollision(Projectile* projectile)
{
    
}

TowerTile::~TowerTile()
{
    
}

const char* TowerTile::getType()
{
    return MAIN_TOWER_TILE;
}