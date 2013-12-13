//
//  MainMenuBack.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-12-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__MainMenuBack__
#define __GAM_1514_OSX_Game__MainMenuBack__


#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"

class MainMenuBack : public Screen, public UIButtonListener
{
public:
    MainMenuBack();
    ~MainMenuBack();
    
    const char* getName();
    
    
    void update(double delta);
    void paint();
    void keyUpEvent(int keyCode);
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    
protected:
    void buttonAction(UIButton * button);
    
private:
    UIButton* m_PressSpace;
    OpenGLTexture* m_MainBackGround;
    virtual void buttonIsSelected(UIButton* button);
	bool buttonShouldBeDeselectedOnExit(UIButton* button) { return true; }
};


#endif /* defined(__GAM_1514_OSX_Game__MainMenuBack__) */
