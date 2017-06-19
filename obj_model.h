//
//  FpsTimer.h
//  amethyst_engine
//
//  Created by Albert Bode on 5/21/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
//

#ifndef OBJ_MODEL_H_INCLUDED
#define OBJ_MODEL_H_INCLUDED

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "string"

// Definition of Resources path based on OS.
#ifdef __APPLE__
#define resourcesPath "/Users/Albert/objectFiles/"    // Temporary Mac position.
#else
#define resourcesPath "C:\\Program Files \(x86\)\\amethyst_engine\\Resources\\"   // Hopefully permanent Windows position.
#endif

#define solid 24

using namespace std;

struct wcPt3d{
    /// 3d coordinate representation
    GLfloat x,y,z;
};

class model{
    class verTexture{
        /// Internal texture class
    public:
        GLfloat x,y;
        verTexture(){
        x = 0;
        y = 0;
        }
    };
    class face{
        /// Internal normal class
    public:
        GLfloat xv, xvt, yv, yvt, zv, zvt;
        char discard;

        face(){
        xv = 0;
        xvt = 0;
        yv = 1;
        yvt = 1;
        zv = 2;
        zvt = 2;
        }
    };

private:
    vector<wcPt3d> vertices;                // Vertexes of the Object.
    vector<verTexture> verTextures;         // Texture cords of the object.
    vector<face> faces;                     // Linking information on what vertexes make up which polygons.
    wcPt3d location;                        // Location of object.
    wcPt3d rotation;                        // Rotation of object.

public:
    GLint polymode;                         // Tells GLUT how to render the object ex. GL_LINE, GL_FILL being wire-frame or solid respectively.
    string filename;                        // Name of file to load model from.
    int id;                                 // Internal id of model
    //string objpath;                       // The path is now defined based on OS in the beginning of this file.

    // Functions
public:
    void readObjFile();                             // Load vertices, vertextures and faces from obj file.
    void objDraw();                                 // Function to add object to the overall scene.

    void translatef(float x, float y, float z);     // Move object from current position by x, y, z.
    void rotatef(float x, float y, float z);        // Rotate object from current rotation by x, y, z.
    void set_location(float x, float y, float z);   // Move object to the given x, y, z coordinates.
    void reset_rotation();                          // Reset rotation to default.

    // Accessors
    int get_verts();                                // Return the number of vertices in the object.
    int get_faces();                                // Return the number of polygons in the object.
    wcPt3d get_location();                          // Return a array of the object's x,y,z coordinates.
    wcPt3d get_rotation();                          // Return a array of the object's x,y,z rotation.

    // Constructor
    model(string file_name){
        filename = file_name;
        polymode = GL_FILL;
        id = 0;

        readObjFile();
    };
    model(string file_name, int model_id){
        filename = file_name;
        polymode = GL_FILL;
        id = model_id;

        readObjFile();
    };
};

#endif // OBJ_MODEL_H_INCLUDED
