//
//  GameSettings.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-10-27.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GameSettings.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../OpenGL/OpenGL.h"
#include "../Level Editor/LevelEditor.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../UI/UIButton.h"


SettingScreen::SettingScreen() :
m_BackButton(NULL),
m_ScoreLimit(NULL),
m_TimeLimit(NULL),
m_Difficulty(NULL),
m_Controls(NULL),
m_StartGame(NULL),
m_Number5(NULL),
m_Number10(NULL),
m_Number15(NULL),
m_Easy(NULL),
m_Medium(NULL),
m_Hard(NULL)


{

    
    
    
    m_SettingBackground = new OpenGLTexture(GAME_SETTING_SCREEN);
    
    m_BackButton = new UIButton(MAIN_CREDIT_BACK);
    m_BackButton->setCenterPosition(getWidth() / 2.0f, getHeight()* MAINMENU_BACK_Y_PERCENTAGE);
    m_BackButton->setListener(this);
    
    m_ScoreLimit = new UIButton(MAIN_SCORELIMIT);
    m_ScoreLimit->setCenterPosition(getWidth() / 4.0f, getHeight()* MAINMENU_SCORE_Y_PERCENTAGE);
    m_ScoreLimit->setListener(this);
    
    m_TimeLimit = new UIButton(MAIN_TIMELIMIT);
    m_TimeLimit->setCenterPosition(getWidth() / 4.0f, getHeight()* MAINMENU_TIMELIMIT_Y_PERCENTAGE);
    m_TimeLimit->setListener(this);
    
    m_Difficulty = new UIButton(MAIN_DIFFICULTY);
    m_Difficulty->setCenterPosition(getWidth() / 4.0f, getHeight()* MAINMENU_DIFFICULTY_Y_PERCENTAGE);
    m_Difficulty->setListener(this);
    
    m_Controls = new UIButton(MAIN_CONTROLS);
    m_Controls->setCenterPosition(getWidth() / 4.0f, getHeight()* MAINMENU_CONTROLS_Y_PERCENTAGE);
    m_Controls->setListener(this);
    
    m_StartGame = new UIButton(MAIN_STARTGAME);
    m_StartGame->setCenterPosition(getWidth() / 4.0f, getHeight()* MAINMENU_STARTGAME_Y_PERCENTAGE);
    m_StartGame->setListener(this);
    
    m_Number5= new UIButton(MAIN_SCORENUMBER);
    m_Number5->setCenterPosition(getWidth() * MAINMENU_SCORELIMIT5_X_PERCENTAGE, getHeight()* MAINMENU_SCORELIMIT5_Y_PERCENTAGE);
    m_Number5->setListener(this);
    
    m_Number10= new UIButton(MAIN_SCORENUMBER10);
    m_Number10->setCenterPosition(getWidth() * MAINMENU_SCORELIMIT10_X_PERCENTAGE, getHeight()* MAINMENU_SCORELIMIT10_Y_PERCENTAGE);
    m_Number10->setListener(this);
    
    m_Number15= new UIButton(MAIN_SCORENUMBER15);
    m_Number15->setCenterPosition(getWidth() * MAINMENU_SCORELIMIT15_X_PERCENTAGE, getHeight()* MAINMENU_SCORELIMIT15_Y_PERCENTAGE);
    m_Number15->setListener(this);
    
    m_Easy= new UIButton(MAIN_DIFFICULTYEASY);
    m_Easy->setCenterPosition(getWidth() * MAINMENU_DIFFICULTYEASY_X_PERCENTAGE, getHeight()* MAINMENU_DIFFICULTYEASY_Y_PERCENTAGE);
    m_Easy->setListener(this);
    
    m_Medium= new UIButton(MAIN_DIFFICULTYMEDIUM);
    m_Medium->setCenterPosition(getWidth() * MAINMENU_DIFFICULTYMEDIUM_X_PERCENTAGE, getHeight()* MAINMENU_DIFFICULTYMEDIUM_Y_PERCENTAGE);
    m_Medium->setListener(this);
    
    m_Hard= new UIButton(MAIN_DIFFICULTYHARD);
    m_Hard->setCenterPosition(getWidth() * MAINMENU_DIFFICULTYHARD_X_PERCENTAGE, getHeight()* MAINMENU_DIFFICULTYHARD_Y_PERCENTAGE);
    m_Hard->setListener(this);
    
}
SettingScreen::~SettingScreen()
{
    if(m_SettingBackground!= NULL)
    {
        delete m_SettingBackground;
        m_SettingBackground = NULL;
    }
    
    if(m_BackButton != NULL)
    {
        delete m_BackButton;
        m_BackButton = NULL;
    }
    if(m_ScoreLimit != NULL)
    {
        delete m_ScoreLimit;
        m_ScoreLimit= NULL;
    }
    if(m_TimeLimit != NULL)
    {
        delete m_TimeLimit;
        m_TimeLimit= NULL;
    }
    if(m_Difficulty!= NULL)
    {
        delete m_Difficulty;
        m_Difficulty= NULL;
    }
    if(m_Controls!= NULL)
    {
        delete m_Controls;
        m_Controls= NULL;
    }
    if(m_StartGame!= NULL)
    {
        delete m_StartGame;
        m_StartGame= NULL;
    }
    if(m_Number5!= NULL)
    {
        delete m_Number5;
        m_Number5= NULL;
    }
    if(m_Number10!= NULL)
    {
        delete m_Number10;
        m_Number10= NULL;
    }
    if(m_Number15!= NULL)
    {
        delete m_Number15;
        m_Number15= NULL;
    }
    if(m_Easy != NULL)
    {
        delete m_Easy;
        m_Easy = NULL;
    }
    if(m_Medium!= NULL)
    {
        delete m_Medium;
        m_Medium = NULL;
    }
    if(m_Hard!= NULL)
    {
        delete m_Hard;
        m_Hard = NULL;
    }
}
//changed
const char * SettingScreen::getName()
{
    return GAME_SETTING_SCREEN;
}

