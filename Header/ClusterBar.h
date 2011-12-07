//
//  MenueBar.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 07.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef  ClusterBar_H
#define  ClusterBar_H

#include "cinder/params/Params.h"
#include "Cluster.h"


class ClusterBar{
  
    
    
private:
    // Parameter Window
    cinder::params::InterfaceGl		mParams;
    void loadParametersFromCluster( ClusterRef cluster);


public:
    ClusterBar();
    ClusterBar(const string &name, Vec2i pos);
    void draw();
    void loadParameters(vector<ClusterRef> &clusters);
    void removeVar(string* i);
    void removeAllVar();

    
    
};
#endif