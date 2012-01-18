//
//  XmlParser.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "XmlParser.h"
#include "rapidxml/rapidxml.hpp"
#include "cinder/xml.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"

using namespace ci::app;


XmlParser::XmlParser(){
    
}



void XmlParser::loadTemplateClusterToUniverse(vector<ClusterRef> &destination, int universe ){
    
    string source =  getOpenFilePath( getHomeDirectory() );

   
    //catch mal-formed Xml Files
    try {
     
        const XmlTree xml( loadFile( source ) );

        Cluster *cluster = new Cluster(xml.getChild("cluster").getAttributeValue<string>("name"), universe);
        cluster->setPos(  Vec3i(10, 10,0));

        // Iterate through Groups
        for( XmlTree::ConstIter groupIter = xml.begin("/cluster/group"); groupIter != xml.end(); ++groupIter ) {
          
            Group *group = new Group(groupIter->getAttributeValue<string>("name"));
            int gx =groupIter->getAttributeValue<int>("xo");
            int gy =groupIter->getAttributeValue<int>("yo");
            int gz =groupIter->getAttributeValue<int>("zo");
            group->setPosOffset(Vec3i(gx,gy,gz));
            // Iterate through Lights
            for( XmlTree::ConstIter lightIter = groupIter->begin(); lightIter != groupIter->end(); ++lightIter ) {
                
                Light *light = new Light(lightIter->getAttributeValue<string>("name"));
                int lx =lightIter ->getAttributeValue<int>("xo");
                int ly =lightIter ->getAttributeValue<int>("yo");
                int lz =lightIter ->getAttributeValue<int>("zo");

                light->setPosOffset(Vec3i(lx,ly,lz));

                // Iterate through Channels
                for( XmlTree::ConstIter channelIter = lightIter->begin(); channelIter != lightIter->end(); ++channelIter ) {
                    LightChannel *channel;
                    try{
                        channel = new LightChannel(channelIter->getAttributeValue<string>("name"), channelIter->getAttributeValue<char>("source") );
                        int cx =channelIter->getAttributeValue<int>("xo");
                        int cy =channelIter->getAttributeValue<int>("yo");
                        int cz =channelIter->getAttributeValue<int>("zo");
                        
                        channel->setPosOffset(Vec3i(cx,cy,cz));
                        
                    }catch(InvalidSourceException& e){
                        throw rapidxml::parse_error( e.getMessage().c_str(), 0 );
                    }
                    light->addChannel(channel);

                }
                
                group->addLight(light);
            }
            
            cluster->addGroup(group);
        }
        
        if(!destination.empty()){
       
            int usedChannels = *(*destination.back()).getStartAdress() + (*destination.back()).getUsedChannels();
            cluster->setStartAdress(usedChannels);
       
        }
        destination.push_back(ClusterRef(cluster));
        console() << "Cluster added" << endl;

    }catch  (rapidxml::parse_error &e)
    {
        console()<< e.what() << "  RapidXML exception!"<< endl;
    }catch(cinder::XmlTree::ExcChildNotFound &e){
        console() << e.what() << "Child not found" <<endl;
    }catch(cinder::XmlTree::ExcAttrNotFound &e){
        console() << e.what() << "Attribute not found" <<endl;
    }catch(InvalidValueException& e){
        console() << e.getMessage()  <<endl;
    }catch(...){
        console() << "Unable to Load" <<endl;
    }
    

}


