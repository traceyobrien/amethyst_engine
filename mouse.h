//
//  mouse.h
//  amethyst_engine
//
//  Created by Albert Bode on 6/13/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
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

#define MOUSE_SELECT_MODE 1
#define MOUSE_PAN_MODE 2
#define MOUSE_ROTATE_MODE 3
#define MOUSE_DRAG_MODE 4

using namespace std;

typedef void (*func)(void);


class mouse_handler{
    float current_x;
    float current_y;
    float current_z;
    float drag_reference_x;
    float drag_reference_y;

    float lastx;
    float lasty;
    float lastz;

    func left_button_func;
    func right_button_func;
    func middle_button_func;

    bool panning;
    bool draging;
    bool rotating;

public:
    // preset mouse modes
    void select_mode(int button, int state, int x, int y);
    void drag_mode(int button, int state, int x, int y);
    void pan_mode(int button, int state, int x, int y);
    void rotate_mode(int button, int state, int x, int y);

    void draw_mouse();
    void glut_mouse( int button, int state, int x, int y );     // Callback function for glut
    void glut_motion( int x, int y );                           // Callback function for glut

    mouse_handler(){
        panning = false;
        draging = false;
        rotating = false;
    };
};

extern int winHeight;
extern int winWidth;
#endif // MOUSE_H_INCLUDED
