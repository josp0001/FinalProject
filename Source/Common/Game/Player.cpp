//
//  Player.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//
#include "Player.h"
#include "Level.h"
#include "PathNode.h"
#include "Tiles/Tile.h"
#include "../Game/Tiles/TowerTileS.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Game/PickUps/AmmoPickup.h"
#include "../UI/UIFont.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "Projectile.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <string>

Player::Player(Level* aLevel)
{
    m_Level = aLevel;
    m_PathFinder = new PathFinder(aLevel, this);
    
    //Initialize the current and destination tiles to NULL
    m_CurrentTile = NULL;
    m_DestinationTile = NULL;
    
    //Initialize the animation member variables
    m_CanAnimate = false;
    m_AbortAnimation = false;
    m_AnimationPathNodeIndex = -1;
    m_Speed = PLAYER_SPEED;
    //amma and health
    m_Ammo =200;
    m_Health = 5;
    //Initialize the player's size
    setSize(PLAYER_SIZE, PLAYER_SIZE);
    m_Font = new UIFont("Fonties");
}

Player::~Player()
{
    //Set the current and desination tiles to NULL
	m_CurrentTile = NULL;
	m_DestinationTile = NULL;
    
    /*if (m_PathFinder != NULL)
    {
        delete m_PathFinder;
        m_PathFinder = 0;
    }
    for( int i = 0; i < m_Projectiles.size(); i++)
    {
        delete m_Projectiles.at(i);
        m_Projectiles.at(i) = NULL;
    }*/
}

void Player::update(double aDelta)
{
    std::string ammoCount = "";
	std::stringstream ammoAmount;
	ammoAmount << m_Ammo;
	ammoAmount >> ammoCount;
	m_Font->setText(ammoCount.c_str());
    

    //update the projectile
    for(int i = 0; i < m_Projectiles.size(); i++)
    {
        if(m_Projectiles.at(i)->getIsActive() == true)
        {
            m_Projectiles.at(i)->update(aDelta);
            
        }
    }
    //Tower1
    for(int i = 0; i < m_Level->getNumberOfTiles(); i++)
    {
        if(m_Level->getTileTypeForIndex(i) == TileTypeTower)
        {
            TowerTile* temp = (TowerTile*) m_Level->getTileForIndex(i);
            for(int location = 0; location < temp->getProjecticle().size(); location++)
            {
                if (temp->getProjecticle().at(location)->getIsActive())
                    temp->getProjecticle().at(location)->update(aDelta);
            }
        }
    }
    //remove aby inactive projectiles from the projectiles vectors
    int index = 0;
    while(index != m_Projectiles.size())
    {
        if(m_Projectiles.at(index)->getIsActive() == false)
        {
         
            //delete the projectile and remove it from the vector
            delete m_Projectiles.at(index);
            m_Projectiles.erase(m_Projectiles.begin() + index);  
        }
        else
        {
            index++;
        }
}

    if (m_PathFinder->isSearchingPath() == true)
    {
        m_PathFinder->update(aDelta);
    }
    
    if (isAnimating() && m_AnimationPathNodeIndex > -1)
    {
        PathNode* pathNode = m_PathFinder->getPathNodeAtIndex(m_AnimationPathNodeIndex);
        Tile* tile = pathNode != NULL ? pathNode->getTile() : NULL;
        
        if(tile)
        {
            float centerX = tile->getX() + (tile->getWidth() - getWidth()) / 2.0f;
            float centerY = tile->getY() + (tile->getHeight() - getHeight()) / 2.0f;
            Tile * playerTile = m_Level->getTileForPosition(getX(), getY());
            float speed = playerTile->getTileSpeed();
            
            float playerX = animate(getX(), centerX, aDelta, speed);
            float playerY = animate(getY(), centerY, aDelta, speed);
            setPosition(playerX, playerY);
            
            //change G as float for slower and faster tiles
            
            if (playerX == centerX && playerY == centerY)
            {
                m_AnimationPathNodeIndex++;
                m_CurrentTile->setIsPath(false);
                setCurrentTile(tile);
                if (m_AnimationPathNodeIndex >= m_PathFinder->getPathSize())
                {
                        stopAnimating();
                        m_CurrentTile->setIsPath(false);
                }
                
                if(m_AbortAnimation)
                {
                    m_AbortAnimation = false;
                    
                    findPath();
                }
            }
            else
            {
                if(m_AbortAnimation == true)
                {
                    m_AbortAnimation =false;
                    findPath();
                }  
        }
    }
        
}
}

