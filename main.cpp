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

#define PICK_BUFFER_SIZE 256
#define PICK_TOL 5
using namespace std;

// Global Variables
keyboard_handler k = keyboard_handler();
mouse_handler m = mouse_handler();
std::map<string,model*> models;
vector<model_instance*> objects;
FpsTimer fpsTimer = FpsTimer(8);

unsigned int PickBuffer[PICK_BUFFER_SIZE];	// Picking buffer
int RenderMode;	// GL_RENDER or GL_SELECT
int winHeight;
int winWidth;
double fovy;
double aspect_ratio;
model_instance *active;

// Define default light
GLfloat light_position[] = {0, 0.5, 0.5, 0.0};
GLfloat light_diffuse[] = {.5, .5, .5, 1.0};
GLfloat light_ambient[] = {.1, .1, .1, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

void amethyst_Init(){
    // Background color
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

	fovy = 45.0;
	aspect_ratio = 1.333;
	//active = NULL;

    // 3D world projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(fovy, aspect_ratio, 0.01, 1000.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-15);

	RenderMode = GL_RENDER;	// Set default mode
	glSelectBuffer( PICK_BUFFER_SIZE, PickBuffer ); // Set the picking buffer
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );	// Sets the blending algorthim in the scene, required
	glEnable( GL_BLEND );		// Enables alpha values in the scene
    glEnable( GL_DEPTH_TEST );	// Enables depth in the scence
    glEnable( GL_LIGHTING );	// Enables lighting
    glEnable( GL_LIGHT0 );		// Enables the assignment of a light
}

static void resize(int x, int y){
	winHeight = x;
	winWidth = y;
	glViewport(0, 0, x, y);
	//cout << winHeight << winWidth << endl;
};

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

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Draw all objects
    for(std::vector<model_instance*>::iterator item = objects.begin(); item != objects.end(); item++){
		glPushMatrix() ; // save
        (*item)->objDraw();
		glPopMatrix();
    }

    glDisable( GL_LIGHTING ); // Disable Lighting so text is correct color

    // Draw Terrain
    draw_terrain(GL_FILL);
    draw_grid(10);

	// Raster text will screw up the picking matrix so only do it if in rendering mode.
	if ( RenderMode == GL_RENDER ){
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

		// Reset drawing mode to 3d projection
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(fovy, aspect_ratio, 0.01, 1000.0);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glPopMatrix();
	}

    glFlush();						// Makes all the functions execute before it updates the display.
	if(RenderMode == GL_RENDER){	// when you call glut draw functions they draw not to the screen, but to a buffer to
		glutSwapBuffers();			// display the the stuff you just drew you need to swap the buffer with the active
									// screen. When you are in select mode the buffer is not intended to be shown.


	}
}

void select_object(int x, int y){
	int hits;

	// Viewport information
	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	// Selection mode
	glSelectBuffer( PICK_BUFFER_SIZE, PickBuffer );
	glRenderMode( GL_SELECT );

	// Initialize name stack
	glInitNames();
	glPushName(-1);

	// Save transformation matrix
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	// Save original projection (viewing volume)
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();

	// New picking viewing volume (area == 5 pixels)
	glLoadIdentity();
	gluPickMatrix ( GLdouble( x ),GLdouble( viewport[3] - y ),PICK_TOL, PICK_TOL, viewport);
	gluPerspective( fovy, aspect_ratio, 0.01, 1000 );

	// Draw scene
	display();

	// Restore original projection (viewing volume)
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	// Restore original modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	// End select mode
	hits = glRenderMode( GL_RENDER );
	if (hits > 0){
		for (std::vector<model_instance*>::iterator item = objects.begin(); item != objects.end(); item++){
			if ((*item)->model_instance_id == PickBuffer[3]){
				active = (*item);
			}
		}
	}
}

static void idle(void){
    //m.idle_mouse();
    glutPostRedisplay();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    winHeight = 640;
    winWidth = 480;

    // Initialize window system
    glutInit(&argc, argv);                                      // Initializes glut library which provides the interface for drawing to the screen.
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
	glutReshapeFunc( resize );						// Called when the window is resized.
    glutKeyboardFunc( key );                        // Called when a key is pressed
	glutKeyboardUpFunc( keyup );					// Called when a key is released
    glutSpecialFunc( special_key );					// Called when a non-traditional key is pressed ex. (F1, shift, cntl)
    glutMouseFunc( mouse );                         // Called when mouse button input is detected
    glutMotionFunc( motion );                       // Called when the mouse moves and has button(s) pressed
    glutIdleFunc( idle );                           // Called when the program has no input.

	// Not used except for debugging, if you want to use one go ahead and implement it.
	glutEntryFunc( entry );							// Called when the mouse leaves or enters the screen

	glutVisibilityFunc( visable );					// Called when the screen becomes not visible or visible.
	glutPassiveMotionFunc( passivemotion );			// Called when the mouse moves but doesn't have any buttons pressed
	glutKeyboardUpFunc( keyup );					// Called when a key is released

    model buckyball = model("buckyball.obj", 1, "buckyball");
	model cow = model("cow.obj", 2, "cow");
	models["buckyball"] = &buckyball;
	models["cow"] = &cow;

	// Creation of instances and setting of cords.
	model_instance b1 = model_instance("buckyball");
	b1.set_location(0.0f, 0.0f, 0.0f);
	model_instance c1 = model_instance("cow");
	c1.set_location(10.0f, 0.0f, 0.0f);
	model_instance c2 = model_instance("cow");
	c2.set_location(-10.0f, 0.0f, 0.0f);
    model_instance c3 = model_instance("cow");
	c3.set_location(0.0f, 10.0f, 0.0f);
    model_instance c4 = model_instance("cow");
	c4.set_location(0.0f, 0.0f, -10.0f);
	model_instance c5 = model_instance("cow");
	c5.set_location(10.0f, 0.0f, -10.0f);
	model_instance c6 = model_instance("cow");
	c6.set_location(-10.0f, 0.0f, -10.0f);

    objects.push_back(&b1);
	objects.push_back(&c1);
	objects.push_back(&c2);
	objects.push_back(&c3);
	objects.push_back(&c4);
	objects.push_back(&c5);
    objects.push_back(&c6);

	// Set default active object.
	active = &b1;

	// Count the amount of polygons being rendered.
    int polycount = 0;
    for (std::vector<model_instance*>::iterator item = objects.begin(); item != objects.end(); item++){
        polycount += (*item)->object_model->get_faces();
    }

    cout << "Total number of polys being Rendered: " << polycount << endl;

    glutMainLoop();                                             // Main event loop

    return EXIT_SUCCESS;
}
