//
//  engine_keys.h
//  amethyst_engine
//
//  Created by Albert Bode on 6/11/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
//

#ifndef engine_keys_h
#define engine_keys_h

#include <iostream>
#include "obj_model.h"
#include "keyboard.h"

using namespace std;

extern vector<model> objects;
extern keyboard_handler k;

void reset_function(){
	// Reset all location and rotation information
	for (int i=0; i < objects.size(); i++){
		objects[i].set_location(0.0,0.0,0.0);
		objects[i].reset_rotation();
	}
}

void forward_function(){
	// Move all objects 1.0 in z-axis
	for (int i=0; i < objects.size(); i++){
		objects[i].translatef(0.0,0.0,1.0);
		//cout << "i got to this point" << endl;
		//float *location = objects[i].get_location();
		//cout << location[0] << location[1] << location[2] << endl;
	}
}

void backward_function(){
	// Move all objects -1.0 in z-axis
	for (int i=0; i < objects.size(); i++){
		objects[i].translatef(0.0,0.0,-1.0);
		//float *location = objects[i].get_location();
		//cout << location[0] << location[1] << location[2] << endl;
	}
}

void up_function(){
	// Move all objects 1.0 in y-axis
	for (int i=0; i < objects.size(); i++){
		objects[i].translatef(0.0,1.0,0.0);
		//float *location = objects[i].get_location();
		//cout << location[0] << location[1] << location[2] << endl;
	}
}
void down_function(){
	// Move all objects -1.0 in y-axis
	for (int i=0; i < objects.size(); i++){
		objects[i].translatef(0.0,-1.0,0.0);
		//float *location = objects[i].get_location();
		//cout << location[0] << location[1] << location[2] << endl;
	}
}
void left_function(){
	// Move all objects -1.0 in x-axis
	for (int i=0; i < objects.size(); i++){
		objects[i].translatef(-1.0,0.0,0.0);
		//float *location = objects[i].get_location();
		//cout << location[0] << location[1] << location[2] << endl;
	}
}

void right_function(){
	// Move all objects 1.0 in x-axis
	for (int i=0; i < objects.size(); i++){
		objects[i].translatef(1.0,0.0,0.0);
		//float *location = objects[i].get_location();
		//cout << location[0] << location[1] << location[2] << endl;
	}
}

void animation_function(){
	// Start Rotation animation.
	for (int i=0; i < objects.size(); i++){
		objects[i].rotatef(2.0f,0.0f,0.0f);
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
	k.addKey("quit", 'q', quit_function);
}


#endif /* engine_keys_h */
