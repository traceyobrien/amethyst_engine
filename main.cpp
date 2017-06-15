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
vector<model> objects;
FpsTimer fpsTimer = FpsTimer(8);

int winHeight;
int winWidth;

void myInit(){
    // Background color
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // 3D world projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0, 1.333, 0.01, 1000.0);
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
        objects[i].translatef(0.0, 0.0, i*-10.0);
		glPushMatrix() ; // save
        objects[i].objDraw();
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


    // Draw all text
    glColor3f(0.2,0.75,0.2);
	drawText(-8.1f, 5.9f, GLUT_BITMAP_HELVETICA_10, fpsTimer.getFps());

    // Draw Mouse
    m.draw_mouse();

	glEnable( GL_DEPTH_TEST ) ; // Re-enable Depth
	glEnable( GL_LIGHTING ); // Re-enable Lighting
	//glPopMatrix();

    glFlush();                  // Makes all the functions execute before it updates the display.
    glutSwapBuffers();          // when you call glut draw functions they draw not to the screen but to a buffer to display
                                // the the stuff you just drew you need to swap the buffer with the active screen.
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
    myInit();
	init_engine_keys();

    // Set function calls
    glutDisplayFunc( display );                                   // Set the main draw function
    glutKeyboardFunc( key );                                      // Set function to call when keyboard input is detected
    glutSpecialFunc( special_key );
    glutMouseFunc( mouse );                                       // Set function to call when mouse input is detected
    glutMotionFunc( motion );                                     // Set function to call for mouse motion.
    glutIdleFunc( idle );                                         // set function to call when idle

    objects.push_back(model("buckyball.obj"));
    //objects.push_back(model("killeroo.obj"));

    int polycount = 0;
    for (int i=0; i < objects.size(); i++){
        polycount += objects[i].get_faces();
    }

    cout << "Total number of polys being Rendered: "<< polycount*3 << endl;

    glutMainLoop();                                             // Main event loop

    return EXIT_SUCCESS;
}
