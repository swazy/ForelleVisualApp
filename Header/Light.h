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
using namespace std;


class Light{
    
    
private: 
    
    vector<LightChannel> lightChannels;  
    Vec3i pos;
    static int amount;
    int adressOffset;
    string name;
    Vec3i offset;
    
public:
    Light();
    Light(const string &name);
    Vec3i* getOffset();
    void setChannels(vector<LightChannel> & channels);
    void addChannel(LightChannel &channel);
    vector<LightChannel>* getChannels();
    int  getAmountOfChannels();
    void setAdressOffset(int o);
    int getAdressOffset();
    void setChannelValue(const char* channel, int value)throw(InvalidValueException);
    char getSourceAt(int pos) throw(InvalidValueException,InvalidSourceException);
    int getValueAt(int pos) throw(InvalidValueException);
    void setPos(Vec3i &pos);
    Vec3i* getPos();
    string* getName();
    
    
    
};
