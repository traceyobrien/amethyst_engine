//
//  Keyboard.cpp
//  amethyst_engine
//
//  Created by Tracey O'Brien on 6/11/17.
//  Copyright � 2017 Tracey O'Brien. All rights reserved.
//

#include "keyboard.h"
#include <iostream>

void nullcharacter(){/*null function for return if character is not assigned*/};

func keyboard_handler::keyInput(unsigned char key, int x, int y){
	//cout << key << " was pressed" << endl;					// Debugging
	string keyname = keybindings[tolower(key)];
	if (keyname.empty()){
		return nullcharacter;
	}
	else{
		return keyfuncs[keyname];
	};
};

void keyboard_handler::addKey(string keyName, char key, func keyFunction){
    /// Add a key and it's function to the handler.
    keybindings[key] = keyName;
    keyfuncs[keyName] = keyFunction;
};

void keyboard_handler::removeKey(string keyName){
    /// Remove a key and it's function from the handler.
	for (std::map<char,string>::iterator item=keybindings.begin(); item!=keybindings.end(); ++item){
		if (item->second == keyName){
			keybindings.erase(item);
		}
	}
    keyfuncs.erase(keyName);
};

void keyboard_handler::updateKey(string keyName, char key){
    /// Change the key associated with a function
    keybindings[key] = keyName;
};

void keyboard_handler::clear(){
	/// Clear all keybindings in the handler
	keybindings.clear();
	keyfuncs.clear();
}
