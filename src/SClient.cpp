//
//  SyphonClient.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 07.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "SClient.h"

SClient::SClient(){};

void SClient::setup(Vec2i size){
   	
    mFbo = gl::Fbo( size.x, size.y);
    mClientSyphon.setup();
    
	// in order for this to work, you must run simple server from the testapps directory
	// any other syphon item you create would work as well, just change the name
    mClientSyphon.setApplicationName("Quartz Composer");
    mClientSyphon.setServerName("");
	
	mClientSyphon.bind();
   
}
void SClient::update(){
    
    gl::SaveFramebufferBinding bindingSaver;
	mFbo.bindFramebuffer();
	gl::clear( Color( 0.5, 0.5f, 0.5f ) );
	gl::pushMatrices();
	gl::setMatricesWindow(mFbo.getWidth(), mFbo.getHeight());
    mClientSyphon.draw(Vec2f(0,0),Vec2f(mFbo.getWidth(), mFbo.getHeight())); //draw our client image    
    mFbo.unbindFramebuffer();
    gl::popMatrices();
    gl::setViewport( getWindowBounds() );
    mSurface = Surface(mFbo.getTexture(0));
//gl::draw( mFbo.getTexture(0), Rectf(0,0,240,240));


}
gl::Texture* SClient::getTexture(){
    return &mFbo.getTexture(0);
}
Surface* SClient::getSurface(){
    return &mSurface;
}
