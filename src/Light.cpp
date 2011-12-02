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

Light::Light(const string &name){

    adressOffset = 0;
    amount++;
    this->name = name;
    this->offset = Vec3i(0,0,0);
}
Light::Light(){
    adressOffset = 0;
    amount++;
    this->offset = Vec3i(0,0,0);

}

void Light::setChannels(vector<LightChannel> &channels){
    
    lightChannels = channels;

}

vector<LightChannel>* Light::getChannels(){
    return &lightChannels;
}

void Light::addChannel( LightChannel &channel){
    
    lightChannels.push_back(channel);
    
}


void Light::setChannelValue(const char* channel, int value) throw(InvalidValueException){

    vector<LightChannel>::iterator it;
    
    for(it =lightChannels.begin(); it < lightChannels.end(); it++){
    
        if( it->getSource() == *channel){
            it->setValue(value);
            return;
            
        }
    }
    throw InvalidValueException( "Can't set Channel value, because Channel not found. At Light " + string(name), value);

    
}


int Light::getValueAt(int pos) throw(InvalidValueException){
    
    if(pos < 0 || pos >= lightChannels.size()){
        throw InvalidValueException( "Can't get Value. Channelposition out of Bounds. At Light " + string(name), pos);
    }else
        return lightChannels[pos].getValue();
                 
}
char Light::getSourceAt(int pos) throw(InvalidValueException, InvalidSourceException){
    
    if(pos < 0 || pos >= lightChannels.size()){
        throw InvalidValueException( "Can't get Source. Channelposition out of Bounds. At Light " + string(name), pos);
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

string* Light::getName(){
    return &name;
}

void Light::setPos(Vec3i &pos){
    
    this->pos = pos;
}

Vec3i* Light::getPos(){
    return &pos;
}

Vec3i* Light::getOffset(){
    return &offset;
}



