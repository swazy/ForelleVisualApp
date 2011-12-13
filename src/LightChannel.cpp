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
    source = "";
    name = "";
    posOffset = Vec3i(0,0,0);
    
    
} 

LightChannel::LightChannel( const string &name,  char source)throw (InvalidSourceException){
    

    if(strcmp(&source,"R") || strcmp(&source,"G") || strcmp(&source,"B") || strcmp(&source,"A") )
        this->source = source;
    else
        throw InvalidSourceException("Source must be R,G,B or A ", source);

    value   = 10;
    this->name = name;
    this->posOffset = Vec3i(0,0,0);

    
} 
Vec3i* LightChannel::getPosOffset(){
    return &posOffset;
}
void LightChannel::setPosOffset(Vec3i posOffset){
    this->posOffset = posOffset;
}

int LightChannel::getValue(){
    return value;
}
string* LightChannel::getName(){
    return &name;
}
const char* LightChannel::getSource(){
    // char * buffer = new char[source.length()];
    //strcpy(buffer,source.c_str());
    
    //return &buffer[0];
    return source.c_str();
}

string* LightChannel::getSourceAsString(){
    return &source;
}
void LightChannel::setValue(int value)throw(InvalidValueException){
    
    if(value < 0 || value > 255)
        throw InvalidValueException( "Value must be between 0 and 255. At Channel " + string(name), value);
    else
    this->value = value;
}
void LightChannel::setSource( const char &source) throw(InvalidSourceException){
    if(source == 'R' || source == 'G' || source == 'B' || source == 'A' )
        this->source = source;
    else
        throw InvalidSourceException("Source must be R,G,B or A ", source);
    

}

