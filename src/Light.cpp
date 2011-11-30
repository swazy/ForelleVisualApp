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

Light::Light(int size){
    
    channels.assign(size, 0);
    adressOffset = 0;
    amount++;

    //pos = Vec3i(
}
Light::Light(){
    
    // default r,g,b
    channels.assign(3, 0);
    adressOffset = 0;
    amount++;
    //pos = Vec3i(
}

int Light::getRed(){
    return channels[0];
}


int Light::getGreen(){
    return channels[1];
}


 int Light::getBlue(){
    return channels[2];
}

void Light::setBlue(int b){
    
    if(b < 0 || b > 255)
        console()<< "New Color for Blue out of Bounds at  "<<typeid( *this ).name() << " number:  " << amount <<endl;
    else
    channels[2] = b;
}

 void Light::setGreen(int g){
    if(g < 0 || g > 255)
         console()<< "New Color for Green out of Bounds at  "<<typeid( *this ).name() << " number:  " << amount <<endl;
    else
    channels[1] = g;
}

 void Light::setRed(int r){
    if(r < 0 || r > 255)
         console()<< "New Color for Red out of Bounds at  " <<typeid( *this ).name()<< " number:  " << amount <<endl;
    else
    channels[0] = r;
}

int Light::getValueAt(int pos){
    
    if(pos < 0 || pos >= channels.size()){
       console()<< "Channelposition out of Bounds. Pos: "<<pos  << " At Light number " << amount <<endl;
    return -1;
    }else
        return channels[pos];
                 
}
int Light::getAmountOfChannels(){
    
    return channels.size();
    
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

