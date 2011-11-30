//
//  Controller.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "Controller.h"
#include "cinder/app/AppBasic.h"

using namespace std;
using namespace ci;
using namespace ci::app;


const int MAX_DMX_CHANNELS = 512;

Controller::Controller(){
    
    setUniverse(0);

}
Controller::Controller(int u){
    
    setUniverse(u);
    
}

Group* Controller::getGroupAt(int pos){
    
    return &groups[pos];
}
void Controller::addGroup(){
    
    Group group = Group();
    groups.push_back(group);
}
void Controller::addGroupWithLightsAndChannels(int lights,int channels){
    
   
    int usedChannels = getUsedChannels();
    
  
    Group group = Group();
    group.setAdressOffset(usedChannels);
  
    for(int i=0; i< lights; i++){
        group.addLight(channels);
    }
    
    groups.push_back(group);

    
}
int Controller::getUniverse(){
    
    return universe;
    
}
void Controller::setUniverse(int u){
    
    universe = u;
}

void Controller::printUsedChannels(){
 
    int usedChannels = getUsedChannels();
    
    console() << "Used channels   " << usedChannels << endl;
}
void Controller::setStartAdress(int a){
    
    
    startAdress = a;
    
    
}
int Controller::getStartAdress(){
    
    return startAdress;
    
}
int Controller::getUsedChannels(){
    
    // calculate next free channels
    //last pushed light adressoffset + amount of channels
    
    if(groups.size() > 0)
        return groups.back().getAdressOffset() +groups.back().getUsedChannels();
    else
        return 0;
 
}

void Controller::getData(int *data){

    vector<Group>::iterator it;
    
    
    for(it = groups.begin(); it < groups.end(); it++){
    
        vector<Light> *lights = it->getLights();
        vector<Light>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            for(int i=0; i < it2->getAmountOfChannels(); i++){
                    
                // calculate real channel 
                // first with channels in the light = i, + the offset of the light + the offset oh the group
                int channel = i + it2->getAdressOffset() + it->getAdressOffset();
                
                console() << channel << endl;
                int value = it2->getValueAt(i);
                
                if(value != -1){
                    
                    data[channel] = value;
                }else
                    data[channel] = 0;

                
                
            }
            
        }
    }
    
    
}

