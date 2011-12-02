//
//  LightChannel.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "LightChannel.h"



LightChannel::LightChannel(){
    
    value = 0;
    source = '0';
    name = "";
    offset = Vec3i(0,0,0);
    
    
} 

LightChannel::LightChannel( const string &name,  char source){
    
    value = 10;
    if(source != 'R' || source != 'G' || source != 'B' || source != 'A' )
        throw InvalidSourceException("Source must be R,G,B or A ", source);
    else
        this->source = source;

    this->name = name;
    this->offset = Vec3i(0,0,0);

    
} 
Vec3i* LightChannel::getOffset(){
    return &offset;
}

int LightChannel::getValue(){
    return value;
}
string* LightChannel::getName(){
    return &name;
}
char LightChannel::getSource(){
    return source;
}
void LightChannel::setValue(int value)throw(InvalidValueException){
    
    if(value < 0 || value > 255)
        throw InvalidValueException( "Value must be between 0 and 255. At Channel " + string(name), value);
    else
    this->value = value;
}
void LightChannel::setSource( const char &source) throw(InvalidSourceException){
    if(source != 'R' || source != 'G' || source != 'B' || source != 'A'  )
        throw InvalidSourceException("Source must be r,g,b or a ", source);
    else
    this->source = source;
}
