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
Cluster::Cluster(const string &name, int u){
    
    setUniverse(u);
    this->name = name;
    startAdress = 0;
    setPos(Vec3i(0,0,0));
    
}

Group* Cluster::getGroupAt(int pos){
    
    if (pos < 0 || pos >= groups.size()) {
        throw InvalidValueException( "Can't get Group. Channelposition out of Bounds.  At Group " + string(name), pos);
    }
    return &groups[pos];
}

void Cluster::addGroup( Group &group){
    
   
    int usedChannels = getUsedChannels();
    group.setAdressOffset(usedChannels);
    groups.push_back(group);

    
}    
void Cluster::setPos(Vec3i pos){
    this->pos = pos;
}  
Vec3i Cluster::getPos(){
    return pos;
}


int Cluster::getUniverse(){
    
    return universe;
    
}
void Cluster::setUniverse(int u)throw(InvalidValueException){
    
    if(u < 0 || u > 3)
         throw InvalidValueException( "Cluster universe must be between 0 and 3.  At Group " + string(name), u);
    else
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



void Cluster::printCluster(){
    
    vector<Group>::iterator it;
    
    console() <<"ClusterName: " <<name <<endl;
    
    for(it = groups.begin(); it < groups.end(); it++){
        console() << "\tGroupName:  " << *it->getName() <<endl;
        vector<Light> *lights = it->getLights();
        vector<Light>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            console() << "\t\tLight  " << *it2->getName() <<endl;
            vector<LightChannel> *channels = it2->getChannels();
            vector<LightChannel>::iterator it3;
            
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
                console() << "\t\t\tChannelSource  " << it3->getSource() << "  ChannelValue  " <<it3->getValue() << endl; 
            }
            
        }
    }
} 
void Cluster::updateAndDrawCluster(Surface &surface){
    
 
    vector<Group>::iterator it;
    int channel = 0;
    
    for(it = groups.begin(); it < groups.end(); it++){
        
       
        vector<Light> *lights = it->getLights();
        vector<Light>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            vector<LightChannel> *channels = it2->getChannels();
            vector<LightChannel>::iterator it3;
            
            //dont forget the channels
            int i = 0;
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
                
                // calculate real channel 
                // first with channels in the light = i, + the offset of the light + the offset oh the group
                channel = i + it2->getAdressOffset() + it->getAdressOffset() + getStartAdress();
                i++;
                
                //add all the offsets, to get the end pos of each channel
                Vec2i pos = getPos().xy() + it->getPosOffset().xy() + it2->getPosOffset().xy() + it3->getPosOffset().xy();
                // get the color of the pixel at pos
                ColorA8u pixel = surface.getPixel(pos.xy());
                
                try {
                                
                    switch (it3->getSource()) {
                        case 'R':
                            it3->setValue(pixel.r);
                            break; 
                        case 'G':
                            it3->setValue(pixel.r);
                            break; 
                        case 'B':
                            it3->setValue(pixel.r);
                            break;
                        case 'A':
                            it3->setValue(pixel.r);
                            break;
                            
                        default:
                            break;
                    }
                    
                } catch (InvalidValueException &e) {
                    console() << e.getMessage() << "Could not update Channel" << endl;
                }

                //draw each channel 
                gl::color(0.0f, 0.0f, 0.0f);
                gl::drawSolidCircle(pos.xy(), 5.0f);
                gl::color(1.0f, 1.0f, 1.0f);
                         
            }
            
        }
    }

    
}

void Cluster::getChannelData(uint8_t *data){
    
    vector<Group>::iterator it;
    int channel = 0;

    for(it = groups.begin(); it < groups.end(); it++){
        
        vector<Light> *lights = it->getLights();
        vector<Light>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            vector<LightChannel> *channels = it2->getChannels();
            vector<LightChannel>::iterator it3;
            //dont forget the channels
            int i = 0;
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
               
                // calculate real channel 
                // first with channels in the light = i, + the offset of the light + the offset oh the group
                channel = i + it2->getAdressOffset() + it->getAdressOffset() + getStartAdress();
                i++;

                data[channel] = it3->getValue();
                
            }
            
        }
    }
    
    
}

