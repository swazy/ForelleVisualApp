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
    
    adressOffset =0;
    
}


void Group::setAdressOffset(int a){
    
    
    adressOffset = a;
    
    
}
int Group::getAdressOffset(){
    
    return adressOffset;
    
}
void Group::addLightWithChannels(const char * channels){
    
    Light l = Light(channels);
    
    int usedChannels = getUsedChannels();
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

int Group::getUsedChannels(){
    
    // calculate next free channels
    //last pushed light adressoffset + amount of channels

    if(lights.size() > 0)
        return lights.back().getAdressOffset() + lights.back().getAmountOfChannels();
    else
        return 0;
    
    
}
vector<Light>* Group::getLights(){
    
    return &lights;
}

