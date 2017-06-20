//
//  engine_keys.h
//  amethyst_engine
//
//  Created by Albert Bode on 6/11/17.
//  Copyright � 2017 Albert Bode. All rights reserved.
//

#ifndef engine_keys_h
#define engine_keys_h

#include <iostream>
#include "obj_model.h"
#include "keyboard.h"

using namespace std;

extern std::vector<model_instance*> objects;
extern model_instance *active;
extern keyboard_handler k;

void reset_function(){
	// Reset all location and rotation information
	active->set_location(0.0f, 0.0f, 0.0f);
	active->reset_rotation();
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->set_location(0.0f,0.0f,0.0f);
//		objects[i]->reset_rotation();
//	}
}

void forward_function(){
	// Move all objects 1.0 in z-axis
	active->translatef(0.0f, 0.0f, 1.0f);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->translatef(0.0,0.0,1.0);
//		//float *location = objects[i].get_location();
//		//cout << location[0] << location[1] << location[2] << endl;
//	}
}

void backward_function(){
	// Move all objects -1.0 in z-axis
	active->translatef(0.0f, 0.0f, -1.0f);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->translatef(0.0,0.0,-1.0);
//		//float *location = objects[i].get_location();
//		//cout << location[0] << location[1] << location[2] << endl;
//	}
}

void up_function(){
	// Move all objects 1.0 in y-axis
	active->translatef(0.0f, 1.0f, 0.0);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->translatef(0.0,1.0,0.0);
//		//float *location = objects[i].get_location();
//		//cout << location[0] << location[1] << location[2] << endl;
//	}
}
void down_function(){
	// Move all objects -1.0 in y-axis
	active->translatef(0.0f, -1.0f, 0.0f);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->translatef(0.0,-1.0,0.0);
//		//float *location = objects[i].get_location();
//		//cout << location[0] << location[1] << location[2] << endl;
//	}
}
void left_function(){
	// Move all objects -1.0 in x-axis
	active->translatef(-1.0f, 0.0f, 0.0f);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->translatef(-1.0,0.0,0.0);
//		//float *location = objects[i].get_location();
//		//cout << location[0] << location[1] << location[2] << endl;
//	}
}

void right_function(){
	// Move all objects 1.0 in x-axis
	active->translatef(1.0f, 0.0f, 0.0f);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->translatef(1.0,0.0,0.0);
//		//float *location = objects[i].get_location();
//		//cout << location[0] << location[1] << location[2] << endl;
//	}
}

void animation_function(){
	// Start Rotation animation.
	active->rotatef(2.0f, 0.0f, 0.0f);
//	for (int i=0; i < objects.size(); i++){
//		objects[i]->rotatef(2.0f,0.0f,0.0f);
//	}
}

void rotate_function(){
	glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
}

void debuglocations(){
    wcPt3d location;
    wcPt3d rotation;
    string name;
    for (std::vector<model_instance*>::iterator item = objects.begin(); item != objects.end(); item++){
        location = (*item)->get_location();
        rotation = (*item)->get_rotation();
        name = (*item)->object_name;
        cout << name << "\n\tLocation: " << location.x << ", " << location.y << ", " << location.z << endl;
        cout << "\tRotation: " << rotation.x << ", " << rotation.y << ", " << rotation.z << endl;
    }
}

void quit_function(){
	// Quit program
	exit(0);
}

void init_engine_keys(){
	k.addKey("resetKey", 'r', reset_function);
	k.addKey("moveForward", 'x', forward_function);
	k.addKey("moveBackward", 'z', backward_function);
	k.addKey("moveDown", 's', down_function);
	k.addKey("moveLeft", 'a', left_function);
	k.addKey("moveUp", 'w', up_function);
	k.addKey("moveRight", 'd', right_function);
	k.addKey("play", 'p', animation_function);
	k.addKey("rotate", 'j', rotate_function);
	k.addKey("debug",'h', debuglocations);
	k.addKey("quit", 'q', quit_function);
}



#endif /* engine_keys_h */
