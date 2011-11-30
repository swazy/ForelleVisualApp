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


void Group::setGroupAdress(int a){
    
    
    groupAdress = a;
    
    
}
int Group::getGroupAdress(){
    
    return groupAdress;
    
}
void Group::addLight(Light *l){
    
    
    lights.push_back(*l);
    
}
Light* Group::getLight(int pos){
    
    if(pos <0 || pos >= lights.size()){
       console() << "Cant get light. Pos out of Bounds" << endl;
       return NULL;
    }
       else
           return &lights.at(pos);
    
}