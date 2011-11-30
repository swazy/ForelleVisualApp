//
//  Light.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
using namespace ci;


class Light{
    
    
private: 
    int red, green, blue;
    Vec3i pos;
    
public:
    Light();
    int getRed();
    int getBlue();
    int getGreen();
    void setRed(int r);
    void setBlue(int b);
    void setGreen(int g);
    void setPos(Vec3i pos);
    Vec3i getPos();
    
    
    
};
