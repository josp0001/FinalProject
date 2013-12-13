//
//  Player.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <vector>
#include "PathFinder.h"
#include "Projectile.h"

class Level;
class Tile;
class Pickup;
class UIFont;

class Player : public GameObject, public PathFinderListener, public ProjectileListener
{
public:
	Player(Level* level);
	virtual ~Player();

  //Update, paint and reset methods
	void update(double delta);
	void paint();
    void reset();
  //keep gameobject pure virtual method we dont need to declare it pure virtual
  //it makes it easier for inheriting classes to know that player is abstract
    virtual const char* getType() = 0;
  
  //Setter methods for the current and destination tiles
	void setCurrentTile(Tile* tile);
	void setDestinationTile(Tile* tile);
    
   //Projectile methods
    void fireProjectile(float x, float y);
    virtual void applyDamage(int damage);
    int getAmmoCount();
protected:
    //projectile listener methods
    virtual void handlePlayerCollision(Projectile* projectile) = 0;
    virtual void handleBoundsCollision(Projectile* projectile);
    
    void handlePickup(Pickup* pickup);
    void pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound);
    PathFinder* getPathFinder();
    void findPath();
    
  //Animation methods
    float animate(float current, float target, double delta, float speed);
	void startAnimating();
	void stopAnimating();
    bool isAnimating();
    
    //Friend CLass so that it can access protected
    friend class Level;
    
    UIFont* m_Font;
 
    Level* m_Level;
    PathFinder* m_PathFinder;
	Tile* m_CurrentTile;
	Tile* m_DestinationTile;
	bool m_CanAnimate;
    bool m_AbortAnimation;
	int m_AnimationPathNodeIndex;
    float m_Speed;
    int m_Ammo;
    int m_Health;
    int m_Score;
    std::vector<Projectile*>m_Projectiles;
};

#endif