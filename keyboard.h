//
//  Keyboard.h
//  amethyst_engine
//
//  Created by Tracey O'Brien on 6/11/17.
//  Copyright � 2017 Tracey O'Brien. All rights reserved.
//

#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "string"
#include <map>
#include <iostream>

using namespace std;

typedef void (*func)(void);

class keyboard_handler{
	// Map of keys to their function
    std::map<char, string> keybindings;
    std::map<string, func> keyfuncs;

public:
    func keyInput(unsigned char key, int x, int y);             // Function to pass to glut
    void addKey(string keyName, char key, func kFunc);			// Add a key and it's function to the handler
    void removeKey(string keyName);								// Remove a key and it's function from the handler
    void updateKey(string keyName, char key);					// Change the key associated with a function
	void clear();												// Clear all keybindings in the handler

public:
    keyboard_handler(){                                         // Initializes the keyboard bindings.

	};
};

#endif // KEYBOARD_H_INCLUDED
