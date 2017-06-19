//
//  mouse.cpp
//  amethyst_engine
//
//  Created by Albert Bode on 6/13/17.
//  Copyright � 2017 Albert Bode. All rights reserved.
//

#include "mouse.h"

void mouse_handler::draw_mouse(){
    if(panning){
		glPopMatrix();
        glTranslatef((current_x-last_x)/50,-(current_y-last_y)/50,0);  // move by dx,dy and 0
		glPushMatrix();
    };
    if(rotating){
		glPopMatrix();
        glRotatef((current_x-last_x)/10,0.0,1.0,0.0); // rotate x plane by dx
        glRotatef((current_y-last_y)/10,1.0,0.0,0.0); // rotate y plane by dy
		glPushMatrix();
    }
    if(dragging){
		// Fill of drag box
        glColor4f(0.3,0.3,0.9,0.175);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glBegin(GL_POLYGON);
        glVertex3f(drag_reference_x,drag_reference_y,current_z);
        glVertex3f(drag_reference_x,current_y,current_z);
        glVertex3f(current_x,current_y,current_z);
        glVertex3f(current_x,drag_reference_y,current_z);
        glEnd();
		// Outline of drag box
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
    //cout << "last cord: " << last_x << ", " << last_y << ".\n";
    //cout << "Mouse Drag Position: " << x << ", " << y << ".\n";			// Debugging
    //glutPostRedisplay();
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
			if(current_x == drag_reference_x && current_y == drag_reference_y){
				cout << "You clicked the left button" << endl;
			}
			else{
				cout << "You dragged the left button" << endl;
			}
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

