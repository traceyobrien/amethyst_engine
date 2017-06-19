//
//  game_rendering.h
//  amethyst_engine
//
//  Created by Albert Bode on 6/13/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
//
#ifndef GAME_RENDERING_H_INCLUDED
#define GAME_RENDERING_H_INCLUDED

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
void splash_text(void *font, char *string);
void draw_terrain(GLint polymode);
void draw_grid(int spacing);
void drawText(float x, float y, void *font, char *string);

extern int winWidth;

#endif // GAME_RENDERING_H_INCLUDED
