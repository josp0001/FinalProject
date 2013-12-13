//
//  SaveMenu.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-15.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__SaveMenu__
#define __GAM_1514_OSX_Game__SaveMenu__

#include "Menu.h"

class LevelEditor;
class Game;

class SaveMenu : public Menu
{
public:
    SaveMenu();
    ~SaveMenu();
    
    const char* getName();
    void isSaving(const char* returnScreen);
    void isLoading(const char* returnScreen);
    
    
private:
    void buttonAction(UIButton* button);
    
    LevelEditor* m_LevelEditor;
    Game* m_Game;
    
    bool m_IsSaving;
    const char* m_ReturnScreen;
  
};
#endif