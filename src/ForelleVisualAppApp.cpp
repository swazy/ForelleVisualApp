#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "controller.h"

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

    Controller controller;
    int data[512];
    
    
};

void ForelleVisualAppApp::setup()
{
    
    controller = Controller(0);
    controller.addGroupWithLightsAndChannels(3,6);
    controller.printUsedChannels();
    controller.addGroupWithLightsAndChannels(3,6);
    controller.printUsedChannels();

 //   controller.addGroupWithLightsAndChannels(3,3);
  //  controller.printUsedChannels();
    
    controller.getData(data);

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
}



CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
