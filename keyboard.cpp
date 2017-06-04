#include "keyboard.h"
#include <iostream>

func keyboard_handler::keyInput(unsigned char key, int x, int y){
    for (std::map<string, char>::iterator iter=keybindings.begin(); iter!=keybindings.end(); ++iter){
        if (iter->second == key){
            return keyfuncs[iter->first];
        }
    }
};
/*
void keyboard_handler::keyInput(unsigned char key, int x, int y)
{
    if(key == keybindings.at("resetKey")){
        // Reset all location and rotation information
        for (int i=0; i < objects.size(); i++){
            objects[i].set_location(0.0,0.0,0.0);
            objects[i].reset_rotation();
        }
    }
    if(key == keybindings.at("moveForward")){
        // Move all objects 1.0 in z-axis
        for (int i=0; i < objects.size(); i++){
            objects[i].translatef(0.0,0.0,1.0);
            cout << "i got to this point" << endl;
            //float *location = objects[i].get_location();
            //cout << location[0] << location[1] << location[2] << endl;
        }
    }
    if(key == keybindings.at("moveBackward")){
        // Move all objects -1.0 in z-axis
        for (int i=0; i < objects.size(); i++){
            objects[i].translatef(0.0,0.0,-1.0);
            //float *location = objects[i].get_location();
            //cout << location[0] << location[1] << location[2] << endl;
        }
    }
    if(key == keybindings.at("moveUp")){
        // Move all objects 1.0 in y-axis
        for (int i=0; i < objects.size(); i++){
            objects[i].translatef(0.0,1.0,0.0);
            //float *location = objects[i].get_location();
            //cout << location[0] << location[1] << location[2] << endl;
        }
    }
    if(key == keybindings.at("moveDown")){
        // Move all objects -1.0 in y-axis
        for (int i=0; i < objects.size(); i++){
            objects[i].translatef(0.0,-1.0,0.0);
            //float *location = objects[i].get_location();
            //cout << location[0] << location[1] << location[2] << endl;
        }
    }
    if(key == keybindings.at("moveLeft")){
        // Move all objects -1.0 in x-axis
        for (int i=0; i < objects.size(); i++){
            objects[i].translatef(-1.0,0.0,0.0);
            //float *location = objects[i].get_location();
            //cout << location[0] << location[1] << location[2] << endl;
        }
    }
    if(key == keybindings.at("moveRight")){
        // Move all objects 1.0 in x-axis
        for (int i=0; i < objects.size(); i++){
            objects[i].translatef(1.0,0.0,0.0);
            //float *location = objects[i].get_location();
            //cout << location[0] << location[1] << location[2] << endl;
        }
    }
    if(key == keybindings.at("play")){
        // Start Rotation animation.
        for (int i=0; i < objects.size(); i++){
            objects[i].animation = !objects[i].animation;
        }
    }
    if(key == keybindings.at("quit")){
        // Quit program
        exit(0);
    }

    glutPostRedisplay();                                        // Tells display to redraw/update display
}
*/
void keyboard_handler::addKey(string keyName, char key, func kFunc){
    /// Add a key to the keybindings.
    keybindings[keyName] = key;
    keyfuncs[keyName] = kFunc;
}

void keyboard_handler::removeKey(string keyName){
    /// Remove key from keybindings.
    keybindings.erase(keyName);
    keyfuncs.erase(keyName);
};

void keyboard_handler::updateKey(string keyName, char key){
    /// Change the key associated with a binding.
    keybindings[keyName] = key;
};
