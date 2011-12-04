//
//  Cluster.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>
#include "Group.h"
class Cluster{
  
    
private:
    
    int universe;
    int startAdress;;
    std::vector<Group> groups;
    string name;
    Vec3i pos;
    
    
public:
    Cluster();
    Cluster(const string &name, int u);
    
    vector<Group>* getGroups();
    void addGroup( Group &group);

    void setPos(Vec3i pos);
    Vec3i* getPos();
   
    string* getName();
    void setName(string &name);
    
    void moveUp(int y);
    void moveDown(int y);
    void moveLeft(int x);
    void moveRight(int x);

    int* getUniverse();
    void setUniverse(int u)throw(InvalidValueException);
    
    void setStartAdress(int a);
    int*  getStartAdress();
    
    int getUsedChannels();
    void printUsedChannels();

   
    void printCluster();
    void getChannelData(uint8_t *data);
    void updateAndDrawCluster(Surface &surface);

    
}; 