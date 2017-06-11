#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "string"
#include <map>
#include <iostream>

using namespace std;

typedef void (*func)(void);

class keyboard_handler{

    std::map<char, string> keybindings;
    std::map<string, func> keyfuncs;

public:
    func keyInput(unsigned char key, int x, int y);             // Function to pass to glut
    void addKey(string keyName, char key, func kFunc);
    void removeKey(string keyName);
    void updateKey(string keyName, char key);
	void clear();

public:
    keyboard_handler(){                                         // Initializes the keyboard bindings.

	};
};

#endif // KEYBOARD_H_INCLUDED
