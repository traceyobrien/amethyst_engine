//
//  obj_model.cpp
//  amethyst_engine
//
//  Created by Albert Bode on 5/21/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
//

#include "obj_model.h"

using namespace std;

void model::readObjFile(){
    /// Load vertices, vertextures and faces from obj file.
    fstream in;

    string filelocation = resourcesPath + filename;
    in.open( filelocation.c_str(), ios::in );
    if(!in.is_open()){
        cout << " Cannot open file: " + filename << endl;
    }

    // Temporary variables for parsing file
    string testtype;
    wcPt3d temp_vertex;
    verTexture temp_verTexture;
    face temp_face;

    while ( in.eof() == false ){
        // NEEDS SOME SORT OF ERROR CHECKING
        in >> testtype;

        if (testtype == "v"){
            in >> temp_vertex.x;
            in >> temp_vertex.y;
            in >> temp_vertex.z;
            vertices.push_back( temp_vertex );
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

    // set center of object
    location.x = 0;
    location.y = 0;
    location.z = 0;

    // Close the file
    in.close();
}

void model::objDraw(){
    /// Function to add object to the overall scene.
    // Set unique name so that it can be selected.
    glLoadName(solid);

    // Beginning of object
    glPushMatrix();
        // Rotation offset from default.
        glRotatef(rotation.x, location.x, location.y, location.z);
        glRotatef(rotation.y, location.x, location.y, location.z);
        glRotatef(rotation.z, location.x, location.y, location.z);

        // Set color of object
        glColor3f(1.0f,1.0f,1.0f);
        // Set draw mode of object (wire-frame, solid, points)
        glPolygonMode(GL_FRONT_AND_BACK, polymode);

        // Add polygons
        glBegin(GL_TRIANGLES);
        for (int i=0; i< faces.size();i++){
            // Computation of normal for the triangle
            float qx = vertices[faces[i].yv].x - vertices[faces[i].xv].x;
            float qy = vertices[faces[i].yv].y - vertices[faces[i].xv].y;
            float qz = vertices[faces[i].yv].z - vertices[faces[i].xv].z;
            float px = vertices[faces[i].zv].x - vertices[faces[i].xv].x;
            float py = vertices[faces[i].zv].y - vertices[faces[i].xv].y;
            float pz = vertices[faces[i].zv].z - vertices[faces[i].xv].z;
            float xnorm = -( py*qz - pz*qy );
            float ynorm = -( pz*qx - px*qz );
            float znorm = -( px*qy - py*qx );

            float len = 1.0/sqrt( xnorm*xnorm + ynorm*ynorm + znorm*znorm);
            xnorm *= len;
            ynorm *= len;
            znorm *= len;

            // Draw vertices of Triangle and normal.
            glNormal3f(xnorm, ynorm, znorm);
            glVertex3f(location.x + vertices[faces[i].xv].x, location.y + vertices[faces[i].xv].y, location.z + vertices[faces[i].xv].z);
            glVertex3f(location.x + vertices[faces[i].yv].x, location.y + vertices[faces[i].yv].y, location.z + vertices[faces[i].yv].z);
            glVertex3f(location.x + vertices[faces[i].zv].x, location.y + vertices[faces[i].zv].y, location.z + vertices[faces[i].zv].z);
        }
        glEnd();
    glPopMatrix();
}

void model::translatef(float x, float y, float z){
    /// Move object from current position by x, y, z.
    location.x += x;
    location.y += y;
    location.z += z;
};

void model::rotatef(float x, float y, float z){
    /// Rotate object from current rotation by x, y, z.
    rotation.x += x;
    rotation.y += y;
    rotation.z += z;
    if (rotation.x > 360){
        rotation.x -= 360;
    }
    if (rotation.x < 0){
        rotation.x += 360;
    }
    if (rotation.y > 360){
        rotation.y -= 360;
    }
    if (rotation.y < 0){
        rotation.y += 360;
    }
    if (rotation.z > 360){
        rotation.z -= 360;
    }
    if (rotation.z < 0){
        rotation.z += 360;
    }
};

void model::set_location(float x, float y, float z){
    /// Move object to the given x, y, z coordinates.
    location.x = x;
    location.y = y;
    location.z = z;
};

void model::reset_rotation(){
    /// Reset rotation to default.
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
};

int model::get_verts(){
    /// Return the number of vertices in the object.
    return vertices.size();
};
int model::get_faces(){
    /// Return the number of polygons in the object.
    return faces.size();
};

wcPt3d model::get_location(){
    /// Return a array of the object's x,y,z coordinates.
    return location;
};

wcPt3d model::get_rotation(){
    /// Return a array of the object's x,y,z rotation.
    return rotation;
};
