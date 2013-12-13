//
//  PathFinder.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "PathFinder.h"
#include "PathNode.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>



PathFinder::PathFinder(Level* level, PathFinderListener* listener) :
    m_Level(level),
    m_Listener(listener),
    m_State(StateIdle),
    m_DestinationTileIndex(-1),
    m_SearchDelay(0.0),
    m_EnableSearchDelay(false)
{

}

PathFinder::~PathFinder()
{
    clearPathNodes();
}

void PathFinder::findPath(Tile* aCurrentTile, Tile* aDestinationTile)
{
    if (m_State != StateIdle)
    {
        return;
    }
    
    //
    for (int i = 0; i < m_Level->getNumberOfTiles(); i++)
    {
        Tile* tile = m_Level->getTileForIndex(i);
        if (tile != NULL && tile->isWalkableTile() == true)
        {
            tile->setIsPath(false);
        }
    }
    
    clearPathNodes();
    
    int currentTileIndex = m_Level->getTileIndexForTile(aCurrentTile);
    m_DestinationTileIndex = m_Level->getTileIndexForTile(aDestinationTile);
    
    if (currentTileIndex == m_DestinationTileIndex)
    {
        return;
    }
    
    if(aDestinationTile->isWalkableTile() == false)
    {
        return;
    }
    
    PathNode* pathNode = new PathNode(aCurrentTile);
    addPathNodeToOpenList(pathNode);
    
    m_State = StateSearchingPath;
    m_SearchDelay = 0.0;
    
    
}

void PathFinder::update(double aDelta)
{
    if(m_SearchDelay > 0.0)
    {
        m_SearchDelay -= aDelta;
        if(m_SearchDelay <= 0.0)
        {
            m_SearchDelay = 0.0;
        }
        return;
    }
    
    //if for slower animationg
    while (isSearchingPath() == true && m_DestinationTileIndex != -1)
    {
        //safety check that there is somethijg in O list
        if (m_PathNodeOpen.size() == 0)
        {
            m_State = StateError;
            
            if (m_Listener != NULL)
            {
                m_Listener->pathFinderFinishedSearching(this, false);
            }
            
            return;
        }
        
        //get the node with the lowest F score deom that list
        //it should be the first eleement
        PathNode* currentNode = m_PathNodeOpen.front();
        
        m_PathNodeClosed.push_back(currentNode);
        m_PathNodeOpen.erase(m_PathNodeOpen.begin());
        
        
        
        //add node to the closed list and removed it from the open list
        int currentNodeTileIndex = m_Level->getTileIndexForTile(currentNode->getTile());
        
        if(currentNodeTileIndex == m_DestinationTileIndex)
        {
            buildFinalNodePath(currentNode);
            
            m_State = StateFoundPath;
            
            if (m_Listener != NULL)
            {
                m_Listener->pathFinderFinishedSearching(this, true);
            }
            return;
        }
        
        //check to see if the node is at the destination tile
        std::vector<Tile*> adjecentTiles;
        
        addAdjacentTile(adjecentTiles, currentNode->getTile(), 0, -1);
        addAdjacentTile(adjecentTiles, currentNode->getTile(), 0, 1);
        addAdjacentTile(adjecentTiles, currentNode->getTile(), -1, 0);
        addAdjacentTile(adjecentTiles, currentNode->getTile(), 1, -0);
        
        //if it is, stop search and build final path
        for (int i = 0; i < adjecentTiles.size(); i++)
        {
            Tile* adjecentTile = adjecentTiles.at(i);
            
            if(doesTileExistInClosedList(adjecentTile))
            {
                continue;
            }
            
            if(doesTileExistInOpenList(adjecentTile) == false)
            {
                PathNode* adjecentNode = new PathNode(adjecentTile);
                adjecentNode->setParentNode(currentNode);
                adjecentNode->setScoreG(currentNode->getScoreG() +adjecentTile->getMovementCost());
                
                Tile* destinationTile = m_Level->getTileForIndex(m_DestinationTileIndex);
                int scoreH = getManhattanDistanceCost(adjecentTile, destinationTile);
                adjecentNode->setScoreH(scoreH);
                
                addPathNodeToOpenList(adjecentNode);
            }
            else
            {
                PathNode* existingNode = getOpenPathNodeForTile(adjecentTile);
                
                if(currentNode->getScoreG() + adjecentTile->getMovementCost()< existingNode->getScoreG())
                {
                    existingNode->setScoreG(currentNode->getScoreG() + 1);
                    existingNode->setParentNode(currentNode);
                    
                    sortOpenList();
                }
            }
        }
        
        //if we got here that mena we hvaen;t reachred our destination
        //we need geat the adjecent tiles from athe node and add them tothe open list
        
        
        //check the tile above, is it walkable
        
        //check below is it walksable
        
        //check l is it walksable
        
        //check r is it walksable
        
        //cycle through adjecent tiles that are walkable
        
        //is it in the closed list
        
        //if it does disregard it
        
        //is it in the open list
        
        //if it is not, create pathnode
        
        //set parent node
        
        //calculate g and h scores
        
        //add to open list and sort it
        
        //if it exists in open list compares scores and keep the one with the lowest F OR G score
        
        //if the tile has a lower F update the G score and parent node
        
        //re sort the open list
        
    }
    
    
    //If the search delay is enabled, set the delay timer
    if(m_EnableSearchDelay == true)
    {
        m_SearchDelay = PATH_FINDING_DELAY;
    }
}

