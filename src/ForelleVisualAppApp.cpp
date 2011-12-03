#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "CinderArtnet.h"
#include "XmlParser.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder/ImageIo.h"
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
    void printClusters(vector<Cluster> &clusters);
    void updateAndDrawClusters(vector<Cluster> &clusters, Surface &surface);
    void changeSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster);
    void getData(uint8_t *data);
 
    //  void getPixelValue(vector<Cluster> &clusters);
    vector<Cluster> clusters;
    uint8_t data[512]= {0};
    CinderArtnet node;
    XmlParser parser;
    Surface surface;	
    
    Boolean readPixels;
    Boolean sendData;

    //selected cluster
    vector<Cluster>::iterator selectedCluster;
    
    
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
    node = CinderArtnet("Node1", "LongName", "10.0.2.2");
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
    node.enableDMXPortAsInputAndSetAdress(0, 1);
   // node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.startNode();
     

    //setup boolean variables
    
    readPixels = true;
    sendData  = true;
    
    parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");
    parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");
 
    surface = Surface( loadImage(loadResource(RES_IMAGE) ));

    if(!clusters.empty())
        selectedCluster = clusters.end()-1;
         

    printClusters(clusters);
    
}

void ForelleVisualAppApp::mouseDown( MouseEvent event )
{
}
void ForelleVisualAppApp::keyDown( KeyEvent event )
{
    if( event.getCode() == app::KeyEvent::KEY_UP && !clusters.empty() ) {
		selectedCluster->moveUp(1);
	}
	else if( event.getCode() == app::KeyEvent::KEY_DOWN && !clusters.empty()) {
            selectedCluster->moveDown(10);
	}
    else if( event.getCode() == app::KeyEvent::KEY_LEFT && !clusters.empty() ) {
              selectedCluster->moveLeft(10);
    }
    else if( event.getCode() == app::KeyEvent::KEY_RIGHT && !clusters.empty()) {
        selectedCluster->moveRight(10);
    }
    else if( event.getCode() == app::KeyEvent::KEY_TAB ) {
        changeSelectedCluster(clusters, selectedCluster);
    }    
    else if( event.getCode() == 'a' ) {
        parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight2.xml");
        // if this is ther first element in the vector, set Iterator new
        if(clusters.size() == 1)
            selectedCluster = clusters.end()-1;
    }

}

void ForelleVisualAppApp::update()
{    

}

void ForelleVisualAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
  	
	if( surface)
		gl::draw( surface, Vec2f( 0, 0 ) );
    
    if(readPixels)
        updateAndDrawClusters(clusters, surface);
        getData(data);
   // console() << selectedCluster->getName() << endl;
  //  printClusters(clusters);
    
    if(sendData)
        node.sendDataAtPort(data, 0);


}
void ForelleVisualAppApp::printClusters(vector<Cluster> &clusters)
{    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->printCluster();
        
    }
    
}
void ForelleVisualAppApp::updateAndDrawClusters(vector<Cluster> &clusters, Surface &surface){
    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->updateAndDrawCluster(surface);        
    }
    
    
}
void ForelleVisualAppApp::getData(uint8_t *data){
    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->getChannelData(data);        
    }
    
    
}
void ForelleVisualAppApp::changeSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster){
    
    if(!clusters.empty()){
    
        if(selectedCluster == clusters.begin())
            selectedCluster =  clusters.end()-1  ;
        else
            --selectedCluster;
    }
}


CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
