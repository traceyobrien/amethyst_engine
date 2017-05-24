/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Other include statements
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "obj_model.h"

using namespace std;

// Global Variables
vector<model> objects;

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

// Function to be called when a display update is requested all of the drawing will happen in this function and any functions it calls.
static void display(void)
{
    // Clear the buffer before drawing
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw all objects
    for(int i=0; i < objects.size(); i++){
        objects[i].objDraw();
        objects[i].translatef(10.0, 0.0, 0.0);
        objects[i].objDraw();
        objects[i].translatef(-20.0, 0.0, 0.0);
        objects[i].objDraw();
        objects[i].translatef(10.0, 0.0, 0.0);
    }

    glutSwapBuffers();                                          // when you call glut draw functions they draw not to the screen but to a buffer to display
                                                                // the the stuff you just drew you need to swap the buffer with the active screen.
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
    keyboard();

    // Set function calls
    glutDisplayFunc(display);                                   // Set the main draw function
    glutKeyboardFunc(keyInput);                                      // Set function to call when keyboard input is detected
    glutIdleFunc(idle);                                         // set function to call when idle

    objects.push_back(model("buckyball.obj"));

    int polycount = 0;
    for (int i=0; i < objects.size(); i++){
        polycount += objects[i].get_faces();
    }

    cout << "Total number of polys being Rendered: "<< polycount*3 << endl;

    glutMainLoop();                                             // Main event loop

    return EXIT_SUCCESS;
}
