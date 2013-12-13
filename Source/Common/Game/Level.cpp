    //
//  Level.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Level.h"
#include "Player.h"
#include "Hero.h"
#include "Enemy.h"
#include "PathFinder.h"

#include "Tiles/Tile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/WaterTile.h"
#include "Tiles/RocksTile.h"
#include "Tiles/TreeTile.h"
#include "Tiles/BushTile.h"
#include "Tiles/LavaTile.h"

#include "PickUps/Pickup.h"
#include "PickUps/AmmoPickup.h"

#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Utils/Utils.h"
#include "../UI/UIFont.h"
#include "../Math/GDRandom.h"

#include <stdlib.h>
#include <sstream>
#include <fstream>



Level::Level(bool isEditingLevel) :
    m_HorizontalTiles(0),
    m_VerticalTiles(0),
    m_TileSize(EMPTY_LEVEL_TILE_SIZE),
    m_PlayerStartingTileIndex(EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX),
    m_Tiles(NULL),
    m_SelectedTileIndex(-1),
    m_PaintTileScoring(false),
    m_PaintTileIndexes(false), 
    m_EnemyCounter(ENEMY_COUNT),
    m_HeroCounter(HERO_COUNT),
    m_Hero(NULL),
    m_Score(CURRENT_MONEY),
    m_GameTime(PLAYER_SPEED_SLOW),
    m_Timing(0),
    m_TIMERCOUNTER(20)

{
    m_Timer = LEVEL_TIMER;
    //Create the player object
    if(isEditingLevel == false)
    {
        m_Hero = new Hero(this);
        /*for(int i = 0; i < 2; i++)
        {
            Hero* hero = new Hero(this);
            m_Hero.push_back(hero);
        }*/
   
        //create the enemy objects
        //TODO: make constants for these
        float min = 50.0f;
        float max = PLAYER_SPEED - 25.0f;
        GDRandom random;
        random.randomizeSeed();
        
        for(int i = 0; i < ENEMY_COUNT; i++)
        {
            float speed = min + random.random(max-min);
            Enemy* enemy = new Enemy(this, speed); 
            m_Enemies.push_back(enemy);            
        }
    }
        m_Spawnpoints.push_back(397);
        m_Spawnpoints.push_back(365);
        
        m_Health = new UIFont("Fonties");
        m_Time = new UIFont("Fonties");
        m_Money = new UIFont("Fonties");
        
        //Calculate the number of horizontal and vertical tiles
        m_HorizontalTiles = ScreenManager::getInstance()->getScreenWidth() / m_TileSize;
        m_VerticalTiles = ScreenManager::getInstance()->getScreenHeight() / m_TileSize;
        
        //Allocate the tiles array, the inheriting class will populate this array with Tile objects
        m_Tiles = new Tile*[m_HorizontalTiles * m_VerticalTiles];
        
        //Initialize all the tiles to NULL
        for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
        {
            m_Tiles[i] = NULL;
        }
        
        //Load an empty level
        load(NULL);

}

Level::~Level()
{
    /*/Delete the player object
    for (int i = 0; i < m_Hero.size(); i++)
    {
        delete m_Hero.at(i);
        m_Hero.at(i) = NULL;
    }*/
    if(m_Hero != NULL)
    {
        delete m_Hero;
        m_Hero = NULL;
    }

    //HP
    if(m_Health != NULL)
    {
        delete m_Health;
        m_Health = NULL;
    }
    //Time
    if(m_Time != NULL)
    {
        delete m_Time;
        m_Time = NULL;
    }
    //Money
    if(m_Money != NULL)
    {
        delete m_Money;
        m_Money = NULL;
    }
    //delete the enemy objects
    for (int i = 0; i < m_Enemies.size(); i++)
    {
        delete m_Enemies.at(i);
        m_Enemies.at(i) = NULL;
    }
    //Delete the tiles array, the inheriting class
    //must delete the object in this array itself
	if(m_Tiles != NULL)
	{
        //Cycle through and delete all the tile objects in the array
        for(int i = 0; i < getNumberOfTiles(); i++)
        {
            if(m_Tiles[i] != NULL)
            {
                delete m_Tiles[i];
                m_Tiles[i] = NULL;
            }
        }
        
		delete[] m_Tiles;
		m_Tiles = NULL;
	}
}

