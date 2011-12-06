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

Group::Group(const string &name ){
    
    adressOffset =0;
    this->name = name;
    setPosOffset(Vec3i(0,0,0));
    

}


void Group::setAdressOffset(int a){
    
    
    adressOffset = a;
    
    
}
int Group::getAdressOffset(){
    
    return adressOffset;
    
}
void Group::setPosOffset(Vec3i posOffset){
    this->posOffset = posOffset;
}
Vec3i* Group::getPosOffset(){
    return &posOffset;
}

void Group::addLight( Light *light){
    
    
    int usedChannels = getUsedChannels();
    light->setAdressOffset(usedChannels);
    lights.push_back(LightRef(light));
    
}
//Light* Group::getLight(int pos)throw(InvalidValueException){
//    
//    if(pos <0 || pos >= lights.size()){
//       throw InvalidValueException( "Can't get light. Pos out of Bounds. At Group " + string(name), pos);
//    }
//       else
//           return &lights.at(pos);
//    
//}

int Group::getUsedChannels(){
    
    // calculate next free channels
    //last pushed light adressoffset + amount of channels

    if(lights.size() > 0)
        return (*lights.back()).getAdressOffset() + (*lights.back()).getAmountOfChannels();
    else
        return 0;
    
    
}
vector<LightRef>* Group::getLights(){
    
    return &lights;
}
string* Group::getName(){
    return &name;
}


