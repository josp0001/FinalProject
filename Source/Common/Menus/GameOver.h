//
//  GameOver.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__GameOver__
#define __GAM_1514_OSX_Game__GameOver__

#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"

class GameOver: public Screen, public UIButtonListener
{
public:
    GameOver();
    ~GameOver();
    
    const char* getName();
    
    
    void update(double delta);
    void paint();
    void keyUpEvent(int keyCode);
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    
protected:
    void buttonAction(UIButton * button);
    
private:

    OpenGLTexture* m_GameoverScreen;
    UIButton * m_BackButton;
    virtual void buttonIsSelected(UIButton* button);
	bool buttonShouldBeDeselectedOnExit(UIButton* button) { return true; }
};


#endif /* defined(__GAM_1514_OSX_Game__GameOver__) */
