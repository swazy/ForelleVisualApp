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
    
    Group  group, group2;
    
    
};

void ForelleVisualAppApp::setup()
{
    
        
    group =  Group();
    group.addLight(3);
    group.addLight(3);
    group.addLight(3);
    group.addLight(3);
    group2 =  Group();
    group2.addLight(3);
    group2.addLight(3);
    group2.addLight(3);
    group2.addLight(3);
    group2.addLight(3);

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
