//
//  Light.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "LightChannel.h"
using namespace ci;


class Light{
    
    
private: 
    
    std::vector<LightChannel> lightChannels;  
    Vec3i pos;
    static int amount;
    int adressOffset;
    
public:
    Light();
    Light(const char* sources);
    int  getAmountOfChannels();
    void setAdressOffset(int o);
    int getAdressOffset();
    void setChannelValue(const char* channel, int value);
    const char getChannelAt(int pos);
    int getValueAt(int pos);
    void setPos(Vec3i pos);
    Vec3i getPos();
    
    
    
};
