//
//  mouse.cpp
//  amethyst_engine
//
//  Created by Albert Bode on 6/13/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
//

#include "mouse.h"

void mouse_handler::select_mode(int button, int state, int x, int y){
    /*GLuint selectBuffer[ SELECT_BUFfSIZE ];
    GLuint *ptr, names;
    int hits, i, j;

    // Viewport information
    GLuint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );

    // Selection mode
    glSelectBuffer( SELECT_BUFFSIZE, selectBuffer);
    glRenderMode(GL_SELECT);

    // Initialize name stack
    glInitNames();
    */
};
void mouse_handler::drag_mode(int button, int state, int x, int y){

};
void mouse_handler::pan_mode(int button, int state, int x, int y){

};
void mouse_handler::rotate_mode(int button, int state, int x, int y){

};

void mouse_handler::draw_mouse(){
    if(panning){
        glTranslatef(current_x-lastx,current_y-lasty,current_z-lastz);
    };
    if(rotating){
        glRotatef(current_x-lastx,1.0,0.0,0.0);
        glRotatef(current_y-lasty,0.0,1.0,0.0);
        glRotatef(current_z-lastz,0.0,0.0,1.0);
    }
    if(draging){
        glColor4f(0.3,0.3,0.9,0.175);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glBegin(GL_POLYGON);
        glVertex3f(drag_reference_x,drag_reference_y,current_z);
        glVertex3f(drag_reference_x,current_y,current_z);
        glVertex3f(current_x,current_y,current_z);
        glVertex3f(current_x,drag_reference_y,current_z);
        glEnd();
        glColor4f(0.3,0.3,0.9,0.9);
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBegin(GL_POLYGON);
        glVertex3f(drag_reference_x,drag_reference_y,current_z);
        glVertex3f(drag_reference_x,current_y,current_z);
        glVertex3f(current_x,current_y,current_z);
        glVertex3f(current_x,drag_reference_y,current_z);
        glEnd();
    }
};

void mouse_handler::glut_motion( int x, int y ){
    lastx = current_x;
    lasty = current_y;
    current_x = float(x - winWidth/2) / winWidth;
    current_y = float(-y + winHeight/2) / winHeight;

    /*
    if (mousey > winHeight){
        mousey += -winHeight;
    };
    if (mousey < 0.0){
        mousey += winHeight;
    };
    if (mousex > winWidth){
        mousex += -winWidth;
    };
    if (mousex < 0.0){
        mousex += winWidth;
    };
    */

    //drag_reference_x = x;
    //drag_reference_y = y;

    //Print the mouse drag position
    cout << "Internal cord: " << current_x << ", " << current_y << ".\n";
    cout << "Mouse Drag Position: " << x << ", " << y << ".\n";
    glutPostRedisplay();
};

void mouse_handler::glut_mouse( int button, int state, int x, int y ){
    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){
            cout << "you pressed the left button" << endl;
            drag_reference_x = float(x - winWidth/2) / winWidth ;
            drag_reference_y = float(-y + winHeight/2) / winHeight;
            current_x = float(x - winWidth/2) / winWidth;
            current_y = float(-y + winHeight/2) / winHeight;
            lastx = current_x;
            lasty = current_y;
            draging = true;
        }
        if(state == GLUT_UP){
            cout << "you released the left button" << endl;
            draging = false;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN){
            panning = true;
            cout << "you pressed the right button" << endl;
        }
        if(state == GLUT_UP){
            panning = false;
            cout << "you released the right button" << endl;
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        if(state == GLUT_DOWN){
            rotating = true;
            cout << "you pressed the middle button" << endl;
        }
        if(state == GLUT_UP){
            rotating = false;
            cout << "you released the middle button" << endl;
        }
        break;
    }
};
