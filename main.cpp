/* Main.cpp
 * Amethyst Engine
 *
 * Written by Albert Bode June 2017
 */

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
// External library include statements
#include <stdlib.h>
#include <iostream>
#include <vector>
// Internal header includes
#include "obj_model.h"
#include "fpsTimer.h"
#include "keyboard.h"
#include "mouse.h"
#include "engine_keys.h"
#include "game_rendering.h"

#define SELECT_BUFFSIZE 10
using namespace std;

// Global Variables
keyboard_handler k = keyboard_handler();
mouse_handler m = mouse_handler();
std::map<string,model*> models;
vector<model_instance*> objects;
FpsTimer fpsTimer = FpsTimer(8);

int winHeight;
int winWidth;
double fovy;
double aspect_ratio;
int glutid;
model_instance *active;

void amethyst_Init(){
    // Background color
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
	fovy = 45.0;
	aspect_ratio = 1.333;
	glutid = 1;
	//active = NULL;

    // 3D world projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(fovy, aspect_ratio, 0.01, 1000.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-15);
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
}

// Function to be called when keyboard input is detected.
static void key(unsigned char key, int x, int y){
	void (*return_func)();
    return_func = k.keyInput(key, x, y);
    return_func();
};

static void keyup(unsigned char key, int x, int y){
	cout << key << " was released" << endl;
};

static void special_key(int key, int x, int y){
    cout << key << endl;
};

static void mouse( int button, int state, int x, int y ){
    // This could be changed to just call glut_mouse directly.
    // The reason it isn't currently is you have to get a function pointer and im too lazy to fix it.
    m.glut_mouse(button,state,x,y);
};

static void motion(int x, int y){
    // This could be changed to just call glut_motion directly.
    // The reason it isn't currently is you have to get a function pointer and im too lazy to fix it.
    m.glut_motion(x,y);
};

static void passivemotion(int x, int y){
	//cout << "Mouse Drag Position: " << x << ", " << y << ".\n";			// Debugging
}

static void visable(int state){
	if (state == GLUT_NOT_VISIBLE){
		cout << "The screen is not visable" << endl;
	};
	if (state == GLUT_VISIBLE){
		cout << "The screen is now visable" << endl;
	};
};

static void entry(int state){
	if (state == GLUT_LEFT){
		cout << "The mouse cursor left the screen" << endl;
	}
	if (state == GLUT_ENTERED){
		cout << "The mouse cursor entered the screen" << endl;
	}
};

// Function to be called when a display update is requested all of the drawing will happen in this function and any functions it calls.
static void display(void)
{
	fpsTimer.timeFrame();
    // Clear the buffer before drawing
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Define default light
    GLfloat light_position[] = {0, 0.5, 0.5, 0.0};
    GLfloat light_diffuse[] = {.9, .8, .5, 1.0};
    GLfloat light_ambient[] = {.1, .1, .1, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    // Draw all objects
    for(int i=0; i < objects.size(); i++){
		glPushMatrix() ; // save
        objects[i]->objDraw();
		glPopMatrix();
    }

	//glPushMatrix();
	//glLoadIdentity();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
    glDisable( GL_LIGHTING ); // Disable Lighting so text is correct color

    // Draw Terrain
    draw_terrain(GL_FILL);
    draw_grid(10);

    glDisable( GL_DEPTH_TEST ) ; // Disable Depth so that text renders on top

	// Set drawing mode to 2d projection
	glPushMatrix();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, winHeight, winWidth, 0, -1, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

    // Draw all text
    glColor3f(0.2,0.75,0.2);
	drawText(1.0f, 10.0f, GLUT_BITMAP_HELVETICA_10, fpsTimer.getFps());

    // Draw Mouse
    m.draw_mouse();

	glEnable( GL_DEPTH_TEST ) ; // Re-enable Depth
	glEnable( GL_LIGHTING ); // Re-enable Lighting
	//glPopMatrix();

	// Reset drawing mode to 3d projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(fovy, aspect_ratio, 0.01, 1000.0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glPopMatrix();

    glFlush();                  // Makes all the functions execute before it updates the display.
    glutSwapBuffers();          // when you call glut draw functions they draw not to the screen but to a buffer to display
                                // the the stuff you just drew you need to swap the buffer with the active screen.
	glutid = 1;
}

static void idle(void){
    glutPostRedisplay();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    winHeight = 640;
    winWidth = 480;

    // Initialize window system
    glutInit(&argc, argv);                                      // Initializes glut library which provides all draw calls
    glutInitWindowSize(winHeight,winWidth);                     // Window Size in pixels
    glutInitWindowPosition(10,10);                              // Window Offset in pixels
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // Sets screen format

    // Create main window
    glutCreateWindow("Amethyst");                               // Creates the Main Window with Title

    // Startup flow
    splash_text(GLUT_BITMAP_TIMES_ROMAN_24,"Loading Models");

    // Init of logic
    amethyst_Init();
	init_engine_keys();

    // Set function calls
    glutDisplayFunc( display );                     // Main draw function, called by glutPostRedisplay
    glutKeyboardFunc( key );                        // Called when a key is pressed
    glutSpecialFunc( special_key );					// Called when a non-traditional key is pressed ex. (F1, shift, cntl)
    glutMouseFunc( mouse );                         // Called when mouse button input is detected
    glutMotionFunc( motion );                       // Called when the mouse moves and has button(s) pressed
    glutIdleFunc( idle );                           // Called when the program has no input.

	// Not used except for debugging, if you want to use one go ahead and implement it.
	glutEntryFunc( entry );							// Called when the mouse leaves or enters the screen
	glutVisibilityFunc( visable );					// Called when the screen becomes not visable or visable.
	glutPassiveMotionFunc( passivemotion );			// Called when the mouse moves but doesnt have any buttons pressed
	glutKeyboardUpFunc( keyup );					// Called when a key is released

	// Loading Models
	model buckyball = model("buckyball.obj",1);
	model cow = model("cow.obj",2);
	models["buckyball"] = &buckyball;
	models["cow"] = &cow;

	// Creation of instances and setting of cords.
	model_instance b1 = model_instance("buckyball");
	model_instance c1 = model_instance("cow");
	c1.set_location(10, 0, 0);
	model_instance c2 = model_instance("cow");
	c2.set_location(-10, 0, 0);
	objects.push_back(&b1);
	objects.push_back(&c1);
	objects.push_back(&c2);

	// Set default active object.
	active = &b1;

	// Count the amount of polygons being rendered.
    int polycount = 0;
    for (int i=0; i < objects.size(); i++){
        polycount += objects[i]->object_model->get_faces();
    }

    cout << "Total number of polys being Rendered: "<< polycount*3 << endl;

    glutMainLoop();                                             // Main event loop

    return EXIT_SUCCESS;
}