void Level::update(double aDelta)
{
    m_Timing += aDelta;
    //Font stufff
    //HP
    std::stringstream Health;
    Health << "Lives "<< m_HeroCounter;
    std::string stringHealth = Health.str();
    char* HP = new char[stringHealth. length() + 1];
    std::strcpy(HP, stringHealth.c_str());
    m_Health->setText(HP);
    
    //Time 
    std::stringstream Time;
    Time << "Time " << (short)m_Timing;
    std::string stringTime = Time.str();
    char* TIME = new char[stringTime. length() + 1];
    std::strcpy(TIME, stringTime.c_str());
    m_Time->setText(TIME);
    
    //Money 
    std::stringstream Money;
    Money << "Money " << m_Score;
    std::string stringMoney = Money.str();
    char* CRD = new char[stringMoney. length() + 1];
    std::strcpy(CRD, stringMoney.c_str());
    m_Money->setText(CRD);
    
    if(m_Timing >= m_TIMERCOUNTER)
    {
        m_HeroCounter += 1;
        m_TIMERCOUNTER += 20;
    }
    
    //If there is no more enemies Go to the Winner screen
    if(m_EnemyCounter <= 0)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_WIN_NAME );
    }
    
    if(m_HeroCounter <= 0)
    {
        ScreenManager::getInstance()->switchScreen(GAME_OVER_SCREEN);
    }
    //m_Timer -= aDelta;
    //if(m_Timer <= 0)
     
       
    //{
        //ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    //
   // }

	//Update all the game tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
	      m_Tiles[i]->update(aDelta* getGameTime());
		}
	} 
    
	//Update the Hero
    if(m_Hero != NULL)
    {
        m_Hero->update(aDelta);
    }
    
    //Update the enemy object
    for(int i = 0; i < m_Enemies.size(); i++)
    {
        //Removes the enemies if he is at the same index as the player
        if(getTileIndexForPlayer(m_Enemies.at(i)) == getTileIndexForPlayer(m_Hero) && m_Enemies.at(i)->getIsActive() != false)
        {
            m_Enemies.at(i)->setIsActive(true);
            m_EnemyCounter -= 1;
            m_HeroCounter -= 1;
            m_Score += 100;
            Log::debug("", m_HeroCounter);
            Log::debug("", m_EnemyCounter);
        }
        
        if(m_Enemies.at(i)->getIsActive() == true)
        {
            m_Enemies.at(i)->update(aDelta);
        }
        
    }
    
}

void Level::paint()
{
	//Cycle through and paint all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
        //Safety check the tile
		if(m_Tiles[i] != NULL)
		{
            //Paint the tile
            m_Tiles[i]->paint();    
          
          //If the paint tile indexes flag is set to true,
            //draw the index number on the tiles
            if(m_PaintTileIndexes == true)
            {
                m_Tiles[i]->paintIndex(i);
            }
		}
      
    }
    
	//Paint the Hero
//	if(m_Hero != NULL)
//	{
//        //If paint tile scoring flag is set to true,
//        //draw the path scoring
//        if(m_PaintTileScoring == true)
//        {
//            m_Hero->getPathFinder()->paint();
//        }
//        
//        //Paint the player
//		m_Hero->paint();
//	}
//    
//    if(m_Hero2 != NULL)
//    {
//    
//        if(m_PaintTileScoring == true)
//        {
//            m_Hero2->getPathFinder()->paint();
//        }
//        m_Hero2->paint();
/*/    }
    for(int i = 0; i < m_Hero.size(); i++)
    {
        m_Hero.at(i)->paint();
    }
    
    //paint the enemies
    for(int i = 0; i < m_Enemies.size(); i++)
    {
        if(m_Enemies.at(i)->getIsActive() == true)
        {
            m_Enemies.at(i)->paint();
        }  
    }
    for(int i = 0; i < m_Spawnpoints.size(); i++)
   
    {
       Tile* tile = getTileForIndex(m_Spawnpoints.at(i));
       float x = tile->getX() + (tile->getWidth() / 2.0f);
       float y = tile->getY() + (tile->getHeight() / 2.0f);
       OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorGreen());
       OpenGLRenderer::getInstance()->drawCircle(x,y,tile->getWidth() / 2.0f - 4.0f, false);
        
    } */
    if(m_Hero != NULL)
    {
        //If paint tile scoring flag is set to true,
        //draw the path scoring
        if(m_PaintTileScoring == true)
        {
            m_Hero->getPathFinder()->paint();
        }
        
        //Paint the player
        m_Hero->paint();
    }
    
    //Paint the enemies
    for(int i = 0; i < m_Enemies.size(); i++)
    {
        if(m_Enemies.at(i)->getIsActive() == true)
        {
            m_Enemies.at(i)->paint();
        }
    }
    
    //HUD
    if(m_Health != NULL)
    {
        m_Health->draw(40,20);
    }
    
    //HUD
    if(m_Time != NULL)
    {
        m_Time->draw(400,20);
    }
    
    //Money
    if(m_Money != NULL)
    {
        m_Money->draw(770,20);
    }

}

