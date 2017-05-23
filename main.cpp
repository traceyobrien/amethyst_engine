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
#include "Camera.h"

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


    for(int i=0; i < objects.size(); i++){
        objects[i].objDraw();
        objects[i].location.x = objects[i].location.x + 10;
        objects[i].objDraw();
        objects[i].location.x = objects[i].location.x + -20;
        objects[i].objDraw();
        objects[i].location.x = objects[i].location.x + 10;
    }

    glutSwapBuffers();                                          // when you call glut draw functions they draw not to the screen but to a buffer to display
                                                                // the the stuff you just drew you need to swap the buffer with the active screen.
}

// Function to be called when keyboard input is detected.
static void key(unsigned char key, int x, int y)
{
    switch (key)                                                // key is the input from the keyboard
    {
        case 'r':
            // Reset all location and rotation information
            for (int i=0; i < objects.size(); i++){
                objects[i].location.z = 0;
                objects[i].location.y = 0;
                objects[i].location.x = 0;
                objects[i].spin = 0;
            }
            break;
        case 'x':
            // Move all objects 1.0 in z axis

            for (int i=0; i < objects.size(); i++){
                objects[i].location.z = objects[i].location.z + 1.0;
                cout << objects[i].location.x << objects[i].location.y << objects[i].location.z << endl;
            }
            break;
        case 'z':
            // Move all objects -1.0 in z axis
            for (int i=0; i < objects.size(); i++){
                objects[i].location.z = objects[i].location.z + -1.0;
                cout << objects[i].location.x << objects[i].location.y << objects[i].location.z << endl;
            }
            break;
        case 'w':
            // Move all objects 1.0 in y axis
            for (int i=0; i < objects.size(); i++){
                objects[i].location.y = objects[i].location.y + 1.0;
                cout << objects[i].location.x << objects[i].location.y << objects[i].location.z << endl;
            }
            break;
        case 's':
            // Move all objects -1.0 in y axis
            for (int i=0; i < objects.size(); i++){
                objects[i].location.y = objects[i].location.y + -1.0;
                cout << objects[i].location.x << objects[i].location.y << objects[i].location.z << endl;
            }
            break;
        case 'a':
            // Move all objects 1.0 in x axis
            for (int i=0; i < objects.size(); i++){
                objects[i].location.x = objects[i].location.x - 1.0;
                cout << objects[i].location.x << objects[i].location.y << objects[i].location.z << endl;
            }
            break;
        case 'd':
            // Move all objects -1.0 in x axis
            for (int i=0; i < objects.size(); i++){
                objects[i].location.x = objects[i].location.x + 1.0;
                cout << objects[i].location.x << objects[i].location.y << objects[i].location.z << endl;
            }
            break;
        case 'p':
            // Start Rotation animation.
            for (int i=0; i < objects.size(); i++){
                objects[i].animation = !objects[i].animation;
            }
            break;
        case 'q':
            // Quit program
            exit(0);
            break;
    }

    glutPostRedisplay();                                        // Tells display to redraw/update display
}

// Function to be called when idle
static void idle(void)
{
    for (int i=0; i < objects.size(); i++){
        if (objects[i].animation){
            objects[i].spin = objects[i].spin + 1.0;
            if (objects[i].spin > 360){
                objects[i].spin = objects[i].spin - 360;
            }
        }
    }
    glutPostRedisplay();                                        // Tells display to redraw/update display
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

    // Set function calls
    glutDisplayFunc(display);                                   // Set the main draw function
    glutKeyboardFunc(key);                                      // Set function to call when keyboard input is detected
    glutIdleFunc(idle);                                         // set function to call when idle

    objects.push_back(model("C:\\Program Files \(x86\)\\amethyst_engine\\Resources\\buckyball.obj"));

    glutMainLoop();                                             // Main event loop

    return EXIT_SUCCESS;
}
