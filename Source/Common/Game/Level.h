//
//  Level.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "../Constants/Constants.h"
#include <vector>

class Tile;
class Player;
class Hero;
class Enemy;
class Pickup;
class UIFont;

class Level
{
public:
	Level(bool isEditingLevel = false);
	~Level();
    
	//Update, paint and reset methods
	void update(double delta);
    void paint();
    void reset();
    
    //
    void load(const char* levelName);
    void save(const char* levelName);
    void Randomize();
    
    //Input methods
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void keyUpEvent(int keyCode);
	
	//
    TileType getTileTypeForIndex(int index);
    PickupType getPickupTypeForIndex(int index);
    
	//Tile count methods
    
    unsigned int getNumberOfTiles();
	unsigned int getNumberOfHorizontalTiles();
	unsigned int getNumberOfVerticalTiles();
    
	//Validate that the tile coordinates passed in are valid
	bool validateTileCoordinates(int coordinatesX, int coordinatesY);
    
	//Converts a position in screen space into a position in coordinate space
	int getTileCoordinateForPosition(int position);
    
	//Index methods
	int getTileIndexForPosition(int positionX, int positionY);
	int getTileIndexForCoordinates(int coordinatesX, int coordinatesY);
	int getTileIndexForTile(Tile* tile);
    int getTileIndexForPlayer(Player* player);
    
	//Tile methods
	Tile* getTileForPosition(int positionX, int positionY);
	Tile* getTileForCoordinates(int coordinatesX, int coordinatesY);
	Tile* getTileForIndex(int index);
    Tile* getTileForPlayer(Player* player);
    
    
    //
    void setTileTypeAtPosition(TileType tileType, int positionX, int positionY);
    void setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY);
    void setTileTypeAtIndex(TileType tileType, int index);
    //
    void setPickupTypeAtPosition(PickupType pickupType, int positionX, int positionY);
    void setPickupTypeAtCoordinates(PickupType pickupType, int coordinateX, int coordinateY);
    void setPickupTypeAtIndex(PickupType pickupType, int index);
    
    //Coveniance methods to toggle debug paint methods
    void togglePaintTileScoring();
    void togglePaintTileIndexes();
    //Disables the old tiles selection (if ground tile) and
	//enables the newly selected tiles selection (if ground tile)
    
    //getter method for the hero
	void setSelectedTileIndex(int selectedIndex);
    int getSelectedTileIndex();
    //Hero* getHero();
    
   
    void EnemyDead();
    void clearLevel();
    
    Hero* getHero();
    std::vector<Enemy*> getEnemies();
    float getGameTime();
    void setGameTime(float aGameTime);
protected: 
	//Protected Member variables
    UIFont* m_Font;
    float TimeDelay;
   

//std::vector<Hero*>m_Hero;
    Hero* m_Hero;
    std::vector<Enemy*>m_Enemies;
    std::vector<int>m_Spawnpoints;
	Tile** m_Tiles;
	unsigned int m_HorizontalTiles;
	unsigned int m_VerticalTiles;
	unsigned int m_TileSize;
    unsigned int m_PlayerStartingTileIndex;
	int  m_SelectedTileIndex;
    float m_Timer;
    bool m_PaintTileScoring;
    bool m_PaintTileIndexes;
    
    bool isTiming = true;
    int m_Score;
    short m_EnemyCounter;
    short m_HeroCounter;
    float m_GameTime;
    float m_Timing;
    float m_TIMERCOUNTER;
    
    
    UIFont* m_Health;
    UIFont* m_Time;
    UIFont* m_Money;
   
};

#endif
