//
//  TileLava.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "LavaTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"

LavaTile::LavaTile(const char* textureName) : Tile(TileTypeLava, textureName, true)
{
    
}

LavaTile::~LavaTile()
{
    
}

const char* LavaTile::getType()
{
    return TILE_LAVA_TYPE;
}