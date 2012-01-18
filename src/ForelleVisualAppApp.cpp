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
    void saveAsCluster();
    void saveAsScene();
    void saveAsStandartScene();
    void loadScene();
    void loadClusterToUniverse();
    void clearScene();
    void showClusterBar();
    void deleteCluster();
    void saveSettings();
    void loadSettings();
    void shutdown();
    void allOn();
    void allOff();
    // store our clusters 
    vector<ClusterRef> clusters;
   
    // array for the data of the 512 DMX channels
    //uint8_t data[512];
    uint8_t data1[512],data2[512],data3[512],data4[512];
   
    //Artnet node where we send our data
    CinderArtnet node;
    string ipAdress;
    
    // xmlparser so read and write templates and scenes
    XmlParser parser;
  
    
    Surface surface;	
    
    bool readPixels;
    bool sendData;
    bool drawGrid;
    bool updateCluster;
    bool bAllOn, bAllOff;
    bool bShowClusterBar;
    bool selectedClusterOn;
    
    // Universe where we load our Cluster templates
    int templateUniverse;

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
    
    
    // our Logo
    gl::Texture		mLogo;	

   
    
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
    
    loadSettings();
    
    // Setup the parameters
    clusterBar =  ClusterBar( "Cluster Window", Vec2i( 200, 400 ) );

    //Setup menueBar
    
    menueBar = params::InterfaceGl( "Menue Window", Vec2i(300, 400 ), ColorA(0.5,0.5,0.5,0.1) );
    menueBar.setOptions("", "text=light position='724 0' valueswidth=100 contained=true");
    menueBar.addButton("Clear Scene ", std::bind( &ForelleVisualAppApp::clearScene, this ) );
    menueBar.addButton("Delete Selected Cluster", std::bind( &ForelleVisualAppApp::deleteCluster, this ) );
    menueBar.addParam("Draw Grid" , &drawGrid,"");
    menueBar.addParam("Read Pixel" , &readPixels, "true=reading false='not reading'");
    menueBar.addButton("Refresh ClusterBar", std::bind( &ForelleVisualAppApp::refreshClusterBar, this ) );
    menueBar.addParam("Update Cluster" , &updateCluster,"true=updating false='not updating'");
    menueBar.addParam("Send only Selected Cluster" , &selectedClusterOn,"");


    menueBar.addSeparator();	
    menueBar.addButton("Load Scene ", std::bind( &ForelleVisualAppApp::loadScene, this ) );
    menueBar.addButton("Load Cluster to Universe ", std::bind( &ForelleVisualAppApp::loadClusterToUniverse, this ) );
    menueBar.addParam("    Load to Universe" , &templateUniverse,"min=0 max=3 step=1");
    menueBar.addButton("Save as Cluster", std::bind( &ForelleVisualAppApp::saveAsCluster, this ) );
    menueBar.addButton("Save as Scene", std::bind( &ForelleVisualAppApp::saveAsScene, this ) );
    menueBar.addButton("Save as Standart Scene", std::bind( &ForelleVisualAppApp::saveAsStandartScene, this ) );
    menueBar.addParam("Send Data" , &sendData,"true=sending false='not sending'");
    
    menueBar.addSeparator();	
    menueBar.addSeparator();	
    menueBar.addParam("All On" , &bAllOn,"");
    menueBar.addParam("All Off" , &bAllOff,"");

    menueBar.addButton("Show ClusterBar", std::bind( &ForelleVisualAppApp::showClusterBar, this ) );
    menueBar.show(false);
    for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
        data1[i]= 0;
        data2[i]= 0;
        data3[i]= 0;
        data4[i]= 0;
    }

    //setup boolean variables
    readPixels = true;
    sendData  = true;
    drawGrid = true;
    updateCluster = true;
    bAllOn = false;
    bAllOff = false;
    bShowClusterBar = false;
    selectedClusterOn = false;
    
    //default load out templates to universe 0
    templateUniverse = 0;
 
  
    // set our pointer to the last added cluster
    if(!clusters.empty())
        selectedCluster = clusters.end()-1;
         

    controller.printClusters(clusters);


    
    //Setup Artnetnode
    
    if(ipAdress.empty() )
        ipAdress = "10.0.2.1";  //if it isn´t initalised already
    node = CinderArtnet("Art-Net Test", "LongName", ipAdress);
    node.setNodeTypeAsServer();
    node.setSubnetAdress(0);
    node.enableDMXPortAsInputAndSetAdress(0,1);
    node.enableDMXPortAsInputAndSetAdress(1, 2);
    node.enableDMXPortAsInputAndSetAdress(2, 3);
    node.enableDMXPortAsInputAndSetAdress(3, 4);
    node.printConfig();
    node.startNode();
    
    // initalize start our Syphone Client
    client.setup(Vec2i(60,60));
    pos = Vec2i(0,0);
    scale = 9;
     
    
    
    
 
    mLogo = gl::Texture( loadImage( loadResource(RES_LOGO) ) );
        

}
void ForelleVisualAppApp::refreshClusterBar()
{    
    clusterBar.removeAllVar();
    controller.barRefresh(clusters);
    clusterBar.loadParameters(clusters);    
}
void ForelleVisualAppApp::saveAsCluster()
{
    parser.saveAsCluster(clusters);        
}
void ForelleVisualAppApp::saveAsScene()
{
    parser.saveAsScene(clusters);    
}
void ForelleVisualAppApp::saveAsStandartScene()
{
    parser.saveAsScene(clusters,getResourcePath()+"/standartScene");    
}
void ForelleVisualAppApp::loadScene()
{
    parser.loadScene(clusters);
    selectedCluster = clusters.end()-1;
    clusterBar.loadParameters(clusters);    
}
void ForelleVisualAppApp::loadClusterToUniverse()
{
    //TODO catch exception here, or other way to point an iterator
    parser.loadTemplateClusterToUniverse(clusters, templateUniverse );
    clusterBar.loadParameters(clusters);
    
    // if this is the first element in the vector, set Iterator new
    // if(clusters.size() == 1)
    selectedCluster = clusters.end()-1;
    
}
void ForelleVisualAppApp::clearScene()
{
    clusters.clear();
    clusterBar.removeAllVar();
}


