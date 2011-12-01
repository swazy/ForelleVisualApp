//
//  Cluster.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "Cluster.h"
#include "cinder/app/AppBasic.h"

using namespace std;
using namespace ci;
using namespace ci::app;


const int MAX_DMX_CHANNELS = 512;

Cluster::Cluster(){
    
    setUniverse(0);

}
Cluster::Cluster(int u){
    
    setUniverse(u);
    
}

Group* Cluster::getGroupAt(int pos){
    
    return &groups[pos];
}
void Cluster::addGroup(){
    
    Group group = Group();
    groups.push_back(group);
}
void Cluster::addGroupWithLightsAndChannels(int lights,const char* channels){
    
   
    int usedChannels = getUsedChannels();
    
  
    Group group = Group();
    group.setAdressOffset(usedChannels);
  
    for(int i=0; i< lights; i++){
        group.addLightWithChannels(channels);
    }
    
    groups.push_back(group);

    
}
int Cluster::getUniverse(){
    
    return universe;
    
}
void Cluster::setUniverse(int u){
    
    universe = u;
}

void Cluster::printUsedChannels(){
 
    int usedChannels = getUsedChannels();
    
    console() << "Used channels   " << usedChannels << endl;
}
void Cluster::setStartAdress(int a){
    
    
    startAdress = a;
    
    
}
int Cluster::getStartAdress(){
    
    return startAdress;
    
}
int Cluster::getUsedChannels(){
    
    // calculate next free channels
    //last pushed light adressoffset + amount of channels
    
    if(groups.size() > 0)
        return groups.back().getAdressOffset() + groups.back().getUsedChannels();
    else
        return 0;
 
}

void Cluster::getData( uint8_t *data){

    vector<Group>::iterator it;
    
    
    for(it = groups.begin(); it < groups.end(); it++){
    
        vector<Light> *lights = it->getLights();
        vector<Light>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            for(int i=0; i < it2->getAmountOfChannels(); i++){
                    
                // calculate real channel 
                // first with channels in the light = i, + the offset of the light + the offset oh the group
                int channel = i + it2->getAdressOffset() + it->getAdressOffset() + getStartAdress();
                
                int value = it2->getValueAt(i);
               
                console() <</*clustername*/ "Light  " /*<< it2->getName(); */<< "  Channel  " << it2->getChannelAt(i) << "  Value  " <<value << endl; 
                if(value != -1){
                    
                    data[channel] = value;
                }else
                    data[channel] = 0;

                
                
            }
            
        }
    }
    
    
}

