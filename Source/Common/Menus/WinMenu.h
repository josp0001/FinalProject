//
//  WinMenu.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__WinMenu__
#define __GAM_1514_OSX_Game__WinMenu__
#include "Menu.h"

class GameComplete : public Menu
{
public:
    GameComplete();
    ~GameComplete();
    
    const char* getName();
    
    void setGameState(bool aGameState);
    
    bool getGameState();
    
private:
    void buttonAction(UIButton* button);
    bool m_GameState;
};


#endif /* defined(__GAM_1514_OSX_Game__WinMenu__) */
