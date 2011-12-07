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

void Controller::printClusters(vector<ClusterRef> &clusters)
{    
    vector<ClusterRef>::iterator it;

    for (it = clusters.begin(); it < clusters.end(); it++) {

        (*it)->printCluster();
        
    }
    
}
void Controller::updateAndDrawClusters(vector<ClusterRef> &clusters, Surface &surface,  Vec2i imagePosOffset){
    
    vector<ClusterRef>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        (*it)->updateAndDrawCluster(surface,imagePosOffset );        
    }
    
    
}
void Controller::getData(vector<ClusterRef> &clusters, uint8_t *data){
    
    vector<ClusterRef>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        (*it)->getChannelData(data);        
    }
    
    
}
void Controller::changeSelectedCluster(vector<ClusterRef> &clusters, vector<ClusterRef>::iterator &selectedCluster){
    
    if(!clusters.empty()){
        
        if(selectedCluster == clusters.begin())
            selectedCluster =  clusters.end()-1  ;
        else
            --selectedCluster;
    }
}
void Controller::deleteSelectedCluster(vector<ClusterRef> &clusters, vector<ClusterRef>::iterator &selectedCluster){
    
    if(!clusters.empty()){
        
        
        selectedCluster = clusters.erase(selectedCluster);
        
        if (selectedCluster == clusters.end()) {
            selectedCluster = clusters.end()-1;
        }
    }
}