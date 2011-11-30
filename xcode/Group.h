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
    
    int groupAdress;
    
    public:
    Group();
    void setGroupAdress(int a);
    int getGroupAdress();
    void addLight(Light *l);
    Light* getLight(int pos);
    
    
    
    
};