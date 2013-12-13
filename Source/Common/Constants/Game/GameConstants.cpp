#include "GameConstants.h"


//Game Constants
const char* GAME_SCREEN_NAME = "Game";

//Tiles Constants
const char* TILE_GROUND_TYPE = "GroundTile";
const char* TILE_TOWER_TYPE = "Tower";
const char* TILE_ROCK_TYPE = "RockTile";
const char* TILE_TREE_TYPE = "TreeTile";
const char* TILE_WATER_TYPE = "WaterTile";
const char* TILE_BUSH_TYPE = "BushTile";
const char* TILE_LAVA_TYPE = "LavaTile";

const int TILE_PADDING = 2;

//Player Constants

const int PLAYER_SIZE = 30;
const float PLAYER_SPEED = 100.0f;


const OpenGLColor PLAYER_INSIDE_COLOR = OpenGLColor(0.0f, 0.0f, 0.1f, 1.0f);
const OpenGLColor PLAYER_OUTLINE_COLOR = OpenGLColor(1.0f, 0.0f, 1.0f, 1.0f);//Hero
const char* HERO_TYPE = "Hero";
//Enemy
const char* ENEMY_TYPE = "Enemy";

const int ENEMY_HEALTH1 = 10;
const float ENEMY_SPEED1 = 50.0;
const short ENEMY_COUNT = 12;
const short HERO_COUNT = 2;
const float PLAYER_SPEED_SLOW = 1.0f;
//ammo
const char* AMMO_PICKUP_TYPE = "AmmoPickup";
const int CURRENT_MONEY = 200;