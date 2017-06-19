//
//  FpsTimer.h
//  amethyst_engine
//
//  Created by Albert Bode on 5/21/17.
//  Copyright � 2017 Albert Bode. All rights reserved.
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
#include <map>
#include <iostream>
#include <fstream>
#include <math.h>
#include "string"

#include "game_rendering.h"

// Definition of Resources path based on OS.
#ifdef __APPLE__
#define resourcesPath "/Users/Albert/objectFiles/"    // Temporary Mac position.
#else
#define resourcesPath "C:\\Program Files \(x86\)\\amethyst_engine\\Resources\\"   // Hopefully permanent Windows position.
#endif

using namespace std;

struct wcPt3d{
    /// 3d coordinate representation
    GLfloat x,y,z;
};

class model{
    struct verTexture{
        /// Internal texture class
        GLfloat x,y;
		
        verTexture(){
        x = 0;
        y = 0;
        }
    };
    struct face{
        /// Internal normal class
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

public:
    GLint polymode;                         // Tells GLUT how to render the object ex. GL_LINE, GL_FILL being wire-frame or solid respectively.
    string filename;                        // Name of file to load model from.
    int model_id;                           // Internal id of model
    //string objpath;                       // The path is now defined based on OS in the beginning of this file.

    // Functions
public:
    void readObjFile();                             // Load vertices, vertextures and faces from obj file.
    void objDraw(wcPt3d location, wcPt3d rotation); // Function to add model to the overall scene.

    // Accessors
    int get_verts();                                // Return the number of vertices in the object.
    int get_faces();                                // Return the number of polygons in the object.

    // Constructor
    model(string filename){
        this->filename = filename;
        this->model_id = 0;
		polymode = GL_FILL;
		
        readObjFile();
    };
    model(string filename, int model_id){
        this->filename = filename;
        this->model_id = model_id;
		polymode = GL_FILL;
		
        readObjFile();
    };
};

extern std::map<string,model*> models;

class model_instance{
private:
	wcPt3d location;                        // Location of object.
	wcPt3d rotation;                        // Rotation of object.
	
public:
	model *object_model;					// Pointer to actual model.
	int model_id;							// Id of model to load.
	string object_name;						// Name of object
	
	// Functions
	void objDraw();
	void translatef(float x, float y, float z);     // Move object from current position by x, y, z.
	void rotatef(float x, float y, float z);        // Rotate object from current rotation by x, y, z.
	void set_location(float x, float y, float z);   // Move object to the given x, y, z coordinates.
	void reset_rotation();                          // Reset rotation to default.
	
	// Accessors
	wcPt3d get_location();                          // Return a array of the object's x,y,z coordinates.
	wcPt3d get_rotation();                          // Return a array of the object's x,y,z rotation.
	
	// Constructor
	model_instance(string model_name){
		this->object_name = model_name;
		object_model = models[model_name];
	}
};



#endif // OBJ_MODEL_H_INCLUDED
