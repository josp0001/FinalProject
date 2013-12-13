//  GameSettings.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-10-27.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__GameSettings__
#define __GAM_1514_OSX_Game__GameSettings__


#include "Screen.h"
#include "../UI/UIButton.h"

class SettingScreen : public Screen, public UIButtonListener
{
public:
    SettingScreen();
    ~SettingScreen();
    
    const char* getName();
    
    
    void update(double delta);
    void paint();
    void keyUpEvent(int keyCode);
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    
protected:
    void buttonAction(UIButton * button);
    
private:
    
    OpenGLTexture* m_SettingBackground;
    UIButton * m_BackButton;
    UIButton * m_ScoreLimit;
    UIButton * m_TimeLimit;
    UIButton * m_Difficulty;
    UIButton * m_Controls;
    UIButton * m_StartGame;
    UIButton * m_Number5;
    UIButton * m_Number10;
    UIButton * m_Number15;
    UIButton * m_Easy;
    UIButton * m_Medium;
    UIButton * m_Hard;
    virtual void buttonIsSelected(UIButton* button);
};
#endif /* defined(__GAM_1514_OSX_Game__GameSettings__) */
