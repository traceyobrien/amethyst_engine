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
        glTranslatef((current_x-last_x)/150.0,(current_y-last_y)/150.0,0);  // move by dx,dy and 0
    };
    if(rotating){
        glRotatef((current_x-last_x)/150.0,0.0,1.0,0.0); // rotate x plane by dx
        glRotatef((current_y-last_y)/150.0,1.0,0.0,0.0); // rotate y plane by dy
    }
    if(dragging){
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
    // Set last x before updating current position
    last_x = current_x;
    last_y = current_y;
    // Update current position
    current_x = x;
    current_y = y;

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

    //Print the mouse drag position
    cout << "last cord: " << last_x << ", " << last_y << ".\n";
    cout << "Mouse Drag Position: " << x << ", " << y << ".\n";
    glutPostRedisplay();
};

void mouse_handler::glut_mouse( int button, int state, int x, int y ){
     // Update current cord
    current_x = x;
    current_y = y;
    // Reset last x and y
    last_x = x;
    last_y = y;

    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){
            cout << "you pressed the left button" << endl;
            // Set reference point
            drag_reference_x = x;
            drag_reference_y = y;
            dragging = true;
        }
        if(state == GLUT_UP){
            cout << "you released the left button" << endl;
            dragging = false;
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
    case 3: // Scroll Up
        if(state == GLUT_DOWN){
            cout << "you scrolled up button" << endl;
            glTranslatef(0.0,0.0,1.0);
        }
        if(state == GLUT_UP){
            cout << "you pressed the middle button" << endl;
        }
        break;
    case 4: // Scroll Down
        if(state == GLUT_DOWN){
            glTranslatef(0.0,0.0,-1.0);
            cout << "you scrolled down button" << endl;
        }
        if(state == GLUT_UP){
            cout << "you pressed the middle button" << endl;
        }
        break;
    }
};
