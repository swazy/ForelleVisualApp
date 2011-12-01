//
//  LightChannel.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//




class LightChannel{
    
    
    
private: 
    
    int value;
    char source;
    
public:
    LightChannel();
    LightChannel(const char source);
    int getValue();
    const char getSource();
    void setValue(int value);
    void setSource( const char source);
    
    
};