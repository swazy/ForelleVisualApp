#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Group.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ForelleVisualAppApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Group  group;
    
    
};

void ForelleVisualAppApp::setup()
{
    
    
     Light light = Light();
    light.setBlue(12);
    
    group =  Group();
    group.addLight(&light);
    
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
    
    int i = group.getLight(0)->getBlue();
    console() << "blue = " << i << endl;
}


CINDER_APP_BASIC( ForelleVisualAppApp, RendererGl )
