#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "CinderArtnet.h"
#include "XmlParser.h"
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
    void printClusters(vector<Cluster> &clusters);

    vector<Cluster> clusters;
    uint8_t data[512]= {0};
    CinderArtnet node;
    XmlParser parser;
};

void ForelleVisualAppApp::setup()
{
    node = CinderArtnet("Node1", "LongName", "10.0.2.2");
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
    node.enableDMXPortAsInputAndSetAdress(0, 1);
    node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.startNode();
     

    parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");

    
    
    
    printClusters(clusters);
    
    clusters.back().getData(data);
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
    
      node.sendDataAtPort(data, 1);
}
void ForelleVisualAppApp::printClusters(vector<Cluster> &clusters)
{    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->printCluster();
        
    }
    
}


CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
