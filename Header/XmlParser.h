//
//  XmlParser.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "cinder/Xml.h"
#include "Cluster.h"
using namespace ci;
using namespace std;

class XmlParser{
  
private: 
    const XmlTree xml;
    
public:
    
    XmlParser();
    void loadTemplateClusterToUniverse(vector<ClusterRef> &destination, int universe  ,const string &source);
    void saveCurrent(vector<ClusterRef> &source);
    void loadScene(vector<ClusterRef> &destination);
    
};