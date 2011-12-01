//
//  Light.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "cinder/app/AppBasic.h"

using namespace std;
using namespace ci;
using namespace ci::app;


#include "Light.h"

int Light::amount = 0;

Light::Light( const char* sources){
    
    for(int i=0; i < strlen(sources); i++){
        lightChannels.push_back( LightChannel(sources[i]));

    }
       adressOffset = 0;
    amount++;

    //pos = Vec3i(
}
Light::Light(){
    
    // default r,g,b
    lightChannels.push_back( LightChannel('r'));
    lightChannels.push_back( LightChannel('g'));
    lightChannels.push_back( LightChannel('b'));
    adressOffset = 0;
    amount++;
    //pos = Vec3i(
}

void Light::setChannelValue(const char* channel, int value){

    vector<LightChannel>::iterator it;
    
    for(it =lightChannels.begin(); it < lightChannels.end(); it++){
    
        if( it->getSource() == *channel){
            it->setValue(value);
            return;
            
        }
    }
    console()<< "Can't set Channel value, because Channel not found.  " << " At Light number " << amount <<endl;

    
}


int Light::getValueAt(int pos){
    
    if(pos < 0 || pos >= lightChannels.size()){
       console()<< "Channelposition out of Bounds. Pos: "<<pos  << " At Light number " << amount <<endl;
    return -1;
    }else
        return lightChannels[pos].getValue();
                 
}
const char Light::getChannelAt(int pos){
    
    if(pos < 0 || pos >= lightChannels.size()){
        console()<< "Channelposition out of Bounds. Pos: "<<pos  << " At Light  " << "Define Name"<<endl;
        return 0;
    }else
        return lightChannels[pos].getSource();
    
    
}
int Light::getAmountOfChannels(){
    
    return lightChannels.size();
    
}

void Light::setAdressOffset(int o){
    
    adressOffset = o;
    
}

int Light::getAdressOffset(){
    return adressOffset;
}
void Light::setPos(Vec3i pos){
    
    this->pos = pos;
}

Vec3i Light::getPos(){
    return pos;
}

