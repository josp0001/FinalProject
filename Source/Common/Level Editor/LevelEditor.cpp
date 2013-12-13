//
//  LevelEditor.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "LevelEditor.h"
#include "../Constants/Constants.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"
#include "../Menus/SaveMenu.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

LevelEditor::LevelEditor() :
 
m_TilesMenu(NULL),
m_SecondaryMenu(NULL),
m_SaveMenu(NULL),
m_Level(NULL),
m_IsMouseDown(false),
m_SelectedTileIndex(-1)
{
    //Create the Tiles menu items
    
    m_TilesMenu = new UISideMenu(this, SideMenuRight);
    m_TilesMenu->addButton(new UIToggle("MenuTileGround"));
    m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
    m_TilesMenu->addButton(new UIToggle("MenuTileTree"));
    m_TilesMenu->addButton(new UIToggle("MenuTileRock"));
    m_TilesMenu->addButton(new UIToggle("MenuTileBush"));
    m_TilesMenu->addButton(new UIToggle("MenuTileLava"));
    //left side menu
    m_SecondaryMenu = new UISideMenu(this, SideMenuLeft);
    m_SecondaryMenu->addButton(new UIButton("ButtonClear"));
    m_SecondaryMenu->addButton(new UIButton("ButtonSave"));
    m_SecondaryMenu->addButton(new UIButton("ButtonLoad"));
    m_SecondaryMenu->addButton(new UIButton("ButtonExit"));
    //saves
    m_SaveMenu = new UISideMenu(this, SideMenuLeft);
    m_SaveMenu->addButton(new UIButton("SaveButton1"));
    m_SaveMenu->addButton(new UIButton("SaveButton2"));
    m_SaveMenu->addButton(new UIButton("SaveButton3"));
    m_SaveMenu->addButton(new UIButton("SaveButton4"));
    m_SaveMenu->addButton(new UIButton("SaveButton5"));
    m_SaveMenu->addButton(new UIButton("SaveButton6"));
    
    //Create the level object
    m_Level = new Level(true);  
    
    //Reset everything
    reset();
}

LevelEditor::~LevelEditor()
{
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
    
    if(m_TilesMenu != NULL)
    {
        delete m_TilesMenu;
        m_TilesMenu = NULL;
    }
	    
    if(m_SecondaryMenu != NULL)
    {
        delete m_SecondaryMenu;
        m_SecondaryMenu = NULL;
    }
        
    if(m_SaveMenu != NULL)
    {
        delete m_SaveMenu;
        m_SaveMenu = NULL;
    }
}
//new
const char* LevelEditor::getName()
{
    return LEVEL_EDITOR_SCREEN_NAME;
}
void LevelEditor::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }
    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->update(delta);
    }
    
    if(m_SecondaryMenu!= NULL)
    {
        m_SecondaryMenu->update(delta);
    }
}
void LevelEditor::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }
    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->paint();
    }
    
	if(m_SecondaryMenu!= NULL)
    {
        m_SecondaryMenu->paint();
    }
}
void LevelEditor::reset()
{
    if(m_Level != NULL) 
    {
        m_Level->reset();
    }
}
void LevelEditor::save(const char* levelName)
{
//    //Create the buffer
//    int bufferSize = m_Level->getNumberOfTiles();
//    
//    char* buffer = new char[bufferSize];
//    
//    for(int i = 0; i < m_Level->getNumberOfTiles(); i++)
//    {
//        buffer[i] = (char)m_Level->getTileTypeForIndex(i);
//    }
//    
//    // size_t elementSize = sizeof(int);
//    // size_t bufferCount = bufferSize / elementSize;
//    
//    
//    
//    std::ofstream outputStream;
//    
//    //Open the file
//    outputStream.open(levelName, std::ofstream::out | std::ofstream::binary);
//    
//    //Did the file open?
//    if(outputStream.is_open() == true)
//    {
//        //Write the buffer
//        outputStream.write((char*)buffer, bufferSize);
//        
//        //Make sure to close the file stream
//        outputStream.close();
//        
//    }
    
    m_Level->save(levelName);

}

