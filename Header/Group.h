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
    
    int startAdress;
    
    public:
    Group();
    void setStartAdress(int a);
    int getStartAdress();
    void addLight(int lightSize);
    Light* getLight(int pos);
    
    
    
    
};