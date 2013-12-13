//
//  TreeTile.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__TreeTile__
#define __GAM_1514_OSX_Game__TreeTile__

#include "Tile.h"


class TreeTile : public Tile
{
public:
	TreeTile(const char* textureName = RES_TILE_TREE);
	virtual ~TreeTile();
    
    //Return the type of the tile
    const char* getType();
};

#endif
