//
//  GameOver.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GameOver.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"



GameOver::GameOver() : m_BackButton(NULL)
{
    m_GameoverScreen = new OpenGLTexture("Gameoverscreen");
    
    m_BackButton = new UIButton(MAIN_CREDIT_BACK);
    m_BackButton->setCenterPosition(getWidth() / 2.0f, getHeight()* MAINMENU_BACK_Y_PERCENTAGE);
    m_BackButton->setListener(this);
    
}
GameOver::~GameOver()
{    //random
    if( m_GameoverScreen != NULL)
    {
       delete  m_GameoverScreen;
         m_GameoverScreen = NULL;
        
    }
}
//changed
const char * GameOver::getName()
{
    return SPLASH_SCREEN_NAME;
}
void GameOver::update(double delta)
{
    
}
void GameOver::paint()
{
    OpenGLRenderer::getInstance()->drawTexture(m_GameoverScreen,0.0f ,0.0f);
    m_BackButton->paint();
    if(m_BackButton != NULL)
    {
        delete m_BackButton;
        m_BackButton = NULL;
    }
}
void GameOver::keyUpEvent(int keyCode)
{
 
}
void GameOver::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    m_BackButton->mouseMovementEvent(positionX, positionY);
    
}
void GameOver::mouseLeftClickUpEvent(float positionX, float positionY)
{
    m_BackButton->mouseLeftClickUpEvent(positionX,positionY);
}
void GameOver::buttonAction(UIButton * button)
{
    if(button == m_BackButton)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
    
}
void GameOver::buttonIsSelected(UIButton* button)
{
    
}