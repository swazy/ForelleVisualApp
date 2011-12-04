//
//  LightChannel.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifndef LightChannel_H
#define LightChannel_H

#include "InvalidSourceException.h"
#include "InvalidValueException.h"

using namespace std;
using namespace ci;

class LightChannel{
    
    
    
private: 
    
    int value;
    char source;
    string name;
    Vec3i posOffset;
public:
    LightChannel();
    LightChannel( const string &name,  char source)throw (InvalidSourceException);
    int getValue();
    char getSource();
    void setValue(int value)throw(InvalidValueException);
    void setSource( const char &source)throw(InvalidSourceException);
    string* getName();
    Vec3i* getPosOffset();
    void setPosOffset(Vec3i posOffset);


};
#endif