//
//  obj_model.cpp
//  amethyst_engine
//
//  Created by Albert Bode on 5/21/17.
//  Copyright � 2017 Albert Bode. All rights reserved.
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

    // Close the file
    in.close();
}

void model::objDraw(wcPt3d location, wcPt3d rotation, unsigned int model_instance_id){
    /// Function to add object to the overall scene.
    // Set unique name so that it can be selected.
    glLoadName(model_instance_id);

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
        for (unsigned int i=0; i< faces.size();i++){
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

void model_instance::objDraw(){
    if(!q.empty()){
        wcPt3d movement_xyz;
        movement_xyz = q.front();
        //cout << "location before pop: " << movement_xyz.x << ", " << movement_xyz.y << ", " << movement_xyz.z << endl;
        q.pop();
        //cout << "location after pop: " << movement_xyz.x << ", " << movement_xyz.y << ", " << movement_xyz.z << endl;
        this->translatef(movement_xyz.x,movement_xyz.y,movement_xyz.z);
    }
	object_model->objDraw(location, rotation, model_instance_id);
}

int model::get_next_id(){
    return object_id++;
};

int model::get_model_id(){
    return model_id;
};

string model::get_model_name(){
    return model_name;
};

int model::get_verts(){
	/// Return the number of vertices in the object.
	return vertices.size();
};
int model::get_faces(){
	/// Return the number of polygons in the object.
	return faces.size();
};

void model_instance::translatef(float x, float y, float z){
    /// Move object from current position by x, y, z.
    location.x += x;
    location.y += y;
    location.z += z;
};

void model_instance::rotatef(float x, float y, float z){
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

void model_instance::set_location(float x, float y, float z){
    /// Move object to the given x, y, z coordinates.
    location.x = x;
    location.y = y;
    location.z = z;
};

void model_instance::reset_rotation(){
    /// Reset rotation to default.
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
};

wcPt3d model_instance::get_location(){
    /// Return a array of the object's x,y,z coordinates.
    return location;
};

wcPt3d model_instance::get_rotation(){
    /// Return a array of the object's x,y,z rotation.
    return rotation;
};

void model_instance::move_to_point(float x, float y, float z){
    const float max_movement = 0.3f;
    wcPt3d movement_left;
    wcPt3d movement_xyz;

    movement_left.x = x - location.x;
    movement_left.y = y - location.y;
    movement_left.z = z - location.z;

    cout << "movement begins" << endl;
    while(movement_left.x != 0 || movement_left.y != 0 || movement_left.z != 0){
        // X movement
        if (movement_left.x > 0 && movement_left.x > max_movement){
            movement_xyz.x = max_movement;
            movement_left.x -= max_movement;
        }
        else if (movement_left.x < 0 && movement_left.x < -(max_movement)){
            movement_xyz.x = -(max_movement);
            movement_left.x += max_movement;
        }
        else {
            movement_xyz.x = movement_left.x;
            movement_left.x = 0;
        }
        // Y movement
        if (movement_left.y > 0 && movement_left.y > max_movement){
            movement_xyz.y = max_movement;
            movement_left.y -= max_movement;
        }
        else if (movement_left.y < 0 && movement_left.y < -(max_movement)){
            movement_xyz.y = -(max_movement);
            movement_left.y += max_movement;
        }
        else {
            movement_xyz.y = movement_left.y;
            movement_left.y = 0;
        }
        // Z movement
        if (movement_left.z > 0 && movement_left.z > max_movement){
            movement_xyz.z = max_movement;
            movement_left.z -= max_movement;
        }
        else if (movement_left.z < 0 && movement_left.z < -(max_movement)){
            movement_xyz.z = -(max_movement);
            movement_left.z += max_movement;
        }
        else {
            movement_xyz.z = movement_left.z;
            movement_left.z = 0;
        }
        cout << "location: " << movement_xyz.x << ", " << movement_xyz.y << ", " << movement_xyz.z << endl;
        q.push(movement_xyz);
    }
    cout << "movement ends" << endl;
}

void model_instance::empty_queue(){
    if(!q.empty()){
        for(int i = 0; i < q.size(); i++){
            q.pop();
        }
    }
}
