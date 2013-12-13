//
//  WaterTile.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__WaterTile__
#define __GAM_1514_OSX_Game__WaterTile__



#include "Tile.h"


class WaterTile : public Tile
{
public:
	WaterTile(const char* textureName = RES_TILE_WATER);
	virtual ~WaterTile();
    virtual bool isWalkableTile();
    //Return the type of the tile
    const char* getType();
};

#endif