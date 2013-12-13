//
//  LevelConstants.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_CONSTANTS_H
#define LEVEL_CONSTANTS_H

//Global enum for the Level's tile types,
//add additional tile types in this enum
enum TileType
{
  TileTypeGround = 1,
  TileTypeWater = 2,
  TileTypeTree = 4,
  TileTypeRock = 8,
  TileTypeBush = 16,
  TileTypeLava = 32,
  TileTypeTower = 64,
  TileTypeCount = 6,
  TileTypeUnknown = -1
   

};
enum PickupType
{
    PickupTypeAmmo = 64 ,
    PickupTypeCount = 1,
    PickupTypeUnknown = -1
    
};
enum ButtonType
{
    ButtonTypeClear = 0,
    ButtonTypeExit,
    ButtonTypeLoad,
    ButtonTypeSave
};

enum SaveType
{
    SaveTypeSave1 = 0,
    SaveTypeSave2,
    SaveTypeSave3,
    SaveTypeSave4,
    SaveTypeSave5,
    SaveTypeSave6,
};

extern const float LEVEL_TIMER;
//Level editor screen name
extern const char* LEVEL_EDITOR_SCREEN_NAME;

//Empty Level Constants
extern const int EMPTY_LEVEL_TILE_SIZE;
extern const int EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX;

#endif
