//
//  Group.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>
#include "Light.h"

using namespace std;

class Group{
    
    private:
    
    vector<Light> lights;
    string name;
    int adressOffset;
    
    public:
    Group(const string &name);
    void setAdressOffset(int a);
    int getAdressOffset();
    void addLight(Light &light);
    Light* getLight(int pos)throw(InvalidValueException);
    int getUsedChannels();
    vector<Light>* getLights();
    string* getName();
 
    
    
    
    
};