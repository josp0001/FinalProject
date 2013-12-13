#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"
#include "../UI/UISideMenu.h"
#include "../Game/Tiles/Tile.h"

class GameObject;
class Level;
class UIFont;

class Game : public Screen, public UISideMenuListener
{
public:
  Game();
  ~Game();

  //Game lifecycle methods
  void update(double delta);
  void paint();
  void reset();

  //Screen name, must be implemented, it's a pure
  //virtual method in the Screen class
  const char* getName();
  
  Level* getLevel();

private:
  //Mouse Events
  void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
  void mouseLeftClickUpEvent(float positionX, float positionY);
  void keyUpEvent(int keyCode);
  void mouseLeftClickDownEvent(float positionX, float positionY);

  void sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex);
  void sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex);
  //Level pointer
  Level* m_Level;
  UIFont* m_Font;
  UISideMenu* m_TilesMenu;
  UISideMenu* m_SecondaryMenu;
  bool m_IsMouseDown;
  bool m_IsPlaced;
  int m_SelectedTileIndex;
  void buttonAction(UIButton* button);
  bool isPlayerWalkable;
  short GameSpeed;
  bool m_GameISPaused;

    
    
};

#endif