void Player::paint()
{
    //Cycle through and paint all the active projectile
    for(int i = 0; i < m_Projectiles.size(); i++)
    {
        if (m_Projectiles.at(i)->getIsActive() == true)
        {
            m_Projectiles.at(i)->paint();
        }
    }
    for(int i = 0; i < m_Level->getNumberOfTiles(); i++)
    {
        if(m_Level->getTileTypeForIndex(i) == TileTypeTower)
        {
            TowerTile* temp = (TowerTile*) m_Level->getTileForIndex(i);
            for(int location = 0; location < temp->getProjecticle().size(); location++)
            {
                if (temp->getProjecticle().at(location)->getIsActive())
                {
                    temp->getProjecticle().at(location)->paint();
                }
            }
        }
    }
    
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_INSIDE_COLOR);
    OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2);
    OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
    OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false);
    if(m_Font != NULL)
    {
        m_Font->draw(ScreenManager::getInstance()->getScreenWidth() - 100, ScreenManager::getInstance()->getScreenHeight() - 50);
    }
    
}


void Player::reset()
{ 
    stopAnimating();
    m_PathFinder->reset();
    m_DestinationTile = NULL;
    m_Health = 10;
    setIsActive(true);
   
    
}
void Player::fireProjectile(float x, float y)
{
    //safety check that there is some ammo left
    if(m_Ammo > 0)
    {
        m_Ammo--;
        //create a new projectile object
        Projectile* projectile = new Projectile(this, 1, 250.0f);
        projectile->setPosition(getX() + (getWidth() / 2.0f), getY() + getHeight() / 2.0f);
        projectile->setTarget(x,y);
        
        m_Projectiles.push_back(projectile);
        Log::debug("", m_Ammo);
        
    }
    else
    {
        Log::debug("Cant fire projectile, no ammo left");
    }
}

void Player::applyDamage(int damage)
{
    m_Health -= damage;
    if(m_Health <= 0)
    {
        m_Health = 0;
        setIsActive(false);
        m_Level->setPickupTypeAtIndex(PickupTypeAmmo, m_Level->getTileIndexForPlayer(this));
        //ScreenManager::getInstance()->switchScreen(GAME_OVER_SCREEN);
        m_Level->EnemyDead();
        Log::debug("player is dead");
    }
    
    else
    {
     
        Log::debug("Player is hit %i health remaining", m_Health);
    }
    
}
int Player::getAmmoCount()
{
    return m_Ammo;
}

void Player::setCurrentTile(Tile* tile)
{
	//Set the current tile pointer
	m_CurrentTile = tile;
	setPosition(tile->getX() + ((tile->getWidth() - getWidth()) / 2), tile->getY() + ((tile->getHeight() - getHeight()) / 2));
}

void Player::setDestinationTile(Tile* tile)
{
	//Set the destination tile pointer
	m_DestinationTile = tile;
    
    if (!isAnimating())
    {
        findPath();
    }
    else
    {
        m_AbortAnimation = true;
    }
}

void Player::handlePickup(Pickup *pickup)
{
    switch (pickup->getPickupType())
    { 
        case PickupTypeAmmo:
            m_Ammo +=((AmmoPickup*)pickup)->getAmmoCount();
            break; 
        default:
            break;
    }
}

void Player::handleBoundsCollision(Projectile *projectile)
{
    Tile*tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
    if(tile == NULL)
    {
        //if the tile object is null, it means the projectile is no longer in the level
        projectile->setIsActive(false);
    }
    
}

void Player::pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound)
{
    if(pathFinder == m_PathFinder)
    {
        if(pathFinder == m_PathFinder)
        {
            startAnimating();
        }
        else
        {
            m_PathFinder->reset();
        }
    }
}

PathFinder* Player::getPathFinder()
{
    return m_PathFinder;
}

void Player::findPath()
{
    m_PathFinder->reset();
    m_PathFinder->findPath(m_CurrentTile, m_DestinationTile);
}


float Player::animate(float aCurrent, float aTarget, double aDelta, float speed)
{
    float increment = aDelta * m_Speed * (aTarget < aCurrent ? -1 : 1* speed);
    if(fabs(increment) > fabs(aTarget - aCurrent))
    {
        return aTarget;
    }
    else
    {
        aCurrent += increment;
    }
    return aCurrent;
}

void Player::startAnimating()
{
	m_CanAnimate = true; 
	m_AnimationPathNodeIndex = 0;
}

void Player::stopAnimating()
{
	m_CanAnimate = false;
	m_AnimationPathNodeIndex = -1;
}

bool Player::isAnimating()
{
    return m_CanAnimate;
    
}