void Level::reset()
{  
	//Cycle through and reset all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->reset();
		}
    
	}
    
    //make a player vector to hold the hero and enemies for reset()
    std::vector<Player*> player;
    if(m_Hero != NULL)
    {
        player.push_back(m_Hero);
    }
    
    for(int i = 0; i < m_Enemies.size(); i++)
    {
        player.push_back(m_Enemies.at(i));
    }
    
    //Random number generator for the spawn indexes
    GDRandom random;
    random.randomizeSeed();
    int tileIndex = -1;
    std::vector<int> usedTileIndexes;
    
    //Cycle through the Player objects
    for(int i = 0; i < player.size(); i++)
    {
        //Set tileIndex tp -1
        tileIndex = -1;
        
        while (tileIndex == -1)
        {
            tileIndex = random.random(getNumberOfTiles());
            
            //Safety check that it is a walkable tile
            if(getTileForIndex(tileIndex)->isWalkableTile() == false)
            {
                tileIndex = -1;
            }
            else
            {
                for(int j = 0; j < usedTileIndexes.size(); j++)
                {
                    if(usedTileIndexes.at(j) == tileIndex)
                    {
                        tileIndex = -1;
                        break;
                    }
                }
                
                //Safety check that tileIndex isnt -1
                if(tileIndex != -1)
                {
                    player.at(i)->setCurrentTile(getTileForIndex(tileIndex));
                    player.at(i)->reset();
                    usedTileIndexes.push_back(tileIndex);
                }
            }
        }
    }
}


void Level::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
/*   if(m_Hero2 != NULL)
   {
      m_Hero2->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
   }
    for(int i = 0; i < m_Hero.size(); i++)
    {
        m_Hero.at(i)->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
 */
    if(m_Hero != NULL)
    {
        m_Hero->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
}


void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
    
   if(m_Hero!= NULL)
    {
       m_Hero->mouseLeftClickUpEvent(aPositionX, aPositionY);
    
   }
   
     /*   for(int i = 0; i < m_Hero.size(); i++)
        {
            m_Hero.at(i)->mouseLeftClickUpEvent(aPositionX, aPositionY);
        }
      */
}

void Level::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_R)
    {
        reset();
    }
    else if(keyCode == KEYCODE_S)
    {
        togglePaintTileScoring();
    }
    else if(keyCode == KEYCODE_I)
    {
        togglePaintTileIndexes();
    }
    else if(keyCode == KEYCODE_L)
    {
        togglePaintTileScoring();
    }
    else if(keyCode == KEYCODE_ESCAPE)
    {
        exit(0);
    }
    
    else if(keyCode == KEYCODE_D)
    {
        if(m_Hero != NULL)
        {
            m_Hero->getPathFinder()->togglePathFindingDelay();
        }
    }
    else
    {
        if(m_Hero != NULL)
        {
            m_Hero->keyUpEvent(keyCode);
        }
    }
}

void Level::load(const char* levelName)
{

    //If the level name isn't NULL load the level from the filesystem,
    //if it is NULL load an empty level with just ground tiles
    if(levelName != NULL)
    {
        //TODO: save the level
       
        std::ifstream inputStream;
        inputStream.open(levelName, std::ifstream::in | std::ifstream::binary);
        
        
        if(inputStream.is_open() == true)
        {
            inputStream.seekg(0,inputStream.end);
            long long bufferSize = inputStream.tellg();
            inputStream.seekg(0, inputStream.beg);
            
            char * buffer = new char [bufferSize];
            
            inputStream.read(buffer, (int)bufferSize);
            inputStream.close();
            
            for (int i = 0; i < bufferSize; i++)
            {
                PickupType pickupType = PickupTypeUnknown;
                if((buffer[i] & PickupTypeAmmo) > 0)
                {
                    pickupType = PickupTypeAmmo;
                    
                    buffer[i] &= ~PickupTypeAmmo;
                                
                }
                setTileTypeAtIndex((TileType)buffer[i], i);
                setPickupTypeAtIndex(pickupType, i);
            }
            delete [] buffer;
            buffer = NULL;  
            
        }
    }
    else
    {
        //Tile variables
        int tileIndex = 0;
        float tileX = 0.0f;
        float tileY = 0.0f;

        //Cycle through all the tiles and create them
        for(int v = 0; v < getNumberOfVerticalTiles(); v++)
        {
            for(int h = 0; h < getNumberOfHorizontalTiles(); h++)
            {
                //The empty level will contain only ground tiles
                m_Tiles[tileIndex] = new GroundTile();
                m_Tiles[tileIndex]->setPosition(tileX, tileY);
                m_Tiles[tileIndex]->setSize(m_TileSize, m_TileSize);
                
              
                tileIndex++;

                //And increment the tile x position
                tileX += m_TileSize;
            }

            //Increment the tile y position and reset the tile x position, since we started a new row
            tileY += m_TileSize;
            tileX = 0.0f;
        }
    }
    
    //The level is loaded, reset everything
    reset();
}

