    //
//  WinMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "../Menus/WinMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


GameComplete::GameComplete() : Menu("WinnerScreen", NULL, true)
{
    addButton(new UIButton("ButtonBack"));
    addButton(new UIButton("ButtonExit"));
}

GameComplete::~GameComplete()
{
    
}

const char* GameComplete::getName()
{
    return MAIN_MENU_WIN_NAME;
}

void GameComplete::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
    else if (index == 1)
    {
        exit(1);
    }
    
}

bool GameComplete::getGameState()
{
    return m_GameState;
}

void GameComplete::setGameState(bool aGameState)
{
    m_GameState = aGameState;
    
}