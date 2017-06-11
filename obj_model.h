/*
* obj_model.h
* Amethyst_engine
*
* Created by Albert Bode on 5/21/2017
*/

#ifndef OBJ_MODEL_H_INCLUDED
#define OBJ_MODEL_H_INCLUDED

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<vector>
#include"string"

#define solid 24

using namespace std;

class model{
    /// class for holding 3D models to be rendered by glut
    class vertex{
        /// Internal vertex class
    public:
        float x,y,z;
        vertex(){
        x = 0;
        y = 0;
        z = 0;
        }
    };
    class verTexture{
        /// Internal texture class
    public:
        float x,y;
        verTexture(){
        x = 0;
        y = 0;
        }
    };
    class face{
        /// Internal normal class
    public:
        float xv, xvt, yv, yvt, zv, zvt;
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
    vector<vertex> vertices;                // Vertexes of the Object.
    vector<verTexture> verTextures;         // Texture cords of the object.
    vector<face> faces;                     // Linking information on what vertexes make up which polygons.
    vertex location;                        // Overall location of object as a whole.
    vertex rotation;                        // Rotation attributes of object.

public:
    bool animation;                         // True for animation on, False for not.
    int polymode;                           // Tells GLUT how to render the object ex. GL_LINE, GL_FILL being wire-frame or solid respectively.
    string objfile;                         // Name of obj file to load from.
    string objpath;                         // Path in which the Object resources are stored. This should be changed to a static variable somewhere else eventually

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
    float* get_location();                          // Return a array of the object's x,y,z coordinates.
    float* get_rotation();                          // Return a array of the object's x,y,z rotation.

    // Constructor
    model(string filename){
        objfile = filename;
        objpath = "C:\\Program Files \(x86\)\\amethyst_engine\\Resources\\";	// Windows path
		//objpath = "/Users/Albert/objectFiles/";									// Tempory Mac path will be fixed evenutly
        polymode = GL_LINE;
        animation = false;

        readObjFile();
    }
};

#endif // OBJ_MODEL_H_INCLUDED