void Level::save(const char* levelName)
{
    {
        int bufferSize = getNumberOfTiles();
        char * buffer = new char [bufferSize];
        
        for (int i = 0; i < bufferSize; i++)
        {
            buffer[i] = (char)getTileTypeForIndex(i);
            
            if(m_Tiles[i]->getPickup() !=NULL && m_Tiles[i]->getPickup()->getPickupType() != PickupTypeUnknown)
            {
                buffer[i] |= m_Tiles[i]->getPickup()->getPickupType();
            
            }
        }
        
        std::ofstream outputStream;
        outputStream.open(levelName, std::ofstream::out | std::ofstream::binary);
     
        
        
        if(outputStream.is_open() == true)
        {
            outputStream.write(buffer, bufferSize);
            outputStream.close();
            
        }
        delete [] buffer;
        buffer = NULL;    
        
    }
}

TileType Level::getTileTypeForIndex(int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        return m_Tiles[index]->getTileType();
    
    }
    return TileTypeUnknown;
}

PickupType Level::getPickupTypeForIndex(int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        if(m_Tiles[index] ->getPickup() != NULL)
        {
            return m_Tiles[index]->getPickup()->getPickupType();
        }
    }
    return PickupTypeUnknown;
}

unsigned int Level::getNumberOfTiles()
{
    return getNumberOfHorizontalTiles() * getNumberOfVerticalTiles();
}

unsigned int Level::getNumberOfHorizontalTiles()
{
	return m_HorizontalTiles;
}

unsigned int Level::getNumberOfVerticalTiles()
{
	return m_VerticalTiles;
}

bool Level::validateTileCoordinates(int aCoordinatesX, int aCoordinatesY)
{
    if(aCoordinatesX < 0 || aCoordinatesY < 0 || aCoordinatesX >= getNumberOfHorizontalTiles() || aCoordinatesY >= getNumberOfVerticalTiles())
	{
        return false;
    }
    return true;
}

int Level::getTileCoordinateForPosition(int aPosition)
{
	return (aPosition / m_TileSize);
}

int Level::getTileIndexForPosition(int aPositionX, int aPositionY)
{
	int coordinatesX = getTileCoordinateForPosition(aPositionX);
	int coordinatesY = getTileCoordinateForPosition(aPositionY);
	return getTileIndexForCoordinates(coordinatesX, coordinatesY);
}

int Level::getTileIndexForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	//Validate the coordinates, then calculate the array index
	if(validateTileCoordinates(aCoordinatesX, aCoordinatesY) == true)
	{
		return aCoordinatesX + (aCoordinatesY * getNumberOfHorizontalTiles());
	}
    
	return -1;
}

int Level::getTileIndexForTile(Tile* aTile)
{
	return getTileIndexForPosition(aTile->getX(), aTile->getY());
}

int Level::getTileIndexForPlayer(Player* player)
{
    return getTileIndexForCoordinates(player->getX(), player->getY());
}


Tile* Level::getTileForPosition(int aPositionX, int aPositionY)
{
	return getTileForIndex(getTileIndexForPosition(aPositionX, aPositionY));
}

Tile* Level::getTileForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	return getTileForIndex(getTileIndexForCoordinates(aCoordinatesX, aCoordinatesY));
}

Tile* Level::getTileForIndex(int aIndex)
{
    //Safety check the index bounds
	if(aIndex >= 0 && aIndex < getNumberOfTiles())
	{
		return m_Tiles[aIndex];
	}
    
    //If we got here, it means the index passed in was out of bounds
	return NULL;
}
Tile* Level::getTileForPlayer(Player *player)
{
    return getTileForPosition(player->getX(), player->getY());
}

