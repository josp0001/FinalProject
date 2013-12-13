//
//  Pickup.h
//  GAM-1514 OSX Game
//
//  Created by Marc Jospeh on 2013-11-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__Pickup__
#define __GAM_1514_OSX_Game__Pickup__

#include"../GameObject.h"
#include"../../Constants/Constants.h"


class Pickup : public GameObject
{
public:
    Pickup(PickupType pickupType);
    virtual ~Pickup();
    
    virtual void update(double detla);
    virtual void paint() = 0;
    virtual void reset();
    
    virtual const char* getType() = 0;
    
    virtual PickupType getPickupType();
    
protected:
    PickupType m_PickupType;
    
};
#endif /* defined(__GAM_1514_OSX_Game__Pickup__) */
