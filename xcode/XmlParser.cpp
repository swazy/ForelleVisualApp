//
//  XmlParser.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "XmlParser.h"
#include "rapidxml/rapidxml.hpp"
#include "cinder/xml.h"
#include "cinder/app/AppBasic.h"

using namespace ci::app;


XmlParser::XmlParser(){
    
}



void XmlParser::loadTemplateClusterToUniverse(vector<Cluster> &destination, int universe , const string &source){
    
    	
   
    //catch mal-formed Xml Files
    try {
        const XmlTree xml( loadFile( source ) );

        Cluster cluster = Cluster(xml.getChild("cluster").getAttributeValue<string>("name"), universe);
        cluster.setPos(  Vec3i( getWindowWidth()/2 -300, getWindowHeight()/2,0));

        // Iterate through Groups
        for( XmlTree::ConstIter groupIter = xml.begin("/cluster/group"); groupIter != xml.end(); ++groupIter ) {
          
            Group group = Group(groupIter->getAttributeValue<string>("name"));
            int gx =groupIter->getAttributeValue<int>("xo");
            int gy =groupIter->getAttributeValue<int>("yo");
            int gz =groupIter->getAttributeValue<int>("zo");
            group.setPosOffset(Vec3i(gx,gy,gz));
            // Iterate through Lights
            for( XmlTree::ConstIter lightIter = groupIter->begin(); lightIter != groupIter->end(); ++lightIter ) {
                
                Light light = Light(lightIter->getAttributeValue<string>("name"));
                int lx =lightIter ->getAttributeValue<int>("xo");
                int ly =lightIter ->getAttributeValue<int>("yo");
                int lz =lightIter ->getAttributeValue<int>("zo");

                light.setPosOffset(Vec3i(lx,ly,lz));

                // Iterate through Channels
                for( XmlTree::ConstIter channelIter = lightIter->begin(); channelIter != lightIter->end(); ++channelIter ) {
                    LightChannel channel;
                    try{
                        channel = LightChannel(channelIter->getAttributeValue<string>("name"), channelIter->getAttributeValue<char>("source") );
                        int cx =channelIter->getAttributeValue<int>("xo");
                        int cy =channelIter->getAttributeValue<int>("yo");
                        int cz =channelIter->getAttributeValue<int>("zo");
                        
                        channel.setPosOffset(Vec3i(cx,cy,cz));
                        
                    }catch(InvalidSourceException& e){
                        throw rapidxml::parse_error( e.getMessage().c_str(), 0 );
                    }
                    light.addChannel(channel);

                }
                
                group.addLight(light);
            }
            
            cluster.addGroup(group);
        }
        
        if(!destination.empty()){
       
            int usedChannels = *destination.back().getStartAdress() + destination.back().getUsedChannels();
            cluster.setStartAdress(usedChannels);
       
        }
        destination.push_back(cluster);

    }catch  (rapidxml::parse_error &e)
    {
        console()<< e.what() << "  RapidXML exception!"<< endl;
    }catch(cinder::XmlTree::ExcChildNotFound &e){
        console() << e.what() << "Child not found" <<endl;
    }catch(cinder::XmlTree::ExcAttrNotFound &e){
        console() << e.what() << "Attribute not found" <<endl;
    }
    
    console() << "Cluster added" << endl;

}
