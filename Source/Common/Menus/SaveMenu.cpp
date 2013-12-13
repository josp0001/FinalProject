//
//  SaveMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-15.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "SaveMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Constants/Constants.h"



SaveMenu::SaveMenu() : Menu(NULL, NULL), m_LevelEditor(NULL)
{
    addButton(new UIButton("SaveButton1"));
    addButton(new UIButton("SaveButton2"));
    addButton(new UIButton("SaveButton3"));
    addButton(new UIButton("SaveButton4"));
    addButton(new UIButton("SaveButton5"));
    addButton(new UIButton("SaveButton6"));
    
 
    m_LevelEditor = (LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME);
    m_Game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
    
    m_IsSaving = false;
    m_ReturnScreen = NULL;
}

SaveMenu::~SaveMenu()
{
    
}

const char* SaveMenu::getName()
{
    return SAVE_MENU_SCREEN_NAME;
}

void SaveMenu::isSaving(const char* returnScreen)
{
    m_ReturnScreen = returnScreen;
    m_IsSaving = true;        
}

void SaveMenu::isLoading(const char* returnScreen)
{
    m_ReturnScreen = returnScreen;
    m_IsSaving = false;
}

void SaveMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(strcmp(m_ReturnScreen, LEVEL_EDITOR_SCREEN_NAME) == 0)
    {
        if(index == 0)
        {
            m_IsSaving == true ? m_LevelEditor->save(T1) : m_LevelEditor->load(T1);
        }
        else if(index == 1)
        {
           m_IsSaving == true ? m_LevelEditor->save(T2) : m_LevelEditor->load(T2);
        }
        else if(index == 2)
        {
            m_IsSaving == true ? m_LevelEditor->save(T3) : m_LevelEditor->load(T3);
        }
        else if(index == 3)
        {
            m_IsSaving == true ? m_LevelEditor->save(T4) : m_LevelEditor->load(T4);
        }
        else if(index == 4)
        {
             m_IsSaving == true ? m_LevelEditor->save(T5) : m_LevelEditor->load(T5);
        }
        else if(index == 5)
        {
            m_IsSaving == true ? m_LevelEditor->save(T6) : m_LevelEditor->load(T6);
        }
    }
    else if(strcmp(m_ReturnScreen, GAME_SCREEN_NAME) == 0)
    {

        if(index == 0)
        
        {
            m_IsSaving == true ? m_Game->getLevel()->save(T1) : m_Game->getLevel()->load(T1);
        }
        else if(index == 1)
        {
          
            m_IsSaving == true ? m_Game->getLevel()->save(T2) : m_Game->getLevel()->load(T2);
        }
        else if(index == 2)
        {
            m_IsSaving == true ? m_Game->getLevel()->save(T3) : m_Game->getLevel()->load(T3);
        }
        else if(index == 3)
        {
            m_IsSaving == true ? m_Game->getLevel()->save(T4) : m_Game->getLevel()->load(T4);
        }
        else if(index == 4)
        {
            m_IsSaving == true ? m_Game->getLevel()->save(T5) : m_Game->getLevel()->load(T5);
        }
        else if(index == 5)
        {
            m_IsSaving == true ? m_Game->getLevel()->save(T6) : m_Game->getLevel()->load(T6);
        }
    }
    ScreenManager::getInstance()->switchScreen(m_ReturnScreen);
}
