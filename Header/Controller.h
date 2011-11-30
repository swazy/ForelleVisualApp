//
//  Controller.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>
#include "Group.h"
class Controller{
  
    
private:
    
    int universe;
    int controllerAdress;
    std::vector<Group> groups;
    
    
public:
    Controller();
    Controller(int u);
    Group* getGroupAt(int pos);
    void   addGroup(Group *g);
    int getUniverse();
    void setUniverse(int u);
    
    
    
}; 