//
//  game_rendering.cpp
//  amethyst_engine
//
//  Created by Albert Bode on 6/13/17.
//  Copyright � 2017 Albert Bode. All rights reserved.
//
#include "game_rendering.h"

void splash_text(void *font, char *string){
    glClearColor(1.0,1.0,1.0,1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f(0.0,0.0,0.0);
    char *c;
    char *b;
    float offset = 0;
    for (b=string; *b != '\0'; b++){
        offset += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *b);
    }
	glRasterPos2f(0.0f-offset/(float(winWidth)*2.0f),0.0f);

	for(c=string; *c != '\0'; c++){
		glutBitmapCharacter(font, *c);
	}
	glutSwapBuffers();
}

void drawText(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x,y);

	for(c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void draw_terrain(int polymode){
    glPushMatrix();

    // Set color of object
    glColor3f(0.1, 0.4, 0.1);
    // Set draw mode of object (wire-frame, solid, points)
    glPolygonMode(GL_FRONT_AND_BACK, polymode);

    // Add polygons
    glBegin(GL_TRIANGLES);
        glVertex3f(1000, -10, 1000);
        glVertex3f(1000, -10, -1000);
        glVertex3f(-1000, -10, -1000);

        glVertex3f(1000, -10, 1000);
        glVertex3f(-1000, -10, 1000);
        glVertex3f(-1000, -10, -1000);
    glEnd();
    glPopMatrix();
}

void draw_grid(int spacing){
    glLineWidth(2.5);
    glColor4f(0.8,0.8,0.8,0.5);
    for (int i=0; i<spacing*200; i+=spacing){
        glBegin(GL_LINES);
            glVertex3f(1000-i,-10,1000);
            glVertex3f(1000-i,-10,-1000);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(1000,-10,1000-i);
            glVertex3f(-1000,-10,1000-i);
        glEnd();
    }
    /*
    if(text){
        std::string cord_string;
        char *c;
        for (int i=0; i<spacing*20; i+=spacing){
            cord_string = i-100 + ",0";
            c = (char *)cord_string.c_str();
            drawText(i-100,0,GLUT_BITMAP_HELVETICA_10,c);
        }
        for (int i=0; i<spacing*20; i+=spacing){
            cord_string = "0," + i-100;
            c = (char *)cord_string.c_str();
            drawText(0,i-100,GLUT_BITMAP_HELVETICA_10,c);
        }
    }
    */
};

int getNextId(){
	return glutid++;
};
