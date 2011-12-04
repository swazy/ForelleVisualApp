#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "CinderArtnet.h"
#include "XmlParser.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder/ImageIo.h"
#include "cinder/params/Params.h"

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
    void deleteSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster);
    void getData(uint8_t *data);
    void loadParameters(vector<Cluster> &clusters, params::InterfaceGl mParams);

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
    
    // Parameter Window
    params::InterfaceGl		mParams;

    
    
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
	mParams = params::InterfaceGl( "App parameters", Vec2i( 200, 400 ) );
//	mParams.addParam( "Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z" );
//	mParams.addParam( "Cube Rotation", &mObjOrientation );
//	mParams.addParam( "Cube Color", &mColor, "" );	
//	mParams.addSeparator();	
//	mParams.addParam( "Light Direction", &mLightDirection, "" );
//	mParams.addButton( "Button!", std::bind( &TweakBarApp::button, this ) );
//	mParams.addParam( "String ", &mString, "" );

    
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
    parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight2.xml");
 
    surface = Surface( loadImage(loadResource(RES_IMAGE) ));

    if(!clusters.empty())
        selectedCluster = clusters.end()-1;
         

    printClusters(clusters);
    loadParameters(clusters, mParams);


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
        
        //TODO catch exception here, or other way to point an iterator
        parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight3.xml");
        loadParameters(clusters, mParams);

        // if this is ther first element in the vector, set Iterator new
       // if(clusters.size() == 1)
            selectedCluster = clusters.end()-1;
    } else if( event.getCode() == 'd' ) {
        deleteSelectedCluster(clusters, selectedCluster);
    }

}

void ForelleVisualAppApp::update()
{    
    //othe way to initialsie with 0, and don´t have to update ??
    for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
        data[i]= 0;

    }

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
    
    
    // Draw the interface
	params::InterfaceGl::draw();



}
void ForelleVisualAppApp::loadParameters(vector<Cluster> &clusters, params::InterfaceGl mParams){
    

    vector<Cluster>::iterator it;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        
        string clusterName = *it->getName();
        
        mParams.addParam( "X" , &it->getPos()->x, "group="+clusterName );	
        mParams.addParam( "Y" , &it->getPos()->y, "group="+clusterName );	
        mParams.addParam( "StartAdress" , it->getStartAdress(), "group="+clusterName );	
        mParams.addParam( "Universe" , it->getUniverse(), "group="+clusterName );	
//
//        vector<Group> groups = *it->getGroups();
//        vector<Group>::iterator it2;
//        
//        for(it2 = groups.begin(); it2 < groups.end(); it2++){
//            
//            string groupName = *it2->getName();
//            int *x = &it2->getPosOffset()->x;
//            console() << *x <<endl;
//            mParams.addParam( "Xoffset" , &it2->getPosOffset()->x, "group="+groupName );	
//            mParams.addParam( "Yoffset" , &it2->getPosOffset()->y, "group="+groupName );	
//            mParams.addParam( "AdressOffset" , it2->getAdressOffset(), "group="+groupName );	
//            mParams.setOptions( groupName , " group="+clusterName+" opened=false");
//
//            
//            vector<Light> *lights = it2->getLights();
//            vector<Light>::iterator it3;
//            
//            for(it3 = lights->begin(); it3 < lights->end(); it3++){
//                
//                vector<LightChannel> *channels = it3->getChannels();
//                vector<LightChannel>::iterator it4;
//           
//                string lightName = *it3->getName();
                
//                  mParams.addParam( "Xoffset" , &it3->getPosOffset()->x, "group="+lightName);	
//                mParams.addParam( "Yoffset" , &it3->getPosOffset()->y, "group="+lightName );	
//                mParams.addParam( "AdressOffset" , it3->getAdressOffset(), "group="+lightName);	
//                mParams.setOptions( lightName , " group="+groupName+" opened=false");
//                

//                
//                for(it4 = channels->begin(); it4 < channels->end(); it4++){
//                    
//                }
//                
//            }
 //   }

    }

    
    
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
void ForelleVisualAppApp::deleteSelectedCluster(vector<Cluster> &clusters, vector<Cluster>::iterator &selectedCluster){
    
    if(!clusters.empty()){
        
    
        selectedCluster = clusters.erase(selectedCluster);
    }
}

CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