void XmlParser::saveAsScene(vector<ClusterRef> &source, const string path ){

    XmlTree sceneNode("scene","");
    
    
    // Iterate through Clusters
    for( vector<ClusterRef>::iterator clusterIter = source.begin(); clusterIter != source.end(); ++clusterIter ) {
        

        XmlTree clusterNode( "cluster", "" );
        clusterNode.setAttribute("name", *(*clusterIter)->getName());
        clusterNode.setAttribute("universe", *(*clusterIter)->getUniverse());
        clusterNode.setAttribute("address", *(*clusterIter)->getStartAdress());
        clusterNode.setAttribute("x", (*clusterIter)->getPos()->x);
        clusterNode.setAttribute("y",(*clusterIter)->getPos()->y);
        clusterNode.setAttribute("z", (*clusterIter)->getPos()->z);
       
        
        vector<GroupRef> *groups = (*clusterIter)->getGroups();
        // Iterate through Groups
        for(  vector<GroupRef>::iterator groupIter = groups->begin(); groupIter != groups->end(); ++groupIter ) {
          
            XmlTree groupNode( "group", "" );
            groupNode.setAttribute("name", *(*groupIter)->getName());
            groupNode.setAttribute("address", *(*groupIter)->getAdressOffset());
            groupNode.setAttribute("xo", (*groupIter)->getPosOffset()->x);
            groupNode.setAttribute("yo",(*groupIter)->getPosOffset()->y);
            groupNode.setAttribute("zo", (*groupIter)->getPosOffset()->z);
            
            vector<LightRef> *lights = (*groupIter)->getLights();
            // Iterate through Lights
            for( vector<LightRef>::iterator lightIter = lights->begin(); lightIter != lights->end(); ++lightIter ) {
                    
                XmlTree lightNode( "light", "" );
                lightNode.setAttribute("name", *(*lightIter)->getName());
                lightNode.setAttribute("address", *(*lightIter)->getAdressOffset());
                lightNode.setAttribute("xo", (*lightIter)->getPosOffset()->x);
                lightNode.setAttribute("yo",(*lightIter)->getPosOffset()->y);
                lightNode.setAttribute("zo", (*lightIter)->getPosOffset()->z);
                
                vector<LightChannelRef> *channels = (*lightIter)->getChannels();
                // Iterate through Channels
                for( vector<LightChannelRef>::iterator channelIter = channels->begin(); channelIter != channels->end(); ++channelIter ) {

                    XmlTree channelNode( "channel", "" );
                    channelNode.setAttribute("name", *(*channelIter)->getName());
                    channelNode.setAttribute("source", *(*channelIter)->getSource());
                    channelNode.setAttribute("xo", (*channelIter)->getPosOffset()->x);
                    channelNode.setAttribute("yo",(*channelIter)->getPosOffset()->y);
                    channelNode.setAttribute("zo", (*channelIter)->getPosOffset()->z);
                    lightNode.push_back(channelNode);
                }
                groupNode.push_back(lightNode);
            } 
            clusterNode.push_back(groupNode);
        }
        sceneNode.push_back(clusterNode);
    }

    try {
        
      
        
        if( ! path.empty() ) {
            sceneNode.write( writeFile( path+".xml" ) );
        }
    }
    catch( ... ) {
        console() << "unable to save file" << std::endl;
    }		
    
}
void XmlParser::saveAsScene(vector<ClusterRef> &source){

    try {
        
        string path = getSaveFilePath( getHomeDirectory() );
        
        if( ! path.empty() ) {
            saveAsScene(source, path);
        }
    }
    catch( ... ) {
        console() << "unable to get Path" << std::endl;
    }		

}

void XmlParser::saveAsCluster(vector<ClusterRef> &source ){
    
    XmlTree clusterNode( "cluster", "" );

    // Iterate through Clusters
    for( vector<ClusterRef>::iterator clusterIter = source.begin(); clusterIter != source.end(); ++clusterIter ) {
        
        
        clusterNode.setAttribute("name", *(*clusterIter)->getName());
        clusterNode.setAttribute("universe", *(*clusterIter)->getUniverse());
        clusterNode.setAttribute("address", *(*clusterIter)->getStartAdress());
        clusterNode.setAttribute("x", (*clusterIter)->getPos()->x);
        clusterNode.setAttribute("y",(*clusterIter)->getPos()->y);
        clusterNode.setAttribute("z", (*clusterIter)->getPos()->z);
        
        
        vector<GroupRef> *groups = (*clusterIter)->getGroups();
        // Iterate through Groups
        for(  vector<GroupRef>::iterator groupIter = groups->begin(); groupIter != groups->end(); ++groupIter ) {
            
            XmlTree groupNode( "group", "" );
            groupNode.setAttribute("name", *(*groupIter)->getName());
            groupNode.setAttribute("address", *(*groupIter)->getAdressOffset());
            groupNode.setAttribute("xo", (*groupIter)->getPosOffset()->x);
            groupNode.setAttribute("yo",(*groupIter)->getPosOffset()->y);
            groupNode.setAttribute("zo", (*groupIter)->getPosOffset()->z);
            
            vector<LightRef> *lights = (*groupIter)->getLights();
            // Iterate through Lights
            for( vector<LightRef>::iterator lightIter = lights->begin(); lightIter != lights->end(); ++lightIter ) {
                
                XmlTree lightNode( "light", "" );
                lightNode.setAttribute("name", *(*lightIter)->getName());
                lightNode.setAttribute("address", *(*lightIter)->getAdressOffset());
                lightNode.setAttribute("xo", (*lightIter)->getPosOffset()->x);
                lightNode.setAttribute("yo",(*lightIter)->getPosOffset()->y);
                lightNode.setAttribute("zo", (*lightIter)->getPosOffset()->z);
                
                vector<LightChannelRef> *channels = (*lightIter)->getChannels();
                // Iterate through Channels
                for( vector<LightChannelRef>::iterator channelIter = channels->begin(); channelIter != channels->end(); ++channelIter ) {
                    
                    XmlTree channelNode( "channel", "" );
                    channelNode.setAttribute("name", *(*channelIter)->getName());
                    channelNode.setAttribute("source", *(*channelIter)->getSource());
                    channelNode.setAttribute("xo", (*channelIter)->getPosOffset()->x);
                    channelNode.setAttribute("yo",(*channelIter)->getPosOffset()->y);
                    channelNode.setAttribute("zo", (*channelIter)->getPosOffset()->z);
                    lightNode.push_back(channelNode);
                }
                groupNode.push_back(lightNode);
            } 
            clusterNode.push_back(groupNode);
        }
    }
    
    try {
        
        string path = getSaveFilePath( getHomeDirectory() );
        
        if( ! path.empty() ) {
            clusterNode.write( writeFile( path+".xml" ) );
        }
    }
    catch( ... ) {
        console() << "unable to save file" << std::endl;
    }		
    
}
void XmlParser::loadScene(vector<ClusterRef> &destination){
    
    try {
        
        string path = getOpenFilePath( getHomeDirectory() );
        
        if( ! path.empty() ) {
            loadScene(destination, path);
        }
    }
    catch( ... ) {
        console() << "unable to get Path" << std::endl;
    }		

}

