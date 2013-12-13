//
//  RocksTile.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__RocksTile__
#define __GAM_1514_OSX_Game__RocksTile__


#include "Tile.h"


class RockTile : public Tile
{
public:
	RockTile(const char* textureName = RES_TILE_ROCK);
	virtual ~RockTile();
    virtual bool isWalkableTile();
    //Return the type of the tile
    const char* getType();
};

#endif
