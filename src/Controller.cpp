//
//  Controller.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "Controller.h"

Controller::Controller(){
    
    setUniverse(0);

}
Controller::Controller(int u){
    
    setUniverse(u);
    
}

Group* Controller::getGroupAt(int pos){
    
    return &groups[pos];
}
void   Controller::addGroup(Group *g){
    
    groups.push_back(*g);
    
}
int Controller::getUniverse(){
    
    return universe;
    
}
void Controller::setUniverse(int u){
    
    universe = u;
}

