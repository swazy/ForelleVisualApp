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
    startAdress = 0;
    setPos(Vec3i(0,0,0));
    this->name ="";
    alreadyAdded = false;

}
Cluster::Cluster(const string &name, int u){
    
    setUniverse(u);
    this->name = name;
    startAdress = 0;
    setPos(Vec3i(0,0,0));
    alreadyAdded = false;

}

vector<GroupRef>* Cluster::getGroups(){
    return &groups;
}
bool Cluster::getAdded(){
    return alreadyAdded;
}
void Cluster::notAdded(){
    alreadyAdded = false;
}

void Cluster::added(){
    alreadyAdded = true;
}
void Cluster::setId(string i){
    
    uniqueId = i;
}
string* Cluster::getId(){
    return &uniqueId;
}

void Cluster::addGroup( Group *group){
    
   
    int usedChannels = getUsedChannels();
    group->setAdressOffset(usedChannels);
    groups.push_back(GroupRef(group));

    
}    

string* Cluster::getName(){
    return &name;
}
void Cluster::setName(string &name){
    this->name = name;
}

void Cluster::setPos(Vec3i pos){
    this->pos = pos;
}  
Vec3i* Cluster::getPos(){
    return &pos;
}
void Cluster::moveUp(int y){
    if(pos.y > 0)
        pos.y -= y;
    
}
void Cluster::moveDown(int y){
    if(pos.y < getWindowHeight())
        pos.y += y;

}
void Cluster::moveLeft(int x){
    if(pos.x > 0)
        pos.x -= x;

}
void Cluster::moveRight(int x){
    if(pos.x < getWindowWidth())
        pos.x += x;

}

int* Cluster::getUniverse(){
    
    return &universe;
    
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
int* Cluster::getStartAdress(){
    
    return &startAdress;
    
}
int Cluster::getUsedChannels(){
    
    // calculate next free channels
    //last pushed light adressoffset + amount of channels
    
    if(groups.size() > 0)
        return *(*groups.back()).getAdressOffset() + (*groups.back()).getUsedChannels();
    else
        return 0;
 
}



void Cluster::printCluster(){
    
    vector<GroupRef>::iterator it;
    
    console() <<"ClusterName: " <<name <<endl;
    
    for(it = groups.begin(); it != groups.end(); it++){
        console() << "\tGroupName:  " << (*it)->getName() <<endl;
        vector<LightRef> *lights = (*it)->getLights();
        vector<LightRef>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            console() << "\t\tLight  " << (*it2)->getName() <<endl;
            vector<LightChannelRef> *channels = (*it2)->getChannels();
            vector<LightChannelRef>::iterator it3;
            
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
                console() << "\t\t\tChannelSource  " << (*it3)->getSource() << "  ChannelValue  " <<(*it3)->getValue() << endl; 
            }
            
        }
    }
} 
void Cluster::updateAndDrawCluster(Surface &surface, Vec2i imagePosOffset, int scale){
    
    gl::color(0.0f, 0.0f, 0.0f);
    gl::drawSolidCircle( (getPos()->xy())*scale+imagePosOffset, 4.0f);

 
    vector<GroupRef>::iterator it;    
    for(it = groups.begin(); it < groups.end(); it++){
        
        gl::color(1.0f, 1.0f, 1.0f);
        gl::drawSolidCircle( (getPos()->xy()+(*it)->getPosOffset()->xy())*scale+imagePosOffset, 4.0f);

        vector<LightRef> *lights = (*it)->getLights();
        vector<LightRef>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            vector<LightChannelRef> *channels = (*it2)->getChannels();
            vector<LightChannelRef>::iterator it3;
            
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
                
                //add all the offsets, to get the end pos of each channel
                Vec2i pos = getPos()->xy() + (*it)->getPosOffset()->xy() + (*it2)->getPosOffset()->xy() + (*it3)->getPosOffset()->xy();
                // get the color of the pixel at pos
                ColorA8u pixel = surface.getPixel(pos.xy());
                //   console() << "pixelvalue= " <<(int) surface.getPixel(Vec2i(10,10)).r << endl;
                try {
                                
                    switch (*(*it3)->getSource()) {
                        case 'R':
                            (*it3)->setValue(pixel.r);
                            gl::color(1.0f, 0.0f, 0.0f);
                            break; 
                        case 'G':
                            (*it3)->setValue(pixel.g);
                            gl::color(0.0f, 1.0f, 0.0f);

                            break; 
                        case 'B':
                            (*it3)->setValue(pixel.b);
                            gl::color(0.0f, 0.0f, 1.0f);
                            break;
                        case 'A':
                            (*it3)->setValue(0);
                            gl::color(1.0f, 1.0f, 1.0f);
                            break;
                            
                        default:
                            break;
                    }
                    
                } catch (InvalidValueException &e) {
                    console() << e.getMessage() << "Could not update Channel" << endl;
                }

                //draw each channel 
                // when resize syphone image draw circles on the rigth position
                gl::drawSolidCircle((pos.xy()*scale)+imagePosOffset, 4.0f);
                gl::color(1.0f, 1.0f, 1.0f);
                         
            }
            
        }
    }

    
}

void Cluster::getChannelData( uint8_t *data){
    
    vector<GroupRef>::iterator it;
    int channel = 0;

    for(it = groups.begin(); it < groups.end(); it++){
        
        vector<LightRef> *lights = (*it)->getLights();
        vector<LightRef>::iterator it2;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            vector<LightChannelRef> *channels = (*it2)->getChannels();
            vector<LightChannelRef>::iterator it3;
            //dont forget the channels
            int i = 0;
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
               
                // calculate real channel 
                // first with channels in the light = i, + the offset of the light + the offset oh the group
                channel = i + *(*it2)->getAdressOffset() + *(*it)->getAdressOffset() + *getStartAdress();
                i++;

                data[channel] = (*it3)->getValue();
                
            }
            
        }
    }
    
    
}

