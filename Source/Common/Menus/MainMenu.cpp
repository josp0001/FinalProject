//
//  MainMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MainMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Menus/SaveMenu.h"  



MainMenu::MainMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("ButtonLoadLevel"));
    addButton(new UIButton("ButtonLevelEditor"));
    addButton(new UIButton("ButtonExit"));
}

MainMenu::~MainMenu()
{

}

const char* MainMenu::getName()
{
    return MAIN_MENU_SCREEN_NAME;
}

void MainMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
        
        SaveMenu* saveMenu = (SaveMenu*)ScreenManager::getInstance()->getScreenForName(SAVE_MENU_SCREEN_NAME);
        saveMenu->isLoading(GAME_SCREEN_NAME);
        ScreenManager::getInstance()->switchScreen(GAME_SETTING_SCREEN);
      
    }
    else if(index == 1)
    {
        ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
    else if (index == 2)
    {
        exit(1);
    }
}
