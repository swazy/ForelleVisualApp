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
    
    int adressOffset;
    
    public:
    Group();
    void setAdressOffset(int a);
    int getAdressOffset();
    void addLightWithChannels(const char * channels);
    Light* getLight(int pos);
    int getUsedChannels();
    vector<Light>* getLights();
 
    
    
    
    
};