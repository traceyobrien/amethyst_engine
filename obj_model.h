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

#include <queue>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>

// Definition of Resources path based on OS.
#ifdef __APPLE__
#define resourcesPath "/Users/Albert/objectFiles/"    // Temporary Mac position.
#else
#define resourcesPath "C:\\Program Files \(x86\)\\amethyst_engine\\Resources\\"   // Hopefully permanent Windows position.
#endif

#include "rendering_utils.h"

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
    color *model_color;

public:
    GLint polymode;                         // Tells GLUT how to render the object ex. GL_LINE, GL_FILL being wire-frame or solid respectively.
    string filename;                        // Name of file to load model from.
    string model_name;                      // Name of model which maps to the id.
    int model_id;                           // Id which maps to the name of the model
    int object_id;                          // Id counter for model_instances of this object.
    //string objpath;                       // The path is now defined based on OS in the beginning of this file.

    // Functions
public:
    void readObjFile();                             // Load vertices, vertextures and faces from obj file.
    void objDraw(wcPt3d location, wcPt3d rotation, unsigned int model_instance_id); // Function to add model to the overall scene.

    // Accessors
    int get_verts();                        // Return the number of vertices in the object.
    int get_faces();                        // Return the number of polygons in the object.
    int get_next_id();                      // Return the next available instance_id of this object
    int get_model_id();                     // Return the id of this model
    string get_model_name();                // Return the name of this model

    // Constructor
    model(string filename, int model_id){
        this->filename = filename;
        this->model_id = model_id;
        this->model_name = filename.substr(0, filename.find_last_of("."));
        this->model_color = new color("firebrick",1.0f);
        object_id = 1;
		polymode = GL_FILL;

        readObjFile();
    };
    model(string filename, int model_id, string model_name){
        this->filename = filename;
        this->model_name = model_name;
        this->model_id = model_id;
        this->model_color = new color("grey",1.0f);
        object_id = 1;
		polymode = GL_FILL;

        readObjFile();
    };

    ~model(){
        delete model_color;
    }
};

extern std::map<string,model*> models;

class model_instance{
protected:
	wcPt3d location;                        // Location of object.
	wcPt3d rotation;                        // Rotation of object.

public:
	model *object_model;					// Pointer to actual model.
	int model_id;							// Id of model to load.
	string object_name;						// Name of object
	unsigned int model_instance_id;			// temp name id for glut
	std::queue<wcPt3d> q;

	// Functions
	void objDraw();
	void translatef(float x, float y, float z);     // Move object from current position by x, y, z.
	void rotatef(float x, float y, float z);        // Rotate object from current rotation by x, y, z.
	void set_location(float x, float y, float z);   // Move object to the given x, y, z coordinates.
	void reset_rotation();                          // Reset rotation to default.
	void move_to_point(float x, float y, float z);
	void empty_queue();

	// Accessors
	wcPt3d get_location();                          // Return a array of the object's x,y,z coordinates.
	wcPt3d get_rotation();                          // Return a array of the object's x,y,z rotation.

	// Constructor
	model_instance(string model_name){
		this->object_model = models[model_name];
		this->model_id = object_model->get_model_id();
		stringstream sstmp;
		this->model_instance_id = object_model->get_next_id();
		sstmp << model_name << model_instance_id;
		this->object_name = sstmp.str();

		location.x = 0;
		location.y = 0;
        location.z = 0;

        rotation.x = 0;
        rotation.y = 0;
        rotation.z = 0;
    };
//	model_instance(int model_id){
//      this->model_id = model_id;
//      this->object_model = model_loc[model_id];
//
//      this->object_name = object_model->get_model_name() + object_model->getNextId();
//	};
};



#endif // OBJ_MODEL_H_INCLUDED
