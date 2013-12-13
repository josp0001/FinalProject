//
//  BushTile.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "BushTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


BushTile::BushTile(const char* textureName) : Tile(TileTypeBush, textureName, true)
{
    
}

BushTile::~BushTile()
{
    
}

const char* BushTile::getType()
{
    return TILE_BUSH_TYPE;
}
float BushTile::getTileSpeed()
{
    return 0.4f;
}