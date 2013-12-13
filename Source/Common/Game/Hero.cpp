    //
//  Hero.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-22.c 
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Hero.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Utils/Utils.h"
#include "Enemy.h"
#include "../OpenGL/OpenGL.h"



Hero::Hero(Level * level) : Player(level)
{
      m_Texture = new OpenGLTexture("Tower");
}
Hero::~Hero()
{
    if(m_Texture != NULL)
	{
		delete m_Texture;
		m_Texture = NULL;
	}
    
}

void Hero::paint()
{
for
   (int i = 0; i < m_Projectiles.size(); i++)
    {
    m_Projectiles.at(i)->paint();
    }
    OpenGLRenderer::getInstance()->drawTexture(m_Texture, getX(), getY());
}

const char* Hero::getType()
{
    return HERO_TYPE;
}

void Hero::mouseLeftClickUpEvent(float positionX, float positionY)
{
    Tile* tile = m_Level->getTileForPosition(positionX, positionY);
    if(tile != NULL && tile->isWalkableTile() == true)
    {
        //set the destination tile
         setDestinationTile(tile);
        m_Level->setSelectedTileIndex(m_Level->getTileIndexForTile(tile));
    }
}

void Hero::mouseMovementEvent(float deltaX, float deltaY, float positionsX, float positionY)
{
    Tile* tile = m_Level->getTileForPosition(positionsX, positionY);
    if(tile != NULL && tile->isWalkableTile() == true);
    {
        //set the levels selected tile, this call is optional dont put it
        m_Level->setSelectedTileIndex(m_Level->getTileIndexForTile(tile));
        
    }
}

void Hero::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_SPACE)
    {
        Tile* targetTile = m_Level->getTileForIndex(m_Level->getSelectedTileIndex());
        float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
        float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);
        
        fireProjectile(centerX, centerY);
    }
}

void Hero::handlePlayerCollision(Projectile *projectile)
{
    
    Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
    
    //Cycle through all the enemies and check for Collision with the projectile
    for(int i = 0; i < m_Level->getEnemies().size(); i++)
    {
        Enemy* enemy = m_Level->getEnemies().at(i);
        if(enemy != NULL && enemy->getIsActive() == true)
        {
            //Get the Tile the enemy is on
            Tile* enemyTile = m_Level->getTileForPlayer(enemy);
            
            //Is the projectile on the same tile as the enemy?
            if(tile == enemyTile)
            {
                Log::debug("Hero projectile hit an enemy");
                
                //Apply damage to the enemy AND set The projectile to inactive
                enemy->applyDamage(projectile->getDamage());
                projectile->setIsActive(false);
            }
        }
        
    }
}

