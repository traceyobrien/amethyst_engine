#ifndef RENDERING_UTILS_H_INCLUDED
#define RENDERING_UTILS_H_INCLUDED

#include <sstream>
#include <string>
#include <iostream>

using namespace std;

struct color{
    // RGBA component
    float red;          // Value between 0.0f and 1.0f
    float green;        //
    float blue;         //
    float alpha;        //

    // HSV component
    //float hue;          // Value between 0.0f and 1.0f
    //float saturation;   //
    //float value;        //

    //void RGBtoHSV();    // Update the HSV to reflect the current RGB value
    //void HSVtoRGB();    // Update the RGB to reflect the current HSV value
    string StringtoHEX(string name);
    void HEXtoRGB(string hex);

    color(){
        this->red = 1.0f;
        this->green = 1.0f;
        this->blue = 1.0f;
        this->alpha = 1.0f;
    }
    color(string rgb, float alpha=1.0f){
        HEXtoRGB(StringtoHEX(rgb));
        this->alpha = alpha;
    };
    color(float red, float green, float blue, float alpha=1.0){
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    };
};

#endif // RENDERING_UTILS_H_INCLUDED
