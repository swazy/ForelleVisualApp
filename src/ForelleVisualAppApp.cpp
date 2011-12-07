#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "CinderArtnet.h"
#include "XmlParser.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder/ImageIo.h"
#include "cinder/params/Params.h"
#include "Controller.h"
#include "ClusterBar.h"
#include "SClient.h"

using namespace ci;
using namespace ci::app;
using namespace std;
namespace Const{
    const int MAX_DMX_CHANNELS = 512;
};

class ForelleVisualAppApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void prepareSettings( Settings *settings );
    void keyDown( KeyEvent event );

    // store our clusters 
    vector<ClusterRef> clusters;
   
    // array for the data of the 512 DMX channels
    uint8_t data[512];
    
    //Artnet node where we send our data
    CinderArtnet node;
    
    // xmlparser so read and write templates and scenes
    XmlParser parser;
  
    
    Surface surface;	
    
    Boolean readPixels;
    Boolean sendData;

    //selected cluster
    vector<ClusterRef>::iterator selectedCluster;
    
    // ClusterBar which shows all added Clusters
    ClusterBar clusterBar;
    
    //Controller to manage Clusters
    Controller controller;
    
    // Our syphoneClient
    SClient client;

    // position and size of the syphone image
    Vec2i pos;
    int scale;
   
    
};
void ForelleVisualAppApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1024, 768 );
	settings->setFrameRate( 100.0f );
	settings->setResizable( true );
	settings->setFullScreen( false );
}
void ForelleVisualAppApp::setup()
{
    // Setup the parameters
    clusterBar =  ClusterBar( "Cluster Window", Vec2i( 200, 400 ) );

    //othe way to initialsie with 0, and don´t have to update ??
    for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
        data[i]= 0;
        
    }

    //setup boolean variables
    readPixels = true;
    sendData  = true;
    
    //  parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");
 //   parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight2.xml");
 
   // surface = Surface( loadImage(loadResource(RES_IMAGE) ));

    // set our pointer to the last added cluster
    if(!clusters.empty())
        selectedCluster = clusters.end()-1;
         

    controller.printClusters(clusters);
    // loadParameters(clusters, mParams);

    
    //Setup Artnetnode
    node = CinderArtnet("Art-Net Test", "LongName", "10.0.2.2");
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
    node.enableDMXPortAsInputAndSetAdress(0,1);
   // node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.printConfig();
    node.startNode();
    
    // initalize start our Syphone Client
    client.setup(Vec2i(60,60));
    pos = Vec2i(0,0);
    scale = 1;


}

void ForelleVisualAppApp::mouseDown( MouseEvent event )
{
}
void ForelleVisualAppApp::keyDown( KeyEvent event )
{
    if( event.getCode() == app::KeyEvent::KEY_UP && !clusters.empty() ) {
		(*selectedCluster)->moveUp(1);
	}
	else if( event.getCode() == app::KeyEvent::KEY_DOWN && !clusters.empty()) {
            (*selectedCluster)->moveDown(1);
	}
    else if( event.getCode() == app::KeyEvent::KEY_LEFT && !clusters.empty() ) {
              (*selectedCluster)->moveLeft(1);
    }
    else if( event.getCode() == app::KeyEvent::KEY_RIGHT && !clusters.empty()) {
        (*selectedCluster)->moveRight(1);
    }
    else if( event.getCode() == app::KeyEvent::KEY_TAB ) {
        controller.changeSelectedCluster(clusters, selectedCluster);
    }    
    else if( event.getCode() == 'a' ) {
        
        //TODO catch exception here, or other way to point an iterator
        parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");
    //    mParams =   params::InterfaceGl( "App parameters", Vec2i( 200, 400 ) );
      clusterBar.loadParameters(clusters);

        // if this is the first element in the vector, set Iterator new
       // if(clusters.size() == 1)
            selectedCluster = clusters.end()-1;
    } else if( event.getCode() == 'd' && !clusters.empty()  ) {
        
        clusterBar.removeVar((*selectedCluster)->getId());
        controller.deleteSelectedCluster(clusters, selectedCluster);
      //  loadParameters(clusters, mParams); 
   

    }else if( event.getCode() == 's' ) {
        parser.saveCurrent(clusters);

    }else if( event.getCode() == 'l' ) {
        parser.loadScene(clusters);
        selectedCluster = clusters.end()-1;
        clusterBar.loadParameters(clusters);
    }else if( event.getCode() == 'c' ) {
        clusters.clear();
       clusterBar.removeAllVar();
    } 
    
    if(event.getCode() == app::KeyEvent::KEY_ESCAPE)
        setFullScreen(false);
	if(event.getCode() == 'f')
        setFullScreen(true);
    if(event.getCode() == '8')
        pos.y -=10;
    if(event.getCode() == '5')
        pos.y +=10;
    if(event.getCode() == '4')
        pos.x -=10;
    if(event.getCode() == '6')
        pos.x +=10;
    if(event.getCode() == app::KeyEvent::KEY_KP_PLUS ){
        scale++;
    }
    if(event.getCode() == app::KeyEvent::KEY_m){
        scale--;
    }


}

void ForelleVisualAppApp::update()
{    
    //othe way to initialsie with 0, and don´t have to update ??
    for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
        data[i]=0;

    }
    
    
  
}

void ForelleVisualAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color(0, 0,0 ) ); 
  	
    
    
   // if( surface)
        //update our Client
        // stick together  with draw;
        client.update();
        //draw the Image from the client
        gl::draw( *client.getTexture(), Rectf(pos.x,pos.y,pos.x+(60*scale),pos.y+(60*scale)));
    
    
    // draw Pixel grid
    gl::color( Colorf(1.0f, 1.0f, 1.0f) );
    gl::pushMatrices();
    gl::translate(pos);
	for(float i=0;i<=60*scale;i+=scale) {
		gl::drawLine( Vec2f(i,  0), Vec2f(i,  60*scale) );
		gl::drawLine( Vec2f(0,  i), Vec2f(60*scale,  i) );
	}
    gl::popMatrices();



   
    //   if(readPixels)
    controller.updateAndDrawClusters(clusters, *client.getSurface(), pos, scale);
    controller.getData(clusters,data);
       
    //  if(sendData)
        node.sendDataAtPort(data, 0);
      
    // Draw the interface
	clusterBar.draw();
	


}




CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
