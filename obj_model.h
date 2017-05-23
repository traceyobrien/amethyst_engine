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
    int polymode;                           // Tells GLUT how to render the object ex. GL_LINE, GL_FILL being wire frame or solid respectively.
    string objfile;                         // Name of object file to load from.
    string objpath;                         // Path in which the Object resources are stored.

    // Functions
public:
    void readObjFile();
    void objDraw();

    void translatef(float x, float y, float z);
    void rotatef(float x, float y, float z);
    void set_location(float x, float y, float z);
    void reset_rotation();

    // Accessors
    int get_verts();
    int get_faces();
    float* get_location();
    float* get_rotation();

    // Constructor
    model(string filename){
        objfile = filename;
        objpath = "C:\\Program Files \(x86\)\\amethyst_engine\\Resources\\";
        polymode = GL_LINE;
        animation = false;

        readObjFile();
    }
};

#endif // OBJ_MODEL_H_INCLUDED
