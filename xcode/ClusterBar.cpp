//
//  MenueBar.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 07.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ClusterBar.h"
#include <sstream>
using namespace ci;
using namespace ci::app;
using namespace std;

ClusterBar::ClusterBar(){}
ClusterBar::ClusterBar( const string &name, Vec2i pos){

    mParams = params::InterfaceGl( name, pos );
}
void ClusterBar::draw(){
    mParams.draw();
}

void ClusterBar::removeVar(string* i){
    mParams.removeVar(*i);
}
void ClusterBar::removeAllVar(){
    mParams.removeAllVar();
}
void  ClusterBar::loadParametersFromCluster( ClusterRef cluster){
    
    stringstream cc;
    
    cc << getElapsedSeconds();
    //console() << cc.str() << endl;
    mParams.addParam( "" , cluster->getName(), "label=`Name` group="+*cluster->getName()+cc.str() );
    mParams.addParam( "" , &cluster->getPos()->x, "label=`X` group="+*cluster->getName()+cc.str() );	
    mParams.addParam( "" , &cluster->getPos()->y, "label=`Y` group="+*cluster->getName()+cc.str());
    mParams.addParam( "" , cluster->getStartAdress(), "label=`StartAdress` group="+*cluster->getName()+cc.str());    
    mParams.addParam( "" , cluster->getUniverse(), "label=`Universe` min=0 max=4 step=1 group="+*cluster->getName()+cc.str() ); 
    mParams.setOptions( *cluster->getName()+cc.str() , "label=`" +*cluster->getName() +"` "+ "opened=false" );
    cluster->added();
    cluster->setId( (*cluster->getName())+cc.str());
    
    vector<GroupRef> *groups = cluster->getGroups();
    vector<GroupRef>::iterator it;
    stringstream gg;
    
    for(it = groups->begin(); it < groups->end(); it++){
        
        gg.str(std::string());
        gg << getElapsedSeconds();
        
        string groupName = *(*it)->getName();
        mParams.addParam( "" , &(*it)->getPosOffset()->x, "label=`x-offset` group="+groupName+gg.str() );    
        mParams.addParam( "" , &(*it)->getPosOffset()->y, "label=`y-offset` group="+groupName+gg.str() );    
        mParams.addParam( "" , (*it)->getAdressOffset(), "label=`Adressoffset`  group="+groupName+gg.str()  );    
        mParams.setOptions( groupName+gg.str() , " group="+*cluster->getName()+cc.str()+" label=`" +*(*it)->getName() +"` "+ " opened=false");
        
        
        vector<LightRef> *lights = (*it)->getLights();
        vector<LightRef>::iterator it2;
        stringstream ll;
        
        for(it2 = lights->begin(); it2 < lights->end(); it2++){
            
            ll.str(std::string());
            ll << getElapsedSeconds();
            
            string lightName = *(*it2)->getName();
            
            mParams.addParam( "" , &(*it2)->getPosOffset()->x, "label=`x-Offset` group="+lightName+ll.str() );    
            mParams.addParam( "" , &(*it2)->getPosOffset()->y, "label=`y-Offset` group="+lightName+ll.str() );    
            mParams.addParam( "" , (*it2)->getAdressOffset(),  "label=`Adressoffset` group="+lightName+ll.str() );    
            mParams.setOptions( lightName+ll.str() , " group="+groupName+gg.str()+" label=`" +lightName +"` "+ " opened=false");
            
            vector<LightChannelRef> *channels = (*it2)->getChannels();
            vector<LightChannelRef>::iterator it3;
            stringstream lc;
            
            for(it3 = channels->begin(); it3 < channels->end(); it3++){
                
                lc.str(std::string());
                lc << getElapsedSeconds();
                
                string channelName = *(*it3)->getName();
                stringstream source;
                source << (*it3)->getSource();
                mParams.addParam( "" , &(*it3)->getPosOffset()->x, "label=`x-Offset` group="+channelName+lc.str() );    
                mParams.addParam( "" , &(*it3)->getPosOffset()->y, "label=`y-Offset` group="+channelName+lc.str() );    
                mParams.addParam( "" , (*it3)->getSourceAsString(),  "label=`Source` readonly=true group="+channelName+lc.str());    
                mParams.setOptions( channelName+lc.str() , " group="+lightName+ll.str()+" label=`" +channelName+"` "+ " opened=false");
            }
            
        }
    }

    
}

void ClusterBar::loadParameters(vector<ClusterRef> &clusters){
    
    vector<ClusterRef>::iterator it;
    for (it = clusters.begin(); it < clusters.end(); it++) {
//        if((*it)->getAdded())
//            console() <<"true" << endl;
//        else
//            console() <<"false" << endl;
//        
        if((*it)->getAdded())
            continue;
        
        loadParametersFromCluster(*it );
        
        
    }
}
    
    
    
    
    