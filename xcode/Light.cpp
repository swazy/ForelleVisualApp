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



Light::Light(){
    
    red = 0;
    blue = 0;
    green = 0;
    //pos = Vec3i(
}

int Light::getRed(){
    return red;
}


int Light::getGreen(){
    return green;
}


 int Light::getBlue(){
    return blue;
}

void Light::setBlue(int b){
    
    if(b < 0 || b > 255)
        console()<< "New Color for Blue out of Bounds" << endl;
    else
    blue = b;
}

 void Light::setGreen(int g){
    if(g < 0 || g > 255)
         console()<< "New Color for Green out of Bounds" << endl;
    else
    green = g;
}

 void Light::setRed(int r){
    if(r < 0 || r > 255)
         console()<< "New Color for Red out of Bounds" << endl;
    else
    red = r;
}

void Light::setPos(Vec3i pos){
    
    this->pos = pos;
}

Vec3i Light::getPos(){
    return pos;
}

