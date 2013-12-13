#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../OpenGL/OpenGLColor.h"

//Game Constants
extern const char* GAME_SCREEN_NAME;

//Tile Constants
extern const char* TILE_GROUND_TYPE;
extern const char* TILE_ROCK_TYPE;
extern const char* TILE_WATER_TYPE;
extern const char* TILE_TREE_TYPE;
extern const char* TILE_BUSH_TYPE;
extern const char* TILE_LAVA_TYPE;
extern const char* TILE_TOWER_TYPE;

extern const int TILE_PADDING;

//Player Constants

extern const int PLAYER_SIZE;
extern const float PLAYER_SPEED;


extern const OpenGLColor PLAYER_INSIDE_COLOR;
extern const OpenGLColor PLAYER_OUTLINE_COLOR;

//Hero
extern const char* HERO_TYPE;
//Enemy
extern const float ENEMY_SPEED1;
extern const int ENEMY_HEALTH1;
extern const char* ENEMY_TYPE;
extern const short ENEMY_COUNT;
extern const short HERO_COUNT;

extern const float PLAYER_SPEED_SLOW;

//pickUp constants
extern const char* AMMO_PICKUP_TYPE;
extern const int CURRENT_MONEY;

#endif 