//
//  TreeTile.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "TreeTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


TreeTile::TreeTile(const char* textureName) : Tile(TileTypeTree, textureName, true)
{
    
}

TreeTile::~TreeTile()
{
    
}

const char* TreeTile::getType()
{
    return TILE_GROUND_TYPE;
}
