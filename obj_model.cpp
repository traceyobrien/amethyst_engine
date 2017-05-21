#include "obj_model.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void model::readObjFile(){
    fstream in;

    cout << objfile.c_str();
    in.open( objfile.c_str(), ios::in );

    // Temporary variables for parsing file
    string testtype;
    vertex temp_vertex;
    verTexture temp_verTexture;
    face temp_face;

    while ( in.eof() == false ){
        // NEEDS SOME SORT OF ERROR CHECKING
        in >> testtype;

        if (testtype == "v"){
            in >> temp_vertex.x;
            in >> temp_vertex.y;
            in >> temp_vertex.z;
            vertexs.push_back( temp_vertex );
        }
        else if (testtype == "vt"){
            in >> temp_verTexture.x;
            in >> temp_verTexture.y;
            verTextures.push_back( temp_verTexture );
        }
        else if (testtype == "f"){
            in >> temp_face.xv;
            temp_face.xv--;
            in >> temp_face.discard;
            in >> temp_face.xvt;

            in >> temp_face.yv;
            temp_face.yv--;
            in >> temp_face.discard;
            in >> temp_face.yvt;

            in >> temp_face.zv;
            temp_face.zv--;
            in >> temp_face.discard;
            in >> temp_face.zvt;
            faces.push_back( temp_face );
        }
    }

    // Close the file
    in.close();
}

void model::objDraw(){

    glLoadName(solid);

    glColor3f(1.0,1.0,1.0);
    glPolygonMode(GL_FRONT_AND_BACK, polymode);

    glBegin(GL_TRIANGLES);
    for (int i=0; i< faces.size();i++){
        // Computation of normal for the triangle
        float qx = vertexs[faces[i].yv].x - vertexs[faces[i].xv].x;
        float qy = vertexs[faces[i].yv].y - vertexs[faces[i].xv].y;
        float qz = vertexs[faces[i].yv].z - vertexs[faces[i].xv].z;
        float px = vertexs[faces[i].zv].x - vertexs[faces[i].xv].x;
        float py = vertexs[faces[i].zv].y - vertexs[faces[i].xv].y;
        float pz = vertexs[faces[i].zv].z - vertexs[faces[i].xv].z;
        float xnorm = -( py*qz - pz*qy );
        float ynorm = -( pz*qx - px*qz );
        float znorm = -( px*qy - py*qx );

        float len = 1.0/sqrt( xnorm*xnorm + ynorm*ynorm + znorm*znorm);
        xnorm *= len;
        ynorm *= len;
        znorm *= len;

        glNormal3f(xnorm, ynorm, znorm);
        glVertex3f(vertexs[faces[i].xv].x, vertexs[faces[i].xv].y, vertexs[faces[i].xv].z);
        glVertex3f(vertexs[faces[i].yv].x, vertexs[faces[i].yv].y, vertexs[faces[i].yv].z);
        glVertex3f(vertexs[faces[i].zv].x, vertexs[faces[i].zv].y, vertexs[faces[i].zv].z);
    }
    glEnd();
}