void SettingScreen::update(double delta)
{
    
}
void SettingScreen::paint()
{
    OpenGLRenderer::getInstance()->drawTexture(m_SettingBackground,0.0f ,0.0f);
    m_BackButton->paint();
    m_ScoreLimit->paint();
    m_TimeLimit->paint();
    m_Difficulty->paint();
    m_Controls->paint();
    m_StartGame->paint();
    m_Number5->paint();
    m_Number10->paint();
    m_Number15->paint();
    m_Easy->paint();
    m_Medium->paint();
    m_Hard->paint();
}
void SettingScreen::keyUpEvent(int keyCode)
{
    
}
void SettingScreen::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    m_BackButton->mouseMovementEvent(positionX, positionY);
    m_ScoreLimit->mouseMovementEvent(positionX, positionY);
    m_TimeLimit->mouseMovementEvent(positionX, positionY);
    m_Difficulty->mouseMovementEvent(positionX, positionY);
    m_Controls->mouseMovementEvent(positionX, positionY);
    m_StartGame->mouseMovementEvent(positionX, positionY);
    m_Number5->mouseMovementEvent(positionX, positionY);
    m_Number10->mouseMovementEvent(positionX, positionY);
    m_Number15->mouseMovementEvent(positionX, positionY);
    m_Easy->mouseMovementEvent(positionX, positionY);
    m_Medium->mouseMovementEvent(positionX, positionY);
    m_Hard->mouseMovementEvent(positionX, positionY);
}
void SettingScreen::mouseLeftClickUpEvent(float positionX, float positionY)
{
    m_BackButton->mouseLeftClickUpEvent(positionX,positionY);
    m_ScoreLimit->mouseLeftClickUpEvent(positionX,positionY);
    m_TimeLimit->mouseLeftClickUpEvent(positionX,positionY);
    m_Difficulty->mouseLeftClickUpEvent(positionX,positionY);
    m_Controls->mouseLeftClickUpEvent(positionX,positionY);
    m_StartGame->mouseLeftClickUpEvent(positionX,positionY);
    m_Number5->mouseLeftClickUpEvent(positionX,positionY);
    m_Number10->mouseLeftClickUpEvent(positionX,positionY);
    m_Number15->mouseLeftClickUpEvent(positionX,positionY);
    m_Easy->mouseLeftClickUpEvent(positionX,positionY);
    m_Medium->mouseLeftClickUpEvent(positionX,positionY);
    m_Hard->mouseLeftClickUpEvent(positionX,positionY);
    
}
void  SettingScreen::buttonAction(UIButton * button)
{
    if(button == m_BackButton)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
    if(button == m_StartGame)
    {
        ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
    }
}
void SettingScreen::buttonIsSelected(UIButton* button)
{
    
}