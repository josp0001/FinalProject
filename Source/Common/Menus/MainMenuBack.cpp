//
//  MainMenuBack.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MainMenuBack.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"



MainMenuBack::MainMenuBack() : m_PressSpace(NULL)
{ 
    m_MainBackGround = new OpenGLTexture("Background");
    m_PressSpace = new UIButton(SPLASH_PRESS_SPACE);
    m_PressSpace->setCenterPosition(getWidth() / 2.0f, getHeight() *SPLASH_PRESS_SPACE_Y_PERCENTAGE);
    m_PressSpace->setListener(this);
   
}
MainMenuBack::~MainMenuBack()
{
    //random
    if(m_PressSpace != NULL)
    {
        delete m_PressSpace;
        m_PressSpace = NULL;
    }
    if(m_MainBackGround != NULL)
    {
        delete m_MainBackGround;
        m_MainBackGround = NULL;
    }
}
//changed
const char * MainMenuBack::getName()
{
    return SPLASH_SCREEN_NAME;
}
void MainMenuBack::update(double delta)
{
    
}
void MainMenuBack::paint()
{
    OpenGLRenderer::getInstance()->drawTexture(m_MainBackGround,0.0f ,0.0f);
    m_PressSpace->paint();
}
void MainMenuBack::keyUpEvent(int keyCode)
{
    if (keyCode == KEYCODE_SPACE)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
        
    }
}
void MainMenuBack::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    m_PressSpace->mouseMovementEvent(positionX, positionY);
    
}
void MainMenuBack::mouseLeftClickUpEvent(float positionX, float positionY)
{
    m_PressSpace->mouseLeftClickUpEvent(positionX,positionY);
}
void MainMenuBack::buttonAction(UIButton * button)
{
    if(button == m_PressSpace)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
    
}
void MainMenuBack::buttonIsSelected(UIButton* button)
{
    
}