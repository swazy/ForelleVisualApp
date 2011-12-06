#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "CinderArtnet.h"
#include "XmlParser.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder/ImageIo.h"
#include "cinder/params/Params.h"
#include "Controller.h"
#include "cinderSyphon.h"

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
    void loadParameters(vector<ClusterRef> &clusters, params::InterfaceGl mParams);

    //  void getPixelValue(vector<Cluster> &clusters);
    vector<ClusterRef> clusters;
   
    uint8_t data[512];
    CinderArtnet node;
    XmlParser parser;
  
    
    Surface surface;	
    
    Boolean readPixels;
    Boolean sendData;

    //selected cluster
    vector<ClusterRef>::iterator selectedCluster;
    
    // Parameter Window
    params::InterfaceGl		mParams;
    
    //Controller to manage Clusters
    Controller controller;


    
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
    mParams =  params::InterfaceGl( "App parameters", Vec2i( 200, 400 ) );

    
//	mParams.addParam( "Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z" );
//	mParams.addParam( "Cube Rotation", &mObjOrientation );
//	mParams.addParam( "Cube Color", &mColor, "" );	
//	mParams.addSeparator();	
//	mParams.addParam( "Light Direction", &mLightDirection, "" );
//	mParams.addButton( "Button!", std::bind( &TweakBarApp::button, this ) );
//	mParams.addParam( "String ", &mString, "" );
	
       
    
    //othe way to initialsie with 0, and don´t have to update ??
    for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
        data[i]= 0;
        
    }

    //setup boolean variables
    
    readPixels = true;
    sendData  = true;
    //  parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/patrickfuerst/Desktop/DEV/C++/Cinder/ForelleVisualApp/Templates/eurolight.xml");
 //   parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/pfu/Desktop/ForelleVisualApp/Templates/eurolight2.xml");
 
    surface = Surface( loadImage(loadResource(RES_IMAGE) ));

    if(!clusters.empty())
        selectedCluster = clusters.end()-1;
         

    controller.printClusters(clusters);
    // loadParameters(clusters, mParams);

    node = CinderArtnet("Art-Net Test", "LongName", "10.0.2.1");
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
     node.enableDMXPortAsInputAndSetAdress(0,1);
     node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.printConfig();

    node.startNode();


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
            (*selectedCluster)->moveDown(10);
	}
    else if( event.getCode() == app::KeyEvent::KEY_LEFT && !clusters.empty() ) {
              (*selectedCluster)->moveLeft(10);
    }
    else if( event.getCode() == app::KeyEvent::KEY_RIGHT && !clusters.empty()) {
        (*selectedCluster)->moveRight(10);
    }
    else if( event.getCode() == app::KeyEvent::KEY_TAB ) {
        controller.changeSelectedCluster(clusters, selectedCluster);
    }    
    else if( event.getCode() == 'a' ) {
        
        //TODO catch exception here, or other way to point an iterator
        parser.loadTemplateClusterToUniverse(clusters, 0,"/Users/patrickfuerst/Desktop/DEV/C++/Cinder/ForelleVisualApp/Templates/eurolight.xml");
    //    mParams =   params::InterfaceGl( "App parameters", Vec2i( 200, 400 ) );
      loadParameters(clusters, mParams);

        // if this is the first element in the vector, set Iterator new
       // if(clusters.size() == 1)
            selectedCluster = clusters.end()-1;
    } 
    else if( event.getCode() == 'd' ) {
        controller.deleteSelectedCluster(clusters, selectedCluster);
    }
    else if( event.getCode() == 's' ) {
        parser.saveCurrent(clusters);

    }
    else if( event.getCode() == 'l' ) {
        parser.loadScene(clusters);
        selectedCluster = clusters.end()-1;
        loadParameters(clusters, mParams);

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
  	
    
    if( surface)
		gl::draw( surface, Vec2f( 0, 0 ) );
    
    //   if(readPixels)
       controller.updateAndDrawClusters(clusters, surface);
    controller.getData(clusters,data);
       
    //  if(sendData)
        node.sendDataAtPort(data, 2);
    
    
    // Draw the interface
	params::InterfaceGl::draw();
	


}
void ForelleVisualAppApp::loadParameters(vector<ClusterRef> &clusters, params::InterfaceGl mParams){
    

    vector<ClusterRef>::iterator it;
    int c = 0, g= 0, l = 0;
    stringstream cc,gg,ll;
    
    for (it = clusters.begin(); it < clusters.end(); it++) {
        cc.str(std::string());
        string clusterName = *(*it)->getName();
        cc << c;
        mParams.addParam( cc.str()+"x" , &(*it)->getPos()->x, "label=`X` group="+clusterName+cc.str() );	
        mParams.addParam( cc.str()+"y" , &(*it)->getPos()->y, "label=`Y` group="+clusterName+cc.str() );
        mParams.addParam( cc.str()+"StartAdress" , (*it)->getStartAdress(), "label=`StartAdress` group="+clusterName+cc.str() );    
        mParams.addParam( cc.str()+"Universe" , (*it)->getUniverse(), "label=`Universe` group="+clusterName+cc.str() );    
        
        vector<GroupRef> *groups = (*it)->getGroups();
        vector<GroupRef>::iterator it2;
        
        for(it2 = groups->begin(); it2 < groups->end(); it2++){
            gg.str(std::string());
            gg << g;
            string groupName = *(*it2)->getName();
            mParams.addParam( gg.str()+"Xoffset" , &(*it2)->getPosOffset()->x, "label=`XOffset` group="+groupName+gg.str() );    
            mParams.addParam( gg.str()+"Yoffset" , &(*it2)->getPosOffset()->y, "label=`YOffset` group="+groupName+gg.str() );    
            // mParams.addParam( "AdressOffset" , it2->getAdressOffset(), "group="+groupName );    
            mParams.setOptions( groupName+gg.str() , " group="+clusterName+cc.str()+" opened=false");
            
            
            vector<LightRef> *lights = (*it2)->getLights();
            vector<LightRef>::iterator it3;
            
            for(it3 = lights->begin(); it3 < lights->end(); it3++){
                ll.str(std::string());
                ll << l;
                              
                string lightName = *(*it3)->getName();
                
                mParams.addParam( ll.str()+"Xoffset" , &(*it3)->getPosOffset()->x, "label=`XOffset' group="+lightName+ll.str());    
                mParams.addParam( ll.str()+"Yoffset" , &(*it3)->getPosOffset()->y, "label=`XOffset' group="+lightName+ll.str() );    
                // mParams.addParam( "AdressOffset" , (*it3)->getAdressOffset(), "group="+lightName);    
                mParams.setOptions( lightName+ll.str() , " group="+groupName+gg.str()+" opened=false");
               
                
                l++;
            }
            
            g++;
        }

        c++;   
    }

    
    
}




CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
