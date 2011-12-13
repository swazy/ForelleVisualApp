//
//  SyphonClient.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 07.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifndef  SClient_H
#define  SClient_H

#include "cinderSyphon.h"
#include "cinder/gl/Fbo.h"
using namespace ci;
using namespace ci::app;
using namespace std;
class SClient{
  
private: 

    // retrun that surface to get pixeldata
    Surface mSurface; 
   
    //our syphon client
    syphonClient mClientSyphon;
    
    // our FBO to render into
    gl::Fbo	mFbo;
    
    int fboWidth, fboHeight;
    
    
public:
    SClient();
    void setup(Vec2i size);
    void update();
    gl::Texture* getTexture();
    Surface* getSurface();

    
};
#endif    

