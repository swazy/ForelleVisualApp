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

using namespace ci::app;


XmlParser::XmlParser(){
    
}



void XmlParser::loadTemplateClusterToUniverse(vector<Cluster> &destination, int universe , const string &source){
    
    	
   
    //catch mal-formed Xml Files
    try {
        const XmlTree xml( loadFile( source ) );

        Cluster cluster = Cluster(xml.getChild("cluster").getAttributeValue<string>("name"), universe);


        // Iterate through Groups
        for( XmlTree::ConstIter groupIter = xml.begin("/cluster/group"); groupIter != xml.end(); ++groupIter ) {
          
            Group group = Group(groupIter->getAttributeValue<string>("name"));

            // Iterate through Lights
            for( XmlTree::ConstIter lightIter = groupIter->begin(); lightIter != groupIter->end(); ++lightIter ) {
                
                Light light = Light(lightIter->getAttributeValue<string>("name"));
                
                // Iterate through Channels
                for( XmlTree::ConstIter channelIter = lightIter->begin(); channelIter != lightIter->end(); ++channelIter ) {
                    try{
                    LightChannel channel = LightChannel(channelIter->getAttributeValue<string>("name"), channelIter->getAttributeValue<char>("source") );
                    light.addChannel(channel);
                    }catch(InvalidSourceException& e){
                        console() << e.getMessage() << " Exception" << endl;
                    }
                }
                
                group.addLight(light);
            }
            
            cluster.addGroup(group);
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
    
    

}
