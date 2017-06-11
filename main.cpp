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
#include "engine_keys.h"

using namespace std;

// Global Variables
keyboard_handler k = keyboard_handler();
vector<model> objects;
FpsTimer fpsTimer = FpsTimer(8);

void myInit(){
    // Background color
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // 3D world projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0,1.333, 0.01, 1000.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-15);
    glEnable( GL_DEPTH_TEST );
}

void drawText(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x,y);

	for(c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

// Function to be called when keyboard input is detected.
static void key(unsigned char key, int x, int y){
	void (*return_func)();
    return_func = k.keyInput(key, x, y);
    return_func();
};

// Function to be called when a display update is requested all of the drawing will happen in this function and any functions it calls.
static void display(void)
{
	fpsTimer.timeFrame();
    // Clear the buffer before drawing
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw all objects
    for(int i=0; i < objects.size(); i++){
        objects[i].translatef(0.0, 0.0, i*-10.0);
		glPushMatrix() ; // save
        objects[i].objDraw();
		glPopMatrix();
        objects[i].translatef(10.0, 0.0, 0.0);
		glPushMatrix() ; // save
        objects[i].objDraw();
		glPopMatrix();
        objects[i].translatef(-20.0, 0.0, 0.0);
		glPushMatrix() ; // save
        objects[i].objDraw();
		glPopMatrix();
        objects[i].translatef(10.0, 0.0, 0.0);
        objects[i].translatef(0.0, 0.0, i*10.0);
    }

	//glPushMatrix();
	//glLoadIdentity();
	glDisable( GL_DEPTH_TEST ) ; // Disable Depth so that text renders on top
	//glDisable( GL_LIGHTING ); // Disable Lighting so text is correct color

    // Draw all text
    glColor3f(0.2,0.75,0.2);
	drawText(-8.1f, 5.9f, GLUT_BITMAP_HELVETICA_10, fpsTimer.getFps());

	glEnable( GL_DEPTH_TEST ) ; // Renable Depth
	//glPopMatrix();

    glutSwapBuffers();                                          // when you call glut draw functions they draw not to the screen but to a buffer to display
                                                                // the the stuff you just drew you need to swap the buffer with the active screen.
}

static void idle(void){
    glutPostRedisplay();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    // Initialize window system
    glutInit(&argc, argv);                                      // Initializes glut library which provides all draw calls
    glutInitWindowSize(640,480);                                // Window Size in pixels
    glutInitWindowPosition(10,10);                              // Window Offset in pixels
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // Sets screen format

    // Create main window
    glutCreateWindow("Amethyst");                               // Creates the Main Window with Title

    // Init of logic
    myInit();
	init_engine_keys();

    // Set function calls
    glutDisplayFunc(display);                                   // Set the main draw function
    glutKeyboardFunc(key);                                      // Set function to call when keyboard input is detected
    glutIdleFunc(idle);                                         // set function to call when idle

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
