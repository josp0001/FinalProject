//
//  Enemy.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-22.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Enemy.h"
#include "Level.h"
#include "../Game/Tiles/Tile.h"
#include "Hero.h"
#include "../Constants/Constants.h"
#include "../OpenGL/OpenGL.h"

Enemy::Enemy(Level* level, float speed) : Player(level)
{
    m_Speed = ENEMY_SPEED1;
    m_Health = ENEMY_HEALTH1;
    m_TextureEnemy = new OpenGLTexture("EnemySexy");
    
}
Enemy::~Enemy()
{
    if(m_TextureEnemy != NULL)
	{
		delete m_TextureEnemy;
		m_TextureEnemy = NULL;
	}
}
const char* Enemy::getType()
{    
    return ENEMY_TYPE;
}
void Enemy::update(double delta)
{
    Player::update(delta);
    //set the destination tile bsed on the players current tile
    setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
}
void Enemy::paint()
{
   OpenGLRenderer::getInstance()->drawTexture(m_TextureEnemy, getX(), getY());
}
void Enemy::reset()
{
    Player::reset();
  //set destination tile
    setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero())); 

 
}
void Enemy::handlePlayerCollision(Projectile *projectile)
{
    //TODO handle hero collision with an enemy projectile
    
}