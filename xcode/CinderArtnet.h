//
//  Artnet.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 30.11.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "artnet.h"
#include <string>
using namespace std;

class CinderArtnet{
  
private: 
    artnet_node node;
    
public: 
    
    CinderArtnet( const char  name, const char longName, const char ip_adress);    
    void setNodeTypeAsServer();
    void setSubnetAdress(int subnet);
    void enableDMXPortAsInputAndSetAdress(int port, int adress);
    void printConfig();
    void startNode();
    void sendDataAtPort(const uint8_t  *data, int port);
    
  
};