void XmlParser::loadScene(vector<ClusterRef> &destination, const string source){

        
    //catch mal-formed Xml Files
    try {
        const XmlTree xml( loadFile( source ) );
        
        // Iterate through Clusters
        for( XmlTree::ConstIter clusterIter = xml.begin("scene/cluster"); clusterIter != xml.end(); ++clusterIter ) {

        
            Cluster *cluster = new Cluster(clusterIter->getAttributeValue<string>("name"), clusterIter->getAttributeValue<int>("universe"));
            int x = clusterIter->getAttributeValue<int>("x");
            int y = clusterIter->getAttributeValue<int>("y");
            int z = clusterIter->getAttributeValue<int>("z");
            int adress = clusterIter->getAttributeValue<int>("address");
            console() << adress << endl;
            cluster->setPos(  Vec3i(x,y,z));
            cluster->setStartAdress(adress);
            
            // Iterate through Groups
            for( XmlTree::ConstIter groupIter = clusterIter->begin(); groupIter != clusterIter->end(); ++groupIter ) {
            
                Group *group = new Group(groupIter->getAttributeValue<string>("name"));
                int gx =groupIter->getAttributeValue<int>("xo");
                int gy =groupIter->getAttributeValue<int>("yo");
                int gz =groupIter->getAttributeValue<int>("zo");
                group->setPosOffset(Vec3i(gx,gy,gz));
                // Iterate through Lights
                for( XmlTree::ConstIter lightIter = groupIter->begin(); lightIter != groupIter->end(); ++lightIter ) {
                
                    Light *light = new Light(lightIter->getAttributeValue<string>("name"));
                    int lx =lightIter ->getAttributeValue<int>("xo");
                    int ly =lightIter ->getAttributeValue<int>("yo");
                    int lz =lightIter ->getAttributeValue<int>("zo");
                
                    light->setPosOffset(Vec3i(lx,ly,lz));
                
                    // Iterate through Channels
                    for( XmlTree::ConstIter channelIter = lightIter->begin(); channelIter != lightIter->end(); ++channelIter ) {
                        LightChannel *channel;
                        try{
                            channel = new LightChannel(channelIter->getAttributeValue<string>("name"), channelIter->getAttributeValue<char>("source") );
                            int cx =channelIter->getAttributeValue<int>("xo");
                            int cy =channelIter->getAttributeValue<int>("yo");
                            int cz =channelIter->getAttributeValue<int>("zo");
                            
                            channel->setPosOffset(Vec3i(cx,cy,cz));
                            
                        }catch(InvalidSourceException& e){
                            throw rapidxml::parse_error( e.getMessage().c_str(), 0 );
                        }
                        light->addChannel(channel);
                    
                    }
                
                    group->addLight(light);
                }
            
                cluster->addGroup(group);
            }
        
//            if(!destination.empty()){
//            
//                int usedChannels = *(*destination.back()).getStartAdress() + (*destination.back()).getUsedChannels();
//                cluster->setStartAdress(usedChannels);
//            
//            }
            destination.push_back(ClusterRef(cluster));
            
            // delete clusteR?
        }
        console() << "Cluster added" << endl;
        

    }catch  (rapidxml::parse_error &e)
    {
        console()<< e.what() << "  RapidXML exception!"<< endl;
    }catch(cinder::XmlTree::ExcChildNotFound &e){
        console() << e.what() << "Child not found" <<endl;
    }catch(cinder::XmlTree::ExcAttrNotFound &e){
        console() << e.what() << "Attribute not found" <<endl;
    }catch(...){
        console() << "Unable to Load Scene" <<endl;
    }

    
}