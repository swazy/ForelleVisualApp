//
//  Group.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifndef Group_H
#define Group_H

#include <vector>
#include "Light.h"

using namespace std;
typedef boost::shared_ptr<class Group> GroupRef;

class Group{
    
    private:
    
    vector<LightRef> lights;
    string name;
    int adressOffset;
    Vec3i posOffset;
    
    public:
    Group(const string &name);
    void setAdressOffset(int a);
    void setPosOffset(Vec3i posOffset);
    Vec3i* getPosOffset();
    int* getAdressOffset();
    void addLight(Light *light);
    Light* getLight(int pos)throw(InvalidValueException);
    int getUsedChannels();
    vector<LightRef>* getLights();
    string* getName();
  
    
    
    
    
};
#endif