void LevelEditor::load(const char* levelName)
{
     m_Level->load(levelName);
    
}

void LevelEditor::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{    
    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_SecondaryMenu != NULL)
    {
        m_SecondaryMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
        {
            TileType types[] = {TileTypeGround, TileTypeWater, TileTypeTree, TileTypeRock, TileTypeBush, TileTypeLava};
            m_Level->setTileTypeAtPosition(types[m_SelectedTileIndex], positionX, positionY);
        }
    }
}
void LevelEditor::mouseLeftClickDownEvent(float positionX, float positionY)
{
    //Set the mouse down flag
    m_IsMouseDown = true;
}
void LevelEditor::mouseLeftClickUpEvent(float positionX, float positionY)
{
    //Set the mouse up flag
    m_IsMouseDown = false;
    
    //Safety check the level pointer, then set the new tile type in the index
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
        {
            TileType types[] = {TileTypeGround, TileTypeWater, TileTypeTree, TileTypeRock, TileTypeBush, TileTypeLava};
            m_Level->setTileTypeAtPosition(types[m_SelectedTileIndex], positionX, positionY);
        }
    }
    
    //Notify the tiles menu of the mouse event
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
    }
    
    if(m_SecondaryMenu!= NULL)
    {
        m_SecondaryMenu->mouseLeftClickUpEvent(positionX, positionY);
    }

}
void LevelEditor::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_TAB)
    {
        if(m_TilesMenu != NULL)
        {
            m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
        }
    }
    
    if(keyCode == KEYCODE_TAB)  
    {
        if( m_SecondaryMenu!= NULL)
        {
            m_SecondaryMenu->isShowing() == true ?  m_SecondaryMenu->hide() :  m_SecondaryMenu->show();
        }
    }
    else if (keyCode == KEYCODE_T)
    {
        if(m_Level != NULL)
        {
            m_Level->setPickupTypeAtIndex(PickupTypeAmmo, 101);
        }
        
    }
    else if (keyCode == KEYCODE_Y)
    {
        if(m_Level != NULL)
        {
            m_Level->setPickupTypeAtIndex(PickupTypeUnknown, 101);
        }
        
    }
    
    else
    {
        if(m_Level != NULL)
        {
            m_Level->keyUpEvent(keyCode);
        }
    }
    
    if(keyCode == KEYCODE_C)
    {
        m_Level->load(NULL);
    }
    
    else if(keyCode == KEYCODE_S)
    {
        //togglePaintTileScoring();
        save("Level-1.txt");
        save("Level-2.txt");
        save("Level-3.txt");
        save("Level-4.txt");        
        save("Level-5.txt");
        save("Level-6.txt");    
    }

}
void LevelEditor::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
        if(sideMenu ==  m_SecondaryMenu)
    {
        if(buttonIndex == 0)
            
             m_Level->load(NULL);            
         
        else if(buttonIndex == 1)
        {
            SaveMenu* saveMenu = (SaveMenu*)ScreenManager::getInstance()->getScreenForName(SAVE_MENU_SCREEN_NAME);
            saveMenu->isSaving(LEVEL_EDITOR_SCREEN_NAME);
            ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
        }
        else if(buttonIndex == 2)
        {
            SaveMenu* saveMenu = (SaveMenu*)ScreenManager::getInstance()->getScreenForName(SAVE_MENU_SCREEN_NAME);
            saveMenu->isLoading(LEVEL_EDITOR_SCREEN_NAME);
          ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);            
        }
        else if(buttonIndex == 3)
        {
            ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
        }
    }
}
void LevelEditor::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
    if(sideMenu == m_TilesMenu)
    {
        //Un-toggled the previously selected toggle
        UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
        if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        } 
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_TilesMenu->hide();
        m_SecondaryMenu->hide();        
        
    }
    
}
