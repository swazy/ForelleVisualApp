//
//  Controller.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 04.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef  Controller_H
#define  Controller_H
#include <iostream>
#include "vector.h"
#include "Cluster.h"

class Controller{
    
public:
    Controller();
    void printClusters(vector<Cluster> &clusters);
    void updateAndDrawClusters(vector<Cluster> &clusters, Surface &surface);
    void getData(vector<Cluster> &clusters, uint8_t *data);
    void changeSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster);
    void deleteSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster);
};
#endif