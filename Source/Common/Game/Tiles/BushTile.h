//
//  BushTile.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__BushTile__
#define __GAM_1514_OSX_Game__BushTile__

#include "Tile.h"


class BushTile : public Tile
{
public:
	BushTile(const char* textureName = RES_TILE_BUSH);
	virtual ~BushTile();
    
    //Return the type of the tile
    const char* getType();
    float getTileSpeed();
};

#endif