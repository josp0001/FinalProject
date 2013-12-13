//
//  AmmoPickup.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__AmmoPickup__
#define __GAM_1514_OSX_Game__AmmoPickup__

#include "Pickup.h"

class AmmoPickup : public Pickup
{
public:
    AmmoPickup(int ammoCount);
    ~AmmoPickup();
    
    void paint();
    
    const char* getType();
    
    int getAmmoCount();
    
private:
    
    int m_AmmoCount;
};

#endif /* defined(__GAM_1514_OSX_Game__AmmoPickup__) */
