#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "Cluster.h"
#include "CinderArtnet.h"
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

    Cluster cluster;
     uint8_t data[512]= {0};
    CinderArtnet node;
    
};

void ForelleVisualAppApp::setup()
{
    node = CinderArtnet("Node1", "LongName", "10.0.2.2");
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
    node.enableDMXPortAsInputAndSetAdress(0, 1);
    node.startNode();
    
    cluster = Cluster(0);
    cluster.setStartAdress(3);
    cluster.addGroupWithLightsAndChannels(4,"rgb");
   // cluster.addGroupWithLightsAndChannels(4,3);
  //  cluster.printUsedChannels();
  //  cluster.addGroupWithLightsAndChannels(3,6);
  //  cluster.printUsedChannels();

 //   cluster.addGroupWithLightsAndChannels(3,3);
  //  cluster.printUsedChannels();
    
    cluster.getData(data);

}

void ForelleVisualAppApp::mouseDown( MouseEvent event )
{
}

void ForelleVisualAppApp::update()
{
}

void ForelleVisualAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
      node.sendDataAtPort(data, 0);
}



CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