void ForelleVisualAppApp::showClusterBar()
{
    bShowClusterBar = !bShowClusterBar;
    clusterBar.isVisible(bShowClusterBar);
    if(bShowClusterBar)
        menueBar.setOptions("Show ClusterBar" , "label='Hide ClusterBar'");
    else
        menueBar.setOptions("Show ClusterBar" , "label='Show ClusterBar'");

}
void ForelleVisualAppApp::deleteCluster()
{    
    if(!clusters.empty()){
        
        clusterBar.removeVar((*selectedCluster)->getId());
        controller.deleteSelectedCluster(clusters, selectedCluster);
    }
}
void ForelleVisualAppApp::mouseDown( MouseEvent event )
{
}
void ForelleVisualAppApp::keyDown( KeyEvent event )
{
   


    if( event.isAccelDown() &&  event.getCode()== app::KeyEvent::KEY_n  ) {
        
        if(menueBar.isVisible())
            menueBar.show(false);
        else
            menueBar.show(true);

    }
	else if( event.getCode() == app::KeyEvent::KEY_UP && !clusters.empty() ) {
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
    else  
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
        data3[i]= 0;
        data4[i]= 0;

    }
    
     
}

void ForelleVisualAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color(0, 0,0 ) ); 
  	
    
    // draw our logo 
    gl::draw(mLogo, Vec2i(0, getWindowHeight()-mLogo.getHeight() ) );
    
    //update our Client
    // stick together  with draw;
    client.update();
    //gl::color( Colorf(0.0f, 0.0f, 0.0f) );
    //draw the Image from the client
    gl::draw( *client.getTexture(), Rectf(pos.x,pos.y,pos.x+(60*scale),pos.y+(60*scale)));
    
  
    
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
        controller.getData(clusters,data1,data2,data3,data4);
    
 
    
    if(bAllOn){
        
        for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
            data1[i]= 255;
            data2[i]= 255;
            data3[i]= 255;
            data4[i]= 255;
            
        }
        
    }else if(bAllOff){
        
        for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
            data1[i]= 0;
            data2[i]= 0;
            data3[i]= 0;
            data4[i]= 0;
            
        }
        
    }

    if(selectedClusterOn && !clusters.empty() ){
        for (int i=0; i < Const::MAX_DMX_CHANNELS ; i++) {
            data1[i]= 0;
            data2[i]= 0;
            data3[i]= 0;
            data4[i]= 0;
            
            int universe = *(*selectedCluster)->getUniverse();
            
            if (universe == 0) {
                (*selectedCluster)->getChannelData(data1);
            }else if (universe == 1) {
                (*selectedCluster)->getChannelData(data2);
            }else if (universe == 2) {
                (*selectedCluster)->getChannelData(data3);
            }else if (universe == 3) {
                (*selectedCluster)->getChannelData(data4);
            }

            
        }
        
    }
    
    if(sendData){
        node.sendDataAtPort(data1, 0);
        node.sendDataAtPort(data2, 1);
        node.sendDataAtPort(data3, 2);
        node.sendDataAtPort(data4, 3);
    }
    

    
    // Draw the interface
	clusterBar.draw();
	menueBar.draw();

}
void ForelleVisualAppApp::shutdown(){
    
    saveSettings();
}


void ForelleVisualAppApp::saveSettings(){
    
//    XmlTree settingsNode( "settings", "" );
//    
//    XmlTree artNetNode( "artNet", "" );
//    artNetNode.setAttribute("ipAdress", ipAdress);
//    
//    settingsNode.push_back(artNetNode);
//    try {
//        
//            settingsNode.write( writeFile( "../settings.xml" ) );
//        
//    }
//    catch( ... ) {
//        console() << "unable to save file" << std::endl;
//    }		
//
        
}
void ForelleVisualAppApp::loadSettings(){
    
    try{
    const XmlTree xml( loadFile( "settings.xml"  ) );
    
    
    ipAdress =  xml.getChild("settings/artNet").getAttributeValue<string>("ipAdress");
    
    }catch(StreamExc e){
        
        console() << "no settings file" << std::endl;

    }
    
    
    parser.loadScene(clusters, getResourcePath()+"/standartScene.xml");
    
}



CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
