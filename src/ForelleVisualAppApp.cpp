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
    void printClusters(vector<Cluster> &clusters);
 
    //  void getPixelValue(vector<Cluster> &clusters);
    vector<Cluster> clusters;
    uint8_t data[512]= {0};
    CinderArtnet node;
    XmlParser parser;
    Surface surface;	
    
    
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
    node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.startNode();
     

    parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight.xml");

    surface = Surface( loadImage(loadResource(RES_IMAGE) ));

    
    
    printClusters(clusters);
    
}

void ForelleVisualAppApp::mouseDown( MouseEvent event )
{
}

void ForelleVisualAppApp::update()
{    
  
//    if(!clusters.empty())
//        clusters.back().printCluster();
//    node.sendDataAtPort(data, 1);

}

void ForelleVisualAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    gl::clear( Color( 0.5f, 0.5f, 0.5f ) );
	gl::enableAlphaBlending();
	
	if( surface)
		gl::draw( surface, Vec2f( 0, 0 ) );
    if(!clusters.empty())
        clusters.back().updateAndDrawCluster(surface);
        
    

}
void ForelleVisualAppApp::printClusters(vector<Cluster> &clusters)
{    
    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        it->printCluster();
        
    }
    
}
//void ForelleVisualAppApp::getPixelValue(vector<Cluster> &clusters){
//    
//    vector<Group> groups = clusters.back().getGroupAt(0); 
//    vector<Group>::iterator it;
//    
//        
//    for(it = groups.begin(); it < groups.end(); it++){
//        console() << "\tGroupName:  " << *it->getName() <<endl;
//        vector<Light> *lights = it->getLights();
//        vector<Light>::iterator it2;
//        
//        for(it2 = lights->begin(); it2 < lights->end(); it2++){
//            
//            console() << "\t\tLight  " << *it2->getName() <<endl;
//            vector<LightChannel> *channels = it2->getChannels();
//            vector<LightChannel>::iterator it3;
//            
//            for(it3 = channels->begin(); it3 < channels->end(); it3++){
//                console() << "\t\t\tChannelSource  " << it3->getSource() << "  ChannelValue  " <<it3->getValue() << endl; 
//            }
//            
//        }
//    }

    
    
//}


CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
