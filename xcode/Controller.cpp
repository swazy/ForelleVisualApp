//
//  Controller.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 04.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Controller.h"

Controller::Controller(){
    
}

void Controller::printClusters(vector<Cluster> &clusters)
{    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->printCluster();
        
    }
    
}
void Controller::updateAndDrawClusters(vector<Cluster> &clusters, Surface &surface){
    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->updateAndDrawCluster(surface);        
    }
    
    
}
void Controller::getData(vector<Cluster> &clusters, uint8_t *data){
    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->getChannelData(data);        
    }
    
    
}
void Controller::changeSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster){
    
    if(!clusters.empty()){
        
        if(selectedCluster == clusters.begin())
            selectedCluster =  clusters.end()-1  ;
        else
            --selectedCluster;
    }
}
void Controller::deleteSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster){
    
    if(!clusters.empty()){
        
        
        selectedCluster = clusters.erase(selectedCluster);
    }
}