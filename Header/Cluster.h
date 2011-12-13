//
//  Cluster.h
//  ForelleVisualApp
//
//  Created by Patrick Fuerst on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifndef Cluster_H
#define Cluster_H
#include <vector>
#include "Group.h"

typedef boost::shared_ptr<class Cluster> ClusterRef;

class Cluster{
  
    
private:
    
    int universe;
    int startAdress;;
    std::vector<GroupRef> groups;
    string name;
    Vec3i pos;
    Boolean alreadyAdded;
    string uniqueId;
    
public:
    Cluster();
    Cluster(const string &name, int u);

    vector<GroupRef>* getGroups();
    void addGroup( Group *group);

    void setPos(Vec3i pos);
    Vec3i* getPos();
    
    void setId(string i);
    string* getId();
   
    string* getName();
    void setName(string &name);
    
    void moveUp(int y);
    void moveDown(int y);
    void moveLeft(int x);
    void moveRight(int x);
    bool getAdded();
    void added();
    void notAdded();
    int* getUniverse();
    void setUniverse(int u)throw(InvalidValueException);
    
    void setStartAdress(int a);
    int*  getStartAdress();
    
    int getUsedChannels();
    void printUsedChannels();

   
    void printCluster();
    void getChannelData(uint8_t *data);
    void updateAndDrawCluster(Surface &surface, Vec2i imagePosOffset, int scale);

    
}; 
#endif