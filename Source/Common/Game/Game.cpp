#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Math/GDRandom.h"
#include "../Math/GDRandomSearch.h"
#include "../UI/UIFont.h"



Game::Game():

m_TilesMenu(NULL),
m_SecondaryMenu(NULL),
m_IsMouseDown(false),
m_SelectedTileIndex(-1),
GameSpeed(1)

{
    m_TilesMenu = new UISideMenu(this, SideMenuRight);
    m_TilesMenu->addButton(new UIButton("Tower"));
    m_TilesMenu->addButton(new UIToggle("MenuTileTower1"));
    m_TilesMenu->addButton(new UIButton("ButtonRANGE"));
    
    m_SecondaryMenu = new UISideMenu(this, SideMenuLeft);
    m_SecondaryMenu->addButton(new UIButton("ButtonExit"));
    m_SecondaryMenu->addButton(new UIButton("FastForward1"));
    m_SecondaryMenu->addButton(new UIButton("FastForward2"));
    m_SecondaryMenu->addButton(new UIButton("FastForward4"));
    //Create the level object
    
     m_Level = new Level();
     m_Font = new UIFont("Fonties");
    
    //Reset everything
    reset();
    GDRandomSearch search(10);
    for(int i = 0; i < 10; i++)
    {
        Log::trace("%i", search.getNext());        
    }
    
}

Game::~Game()
{
    //Delete the level object
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
    if(m_Font != NULL)
    {
        delete m_Font;
        m_Font = NULL;
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
}

void Game::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta*GameSpeed);
         
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

void Game::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }
    if(m_Font != NULL)
    {
        m_Font->draw(ScreenManager::getInstance()->getScreenWidth() / 4.0f, ScreenManager::getInstance()->getScreenHeight() * .05f);
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

void Game::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }

}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

Level* Game::getLevel()
{
    return m_Level;
}

void Game::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    if(m_Level != NULL)
    {
        m_Level->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
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
        m_Level->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
        if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
        {
            TileType types[] = {TileTypeTower};
            TileType type = types[m_SelectedTileIndex];
            
            //paints the tile
            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
}

void Game::mouseLeftClickUpEvent(float positionX, float positionY)
{
    (m_IsMouseDown = false);
    
    //Safety check the level pointer, then set the new tile type in the index
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
        {
            TileType types[] = {TileTypeTower};
            TileType type = types[m_SelectedTileIndex];
            
            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
        if(m_TilesMenu->isShowing() != true)
        {
            m_Level->mouseLeftClickUpEvent(positionX, positionY);
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

void Game::keyUpEvent(int keyCode)
{
    if(m_Level != NULL)
    {
        m_Level->keyUpEvent(keyCode);
    }
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
    else if(keyCode == KEYCODE_P)
    {
        if(m_GameISPaused == false)
        {
            m_GameISPaused = true;
        }
        else
        {
            m_GameISPaused = false;
        }
    }
    else
    {
        if(m_Level != NULL)
        {
            m_Level->keyUpEvent(keyCode);
        }
    }
}
void Game::mouseLeftClickDownEvent(float positionX, float positionY)
{
    //Set the mouse down flag
    m_IsMouseDown = true;
} 
void Game::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
    if(buttonIndex == 0)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
    if(buttonIndex == 1)
    {
        GameSpeed = 1;
    }
    if(buttonIndex == 2)
    {
        GameSpeed = 2;
    }
    if(buttonIndex == 3)
    {
        GameSpeed = 5;
    }
  
}
void Game::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
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
