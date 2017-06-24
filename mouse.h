//
//  mouse.h
//  amethyst_engine
//
//  Created by Albert Bode on 6/13/17.
//  Copyright � 2017 Albert Bode. All rights reserved.
//

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "obj_model.h"

#define MOUSE_SELECT_MODE 1
#define MOUSE_PAN_MODE 2
#define MOUSE_ROTATE_MODE 3
#define MOUSE_DRAG_MODE 4

using namespace std;

typedef void (*func)(void);

class mouse_handler{
    // Current mouse position in pixel cords
    float current_x;
    float current_y;

    // Previous mouse position in pixel cords
    float last_x;
    float last_y;

    // Position for the start of the drag box
    float drag_reference_x;
    float drag_reference_y;

    // z position if needed for 3d cords
    float current_z;

    func left_button_func;
    func right_button_func;
    func middle_button_func;

    // Bools for weather an action is active;
    bool panning;
    bool dragging;
    bool rotating;

public:
    void draw_mouse();
    void idle_mouse();
    void glut_mouse( int button, int state, int x, int y );     // Callback function for glut
    void glut_motion( int x, int y );                           // Callback function for glut

    mouse_handler(){
        panning = false;
        dragging = false;
        rotating = false;
    };
};

extern int winHeight;
extern int winWidth;
#endif // MOUSE_H_INCLUDED
