//
//  XmlParser.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 01.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "XmlParser.h"



XmlParser::XmlParser(){
    
}



void XmlParser::loadTemplateClusterWithUniverse(vector<Cluster> &destination, int universe , const string &source){
    
    
    const XmlTree xml( loadFile( source ) );
	
    Cluster cluster = Cluster(universe);
    
    
    for( XmlTree::ConstIter itemIter = xml.begin("/cluster/group"); itemIter != xml.end(); ++itemIter ) {
      
        console() << "Tag: " << child->getTag() << "  Value: " << child->getValue() << endl;

        XmlTree  = doc.getChild( "library/album" );
        for( XmlTree::Iter child = firstAlbum.begin(); child != firstAlbum.end(); ++child )
            console() << "Tag: " << child->getTag() << "  Value: " << child->getValue() << endl;
        
        
        
        
//        
//        string titleLine( itemIter->getChild( "title" ).getValue() );
//		size_t firstComma = titleLine.find( ',' );
//		float magnitude = fromString<float>( titleLine.substr( titleLine.find( ' ' ) + 1, firstComma - 2 ) );
//		string title = titleLine.substr( firstComma + 2 );
//        
//		istringstream locationString( itemIter->getChild( "georss:point" ).getValue() );
//		Vec2f locationVector;
//		locationString >> locationVector.x >> locationVector.y;
//		
//		mEarth.addQuake( locationVector.x, locationVector.y, magnitude, title );		
	}

       }
