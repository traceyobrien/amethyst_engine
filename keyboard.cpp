#include "keyboard.h"
#include <iostream>

void nullcharacter(){/*null function for return if character is not assigned*/};

func keyboard_handler::keyInput(unsigned char key, int x, int y){
	//cout << key << " was pressed" << endl;
	string keyname = keybindings[key];
	if (keyname.empty()){
		//cout << "No function for this key" << endl;
		return nullcharacter;
	}
	else{
		//cout << "Corresponds to "  << keyname << endl;
		return keyfuncs[keyname];		
	};
};

void keyboard_handler::addKey(string keyName, char key, func keyFunction){
    /// Add a key to the keybindings.
	// Needs check for if this will overwrite a key
    keybindings[key] = keyName;
    keyfuncs[keyName] = keyFunction;
};

void keyboard_handler::removeKey(string keyName){
    /// Remove key from keybindings.
//	for (item in keybindings.iterkeys()){
//		if (keybindings[item] == keyName){
//			keybindings.erase(item);
//		}
//	}
//    keyfuncs.erase(keyName);
};

void keyboard_handler::updateKey(string keyName, char key){
    /// Change the key associated with a binding.
	// Needs check for if this will overwrite a key
    keybindings[key] = keyName;
};

void keyboard_handler::clear(){
	/// Erase all keybindings.
};
