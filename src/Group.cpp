//
//  Group.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"

using namespace std;
using namespace ci;
using namespace ci::app;



#include "Group.h"

Group::Group(){
    
}


void Group::setStartAdress(int a){
    
    
    startAdress = a;
    
    
}
int Group::getStartAdress(){
    
    return startAdress;
    
}
void Group::addLight(int lightSize){
    
    Light l = Light(lightSize);
    
    // calculate next free channels
    //last pushed light adressoffset + amount of channels
    int usedChannels;
    if(lights.size() > 0){
        usedChannels = lights[lights.size()-1].getAdressOffset() + lights[lights.size()-1].getAmountOfChannels();
    }else
        usedChannels = 0;
    console()<< "UsedChannels  " << usedChannels <<endl;
    l.setAdressOffset(usedChannels);
    lights.push_back(l);
    
}
Light* Group::getLight(int pos){
    
    if(pos <0 || pos >= lights.size()){
       console() << "Cant get light. Pos out of Bounds" << endl;
       return NULL;
    }
       else
           return &lights.at(pos);
    
}