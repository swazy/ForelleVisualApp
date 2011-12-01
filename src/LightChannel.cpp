//
//  LightChannel.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "LightChannel.h"

using namespace std;


LightChannel::LightChannel(){
    
    value = 0;
    source = '0';
    
    
} 

LightChannel::LightChannel( char source){
    
    value = 0;
    this->source = source;

    
} 
int LightChannel::getValue(){
    return value;
}
const char LightChannel::getSource(){

    return source;
}
void LightChannel::setValue(int value){
    
    if(value < 0 || value > 255)
        cinder::app::console()<< "Value must be between 0 and 255 "<<endl;
    else
    this->value = value;
}
void LightChannel::setSource( const char source){
    if(source != 'r' || source != 'g' || source != 'b' || source != 'a' )
        cinder::app::console()<< "Source must be r,g,b or a "<<endl;
    else
    this->source = source;
}
