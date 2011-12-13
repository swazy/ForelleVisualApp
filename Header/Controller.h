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
    void printClusters(vector<ClusterRef> &clusters);
    void updateAndDrawClusters(vector<ClusterRef> &clusters, Surface &surface,  Vec2i imagePosOffset, int scale);
    void getData(vector<ClusterRef> &clusters, uint8_t *data1, uint8_t *data2 );
    void changeSelectedCluster(vector<ClusterRef>&clusters, vector<ClusterRef>::iterator &selectedCluster);
    void deleteSelectedCluster(vector<ClusterRef> &clusters, vector<ClusterRef>::iterator &selectedCluster);
    void barRefresh(vector<ClusterRef> &clusters);

};
#endif