//
//  RocksTile.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "RocksTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


RockTile::RockTile(const char* textureName) : Tile(TileTypeRock, textureName, true)
{
    
}

RockTile::~RockTile()
{
    
}

const char* RockTile::getType()
{
   return TILE_GROUND_TYPE;
}
bool RockTile::isWalkableTile()
{
  return 0.3;
}
