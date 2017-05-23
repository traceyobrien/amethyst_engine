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
    // Variables
    vector<vertex> vertices;
    vector<verTexture> verTextures;
    vector<face> faces;
public:
    vertex location;
    bool animation;
    int polymode;
    string objfile;
    float spin;
public:
    // Functions
    void readObjFile();
    void objDraw();

    model(string filename){
        objfile = filename;
        polymode = GL_LINE;
        spin = 0.0;
        animation = false;

        readObjFile();
    }
};

#endif // OBJ_MODEL_H_INCLUDED
