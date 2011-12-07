//
//  Artnet.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 30.11.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Artnet.h"
#include "common.h"
#include "CinderArtnet.h"
#include "cinder/app/AppBasic.h"
using namespace ci::app;

CinderArtnet::CinderArtnet(){

}

CinderArtnet::CinderArtnet(string  name, string  longName, string ip_adress)   
{       
    //Address to send from
    node = artnet_new(ip_adress.c_str(), 0);
    // Set name of the node
    artnet_set_long_name(node, longName.c_str());
    artnet_set_short_name(node, name.c_str());

}

void CinderArtnet::setNodeTypeAsServer(){
    
    artnet_set_node_type(node, ARTNET_SRV);

    
}
void CinderArtnet::setSubnetAdress(int subnet){
    // set subnet address

    artnet_set_subnet_addr(node, subnet);

}
void CinderArtnet::enableDMXPortAsInputAndSetAdress(int port, int adress){
    // enable  port
    artnet_set_port_type(node, port, ARTNET_ENABLE_INPUT, ARTNET_PORT_DMX);
    // bind port  to universe (port_addr)
    artnet_set_port_addr(node, port, ARTNET_INPUT_PORT, adress);


}
void CinderArtnet::printConfig(){
    // print the config of the node
    artnet_dump_config(node);
}
void CinderArtnet::startNode(){
    // try to start the node
    if (artnet_start(node) != 0) {
        console() << "Error: " << artnet_strerror << endl;
        
    }       

}
void CinderArtnet::sendDataAtPort(const uint8_t *data, int port){
    
    // send data on port 0
    artnet_send_dmx(node, port,  ARTNET_DMX_LENGTH, data);
    
        

}