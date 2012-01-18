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
void Controller::updateAndDrawClusters(vector<ClusterRef> &clusters, Surface &surface,  Vec2i imagePosOffset, int scale){
    
    vector<ClusterRef>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        (*it)->updateAndDrawCluster(surface,imagePosOffset, scale );        
    }
    
    
}
void Controller::barRefresh(vector<ClusterRef> &clusters){
    
    vector<ClusterRef>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        (*it)->notAdded();   
    }
    
    
}
void Controller::getData(vector<ClusterRef> &clusters, uint8_t *data1, uint8_t *data2, uint8_t *data3,uint8_t *data4){
    
    vector<ClusterRef>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        // cinder::app::console() << "universe  " << *(*it)->getUniverse() << endl;

        if (*(*it)->getUniverse() == 0) {
            (*it)->getChannelData(data1);  
            //  cinder::app::console() << "asdasdasd" << endl;
            
        }else  if (*(*it)->getUniverse() == 1) {
            (*it)->getChannelData(data2);        
            
        }else  if (*(*it)->getUniverse() == 2) {
            (*it)->getChannelData(data3);        
            
        }else  if (*(*it)->getUniverse() == 3) {
            (*it)->getChannelData(data4);        
            
        }

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