void Level::setTileTypeAtPosition(TileType tileType, int positionX, int positionY)
{
    setTileTypeAtIndex(tileType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY)
{
    setTileTypeAtIndex(tileType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTileTypeAtIndex(TileType tileType, int index)
{
    //Safety check the index
    if(index >= 0 && index < getNumberOfTiles())
	{
        //Don't replace the tile if its the same type of tile that already exists
        if(m_Tiles[index]->getTileType() == tileType)
        {
            return;
        }
    
        //Delete the tile at the index, if one exists
        if(m_Tiles[index] != NULL)
        {
            delete m_Tiles[index];
            m_Tiles[index] = NULL;
        }
        
        //Create the new tile based on the TileType
        switch (tileType)
        {
            case TileTypeGround:
                m_Tiles[index] = new GroundTile();
                break;
                
            case TileTypeWater:
                m_Tiles[index] = new WaterTile();
                break;
                
            case TileTypeTree:
                m_Tiles[index] = new TreeTile();
                break;
                
            case TileTypeRock:
                m_Tiles[index] = new RockTile();
                break;
                
            case TileTypeBush:
                m_Tiles[index] = new BushTile();
                break;
                
            case TileTypeLava:
                m_Tiles[index] = new LavaTile();
                break;
                
            case TileTypeUnknown:
            default:
                m_Tiles[index] = NULL;
                break;
        }
        
        //Calculate the coordinates and set the tile position and size
        int coordinateX = (index % getNumberOfHorizontalTiles());
        int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
        m_Tiles[index]->setPosition(coordinateX  * m_TileSize, coordinateY * m_TileSize);
        m_Tiles[index]->setSize(m_TileSize, m_TileSize);
	}
}
void Level::clearLevel()
{
    for(int i = 0; i < getNumberOfTiles(); i++)
    {
        //set All tiles to the ground tile
        setTileTypeAtIndex(TileTypeGround,i);
    }
}
void Level::EnemyDead()
{
    m_EnemyCounter -= 1;
    Log::debug("", m_EnemyCounter);
}


void Level::setPickupTypeAtPosition(PickupType pickupType, int positionX, int positionY)
{
    setPickupTypeAtIndex(pickupType, getTileIndexForPosition(positionX, positionY));
}

void Level::setPickupTypeAtCoordinates(PickupType pickupType, int coordinateX,int coordinateY)
{
    setPickupTypeAtIndex(pickupType, getTileIndexForCoordinates(coordinateX,coordinateY));
}

void Level::setPickupTypeAtIndex(PickupType pickupType, int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        if(m_Tiles[index] != NULL && m_Tiles[index]->getPickup() != NULL)
        {
            if(m_Tiles[index]->getPickup()->getPickupType() == pickupType)
            {
                return;
            }
        }
        if(m_Tiles[index] != NULL)
        {
            if(m_Tiles[index]->getPickup() !=NULL)
            {
                m_Tiles[index]->setPickup(NULL);
            }
            switch (pickupType)
            {
                case PickupTypeAmmo:
            {
                    GDRandom random;
                    random.randomizeSeed();
                    int min = 5;
                    int max = 50;
                    int ammo = min+ random.random(max-min);
            
                    m_Tiles[index]->setPickup(new AmmoPickup(ammo));
            }
                    break;
                    
                case PickupTypeUnknown:
                default:
                break;
            }
            if(m_Tiles[index]->getPickup() != NULL)
            {
                int coordinateX = (index % getNumberOfHorizontalTiles());
                int coordinateY = ((index - coordinateX)/ getNumberOfHorizontalTiles());
                Pickup* pickup = m_Tiles[index]->getPickup();
                float x = (coordinateX * m_TileSize + (m_TileSize - pickup->getWidth())) / 2.0f;
                float y = (coordinateY * m_TileSize) + (m_TileSize - pickup->getHeight()) / 2.0f;
                pickup->setPosition(x, y);
            }
        }
    }
}

void Level::togglePaintTileScoring()
{
    m_PaintTileScoring = !m_PaintTileScoring;
}

void Level::togglePaintTileIndexes()
{
    m_PaintTileIndexes = !m_PaintTileIndexes;
}

void Level::setSelectedTileIndex(int aSelectedIndex)
{
	//Deselect the previously selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(false);
	}
    
	//Set the new tile index
	m_SelectedTileIndex = aSelectedIndex;
    
	//Selected the newly selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(true);
	}
}
float Level:: getGameTime()
{
    return m_GameTime;
}
int Level::getSelectedTileIndex()
{
    return m_SelectedTileIndex;
}
Hero*Level::getHero()
{
    return m_Hero;
}
std::vector<Enemy*> Level::getEnemies()
{
    return m_Enemies;
}
void Level::setGameTime(float aGameTime)
{
    aGameTime = m_GameTime;
}

