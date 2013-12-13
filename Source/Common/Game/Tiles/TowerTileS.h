//
//  TowerTileS.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__TowerTileS__
#define __GAM_1514_OSX_Game__TowerTileS__


#include "Tile.h"
#include "../Player.h"
#include "../Game.h"
#include "../Projectile.h"
#include <vector>

class Level;

class TowerTile : public Tile, public ProjectileListener
{
public:
    TowerTile(Level* level);
	TowerTile(const char* textureName = MAIN_TOWER_TILE);
	virtual~TowerTile();
    
    //Update, paint and reset methods
	void update(double delta);
    
    //Projectile methods
    void fireProjectile(float x, float y);
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void keyUpEvent(int keyCode);
    
    //Upgrades
    void Speedup();
    
    std::vector<Projectile*> getProjecticle();
    
    float m_CurrentState;
    //Projectile listener methods
    virtual void handlePlayerCollision(Projectile* projectile);
    virtual void handleBoundsCollision(Projectile* projectile);
    
protected:
    
    //Return the type of the tile
    const char* getType();
    
    Level* m_Level;
    Player* m_Player;
    Game* m_Game;
    int m_Ammo;
    int m_Health;
    int i;
    float m_TowerSpeed;
    float m_Time;
    
    std::vector<Projectile*> m_Projectiles;
};

#endif /* defined(__GAM_1514_OSX_Game__TowerTileS__) */