void PathFinder::paint()
{
    //Paint the open list path scoring
    for(int i = 0; i < m_PathNodeOpen.size(); i++)
    {
        m_PathNodeOpen.at(i)->paintScore(OpenGLColorRed());
    }
    
    //Paint the closed list path scoring
    for(int i = 0; i < m_PathNodeClosed.size(); i++)
    {
        m_PathNodeClosed.at(i)->paintScore(OpenGLColorBlue());
    }
    
    //Paint the final path scoring
    for(int i = 0; i < m_PathNodeFinal.size(); i++)
    {
        m_PathNodeFinal.at(i)->paintScore(OpenGLColorYellow());
    }
}

void PathFinder::reset()
{
    m_State = StateIdle;
}

void PathFinder::addAdjacentTile(std::vector<Tile*>& aAdjacentTiles, Tile* aCurrentTile, int aDeltaX, int aDeltaY)
{
    int adjecentCoordinatesX = m_Level->getTileCoordinateForPosition(aCurrentTile->getX()) + aDeltaX;
    int adjecentCoordinatesY = m_Level->getTileCoordinateForPosition(aCurrentTile->getY()) + aDeltaY;
    
    Tile* adjecentTile = m_Level->getTileForCoordinates(adjecentCoordinatesX, adjecentCoordinatesY);
    
    if (adjecentTile != NULL)
    {
        bool isWalkable = adjecentTile->isWalkableTile();
        bool isValid = m_Level->validateTileCoordinates(adjecentCoordinatesX, adjecentCoordinatesY);
        
        if (isWalkable && isValid)
        {
            aAdjacentTiles.push_back(adjecentTile);
        }
    }
}

bool PathFinder::doesTileExistInClosedList(Tile* aTile)
{
    //Get the tile index from the level for the tile pointer
    int tileIndex = m_Level->getTileIndexForTile(aTile);
    
    //Cycle through the closed list and compare the tile indexes
    for(int i = 0; i < m_PathNodeClosed.size(); i++)
    {
        PathNode* pathNode = m_PathNodeClosed.at(i);
        if(m_Level->getTileIndexForTile(pathNode->getTile()) == tileIndex)
        {
            return true;
        }
    }
    
    //The tile doesn't exist in the closed list
    return false;
}

bool PathFinder::doesTileExistInOpenList(Tile* aTile)
{
    return getOpenPathNodeForTile(aTile) != NULL;
}

PathNode* PathFinder::getOpenPathNodeForTile(Tile* aTile)
{
    //Get the tile index from the level for the tile pointer
    int tileIndex = m_Level->getTileIndexForTile(aTile);
    
    //Cycle through the open list and compare the tile indexes
    for(int i = 0; i < m_PathNodeOpen.size(); i++)
    {
        PathNode* pathNode = m_PathNodeOpen.at(i);
        if(m_Level->getTileIndexForTile(pathNode->getTile()) == tileIndex)
        {
            return pathNode;
        }
    }
    
    //The tile doesn't exist in the open list, return NULL
    return NULL;
}

bool PathFinder::isSearchingPath()
{
    return m_State == StateSearchingPath;
}

int PathFinder::getPathSize()
{
    return m_PathNodeFinal.size();
}

void PathFinder::sortOpenList()
{
    std::sort(m_PathNodeOpen.begin(), m_PathNodeOpen.end(), PathNode::compareNodes);
}

PathNode* PathFinder::getPathNodeAtIndex(int aIndex)
{
    if(aIndex >= 0 && aIndex < getPathSize())
    {
        return m_PathNodeFinal.at(aIndex);
    }
    return NULL;
}

void PathFinder::addPathNodeToOpenList(PathNode* aPathNode)
{
	//Insert the Path node into the Open path node vector
	m_PathNodeOpen.push_back(aPathNode);
    
    //Sort the open list
    sortOpenList();
}

void PathFinder::buildFinalNodePath(PathNode* aPathNode)
{
	do
	{
        //Safety check the parentNode
		if(aPathNode->getParentNode() != NULL)
		{
			m_PathNodeFinal.insert(m_PathNodeFinal.begin(), aPathNode);
		}
        
		//Set the tile path flag to true
		aPathNode->getTile()->setIsPath(true);
        
		//Set the path node's pointer to it's parent
		aPathNode = aPathNode->getParentNode();
	}
	while (aPathNode != NULL);
}

void PathFinder::clearPathNodes()
{
	//Now cycle through the Open node path vector, and delete all the path node
	while(m_PathNodeOpen.size() > 0)
	{
		//Get the last element in the vector
		PathNode* node = m_PathNodeOpen.back();
        
		//Delete the path node
		delete node;
        
		//Remove the last element in the vector
		m_PathNodeOpen.pop_back();
	}
    
	//Lastly cycle through the Closed node path vector, and delete all the path node
	while(m_PathNodeClosed.size() > 0)
	{
		//Get the last element in the vector
		PathNode* node = m_PathNodeClosed.back();
        
		//Delete the path node
		delete node;
        
		//Remove the last element in the vector
		m_PathNodeClosed.pop_back();
	}
    
    //Clear the final path node list
    m_PathNodeFinal.clear();
    
    //Reset the destination tile index
    m_DestinationTileIndex = -1;
}

void PathFinder::togglePathFindingDelay()
{
    m_EnableSearchDelay = !m_EnableSearchDelay;
}

int PathFinder::getManhattanDistanceCost(Tile* aStartTile, Tile* aDestinationTile)
{
	//Here we use the Manhattan method, which calculates the total number of step moved horizontally and vertically to reach the
	//final desired step from the current step, ignoring any obstacles that may be in the way
	int distance = abs(m_Level->getTileCoordinateForPosition(aDestinationTile->getX()) - m_Level->getTileCoordinateForPosition(aStartTile->getX())) 
    + abs(m_Level->getTileCoordinateForPosition(aDestinationTile->getY()) - m_Level->getTileCoordinateForPosition(aStartTile->getY()));
    
    //Return the distance between the two tiles
	return distance;
}