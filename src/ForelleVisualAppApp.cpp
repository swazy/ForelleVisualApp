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
    void refreshClusterBar();

    // store our clusters 
    vector<ClusterRef> clusters;
   
    // array for the data of the 512 DMX channels
    //uint8_t data[512];
    uint8_t data1[512],data2[512];
    //Artnet node where we send our data
    CinderArtnet node;
    
    // xmlparser so read and write templates and scenes
    XmlParser parser;
  
    
    Surface surface;	
    
    bool readPixels;
    bool sendData;
    bool drawGrid;
    bool updateCluster;
    bool allOn;
    bool allOff;

    //selected cluster
    vector<ClusterRef>::iterator selectedCluster;
    
    // ClusterBar which shows all added Clusters
    ClusterBar clusterBar;
    
    params::InterfaceGl menueBar;
    
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

    //Setup menueBar
    
    menueBar = params::InterfaceGl( "Menue Window", Vec2i(200, 400 ) );
    menueBar.addParam("Read Pixel" , &readPixels, "");
    menueBar.addParam("Send Data" , &sendData,"");
    menueBar.addParam("Draw Grid" , &drawGrid,"");
    menueBar.addParam("Update Cluster" , &updateCluster,"");
    menueBar.addSeparator();	
    menueBar.addButton( "Refresh ClusterBar", std::bind( &ForelleVisualAppApp::refreshClusterBar, this ) );
    menueBar.addSeparator();	
    menueBar.addParam("All On" , &allOn,"");
    menueBar.addParam("All Off" , &allOff,"");
  
    
    //othe way to initialsie with 0, and don´t have to update ??
    for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
        data1[i]= 0;
        data2[i]= 0;
        
    }

    //setup boolean variables
    readPixels = true;
    sendData  = true;
    drawGrid = true;
    updateCluster = true;
    allOn = false;
    allOff = false;
    
    
    //  parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");
 //   parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight2.xml");
 
   // surface = Surface( loadImage(loadResource(RES_IMAGE) ));

    // set our pointer to the last added cluster
    if(!clusters.empty())
        selectedCluster = clusters.end()-1;
         

    controller.printClusters(clusters);
    // loadParameters(clusters, mParams);

    
    //Setup Artnetnode
    node = CinderArtnet("Art-Net Test", "LongName", "10.0.2.1");
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
    node.enableDMXPortAsInputAndSetAdress(0,1);
    node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.printConfig();
    node.startNode();
    
    // initalize start our Syphone Client
    client.setup(Vec2i(60,60));
    pos = Vec2i(0,0);
    scale = 1;


}
void ForelleVisualAppApp::refreshClusterBar()
{
    
    clusterBar.removeAllVar();
    controller.barRefresh(clusters);
    clusterBar.loadParameters(clusters);

        
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
        parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/patrickfuerst/Desktop/DEV/C++/Cinder/ForelleVisualApp/Templates/grosserFloor2.xml");
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
    if(event.getCode() == app::KeyEvent::KEY_p){
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
        data1[i]= 0;
        data2[i]= 0;
        


    }
    
    
  
}

void ForelleVisualAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color(0, 0,0 ) ); 
  	
    
    
    //update our Client
    // stick together  with draw;
    client.update();
    
    //draw the Image from the client
    gl::draw( *client.getTexture(), Rectf(pos.x,pos.y,pos.x+(60*scale),pos.y+(60*scale)));
    
    if(allOn == true || allOff == true){
        readPixels = false;
    }
    
    if (drawGrid) {

        // draw Pixel grid
        gl::color( Colorf(1.0f, 1.0f, 1.0f) );
        gl::pushMatrices();
            gl::translate(pos);
            for(float i=0;i<=60*scale;i+=scale) {
                gl::drawLine( Vec2f(i,  0), Vec2f(i,  60*scale) );
                gl::drawLine( Vec2f(0,  i), Vec2f(60*scale,  i) );
            }
        gl::popMatrices();
        
    }
    
    
    if(updateCluster)
        controller.updateAndDrawClusters(clusters, *client.getSurface(), pos, scale);

    if(readPixels)
        controller.getData(clusters,data1,data2);
    
    
    
    if(allOn){
        for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
            data1[i]= 255;
            data2[i]= 255;
            //allOn = false;

        }

    }
    if (allOff) {
        for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
            data1[i]= 0;
            data2[i]= 0;
            // allOff = false;
        }
    }
      
    if(sendData){
        node.sendDataAtPort(data1, 0);
        node.sendDataAtPort(data2, 1);
    }
    
    // Draw the interface
	clusterBar.draw();
	menueBar.draw();

}




CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
