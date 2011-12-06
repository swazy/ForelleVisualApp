//
//  Light.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifndef LIGHT_H
#define LIGHT_H

#include "cinder/app/AppBasic.h"
#include "LightChannel.h"
using namespace ci;
using namespace std;

typedef boost::shared_ptr<class Light> LightRef;
class Light{
    
    
private: 
    
    vector<LightChannelRef> lightChannels;  
    static int amount;
    int adressOffset;
    string name;
    Vec3i posOffset;
    
public:
    Light();
    Light(const string &name);
    void setChannels(vector<LightChannelRef> & channels);
    void addChannel(LightChannel *channel);
    vector<LightChannelRef>* getChannels();
    int  getAmountOfChannels();
    void setAdressOffset(int o);
    int* getAdressOffset();
    void setChannelValue(const char* channel, int value)throw(InvalidValueException);
    char getSourceAt(int pos) throw(InvalidValueException,InvalidSourceException);
    int getValueAt(int pos) throw(InvalidValueException);
    void setPosOffset(Vec3i posOffset);
    Vec3i* getPosOffset();
    string* getName();
    
    
    
};
#endif