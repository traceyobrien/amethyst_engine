#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

typedef void (*func)(void);

class keyboard_handler {

    std::map<string, char> keybindings;
    std::map<string, func> keyfuncs;

    static void keyInput(unsigned char key, int x, int y);      // Function to pass to glut
    void addKey(string keyName, char key, func kFunc);
    void removeKey(string keyName);
    void updateKey(string keyName, char key);

    keyboard_handler(){                                         // Initializes the keyboard bindings.
        keybindings.insert(std::make_pair("resetKey", 'r'));
        keybindings.insert(std::make_pair("moveForward", 'x'));
        keybindings.insert(std::make_pair("moveBackward", 'z'));
        keybindings.insert(std::make_pair("moveUp", 'w'));
        keybindings.insert(std::make_pair("moveDown", 's'));
        keybindings.insert(std::make_pair("moveLeft", 'a'));
        keybindings.insert(std::make_pair("moveRight", 'd'));
        keybindings.insert(std::make_pair("play", 'p'));
        keybindings.insert(std::make_pair("quit", 'q'));
    };

};

#endif // KEYBOARD_H_INCLUDED
