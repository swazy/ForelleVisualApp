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
    
    std::vector<int> channels;  
    Vec3i pos;
    static int amount;
    int adressOffset;
    
public:
    Light();
    Light(int size);
    int getRed();
    int getBlue();
    int getGreen();
    void setRed(int r);
    void setBlue(int b);
    void setGreen(int g);
    int  getAmountOfChannels();
    void setAdressOffset(int o);
    int getAdressOffset();
    int getValueAt(int pos);
    void setPos(Vec3i pos);
    Vec3i getPos();
    
    
    
};
