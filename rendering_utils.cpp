#include "rendering_utils.h"

void color::HEXtoRGB(string hex){
    // make this case independent
    string redstr, greenstr, bluestr;
    std::stringstream redss, greenss, bluess;
    int redval, greenval, blueval;

    redstr = hex.substr(1,2);
    greenstr = hex.substr(3,2);
    bluestr = hex.substr(5,2);

    cout << "red  : " << redstr << endl;
    cout << "green: " << greenstr << endl;
    cout << "blue : " << bluestr << endl;

    redss << std::hex << redstr;
    greenss << std::hex << greenstr;
    bluess << std::hex << bluestr;

    redss >> redval;
    greenss >> greenval;
    bluess >> blueval;

    cout << "RGB : " << redval << ", " << greenval << ", " << blueval << endl;

    this->red = float(redval/256.0f);
    this->green = float(greenval/256.0f);
    this->blue = float(blueval/256.0f);
};

/*
CSS COLOR LIST:
Color Name              HEX
Aliceblue           |   #F0F8FF
Antiquewhite        |   #FAEBD7
Aqua                |   #00FFFF
Aquamarine          |   #7FFFD4
Azure               |   #F0FFFF
Beige               |   #F5F5DC
Bisque              |   #FFE4C4
Black               |   #000000
BlanchedAlmond      |   #FFEBCD
Blue                |   #0000FF
BlueViolet          |   #8A2BE2
Brown               |   #A52A2A
BurlyWood           |   #DEB887
CadetBlue           |   #5F9EA0
Chartreuse          |   #7FFF00
Chocolate           |   #D2691E
Coral               |   #FF7F50
CornflowerBlue      |   #6495ED
Cornsilk            |   #FFF8DC
Crimson             |   #DC143C
Cyan                |   #00FFFF
DarkBlue            |   #00008B
DarkCyan            |   #008B8B
DarkGoldenRod       |   #B8860B
DarkGray            |   #A9A9A9
DarkGrey            |
DarkGreen           |   #006400
DarkKhaki           |   #BDB76B
DarkMagenta         |   #8B008B
DarkOliveGreen      |   #556B2F
DarkOrange          |   #FF8C00
DarkOrchid          |   #9932CC
DarkRed             |   #8B0000
DarkSalmon          |   #E9967A
DarkSeaGreen        |   #8FBC8F
DarkSlateBlue       |   #483D8B
DarkSlateGray       |   #2F4F4F
DarkSlateGrey       |
DarkTurquoise       |   #00CED1
DarkViolet          |   #9400D3
DeepPink            |   #FF1493
DeepSkyBlue         |   #00BFFF
DimGray             |   #696969
DimGrey             |
DodgerBlue          |   #1E90FF
FireBrick           |   #B22222
FloralWhite         |   #FFFAF0
ForestGreen         |   #228B22
Fuchsia             |   #FF00FF
Gainsboro           |   #DCDCDC
GhostWhite          |   #F8F8FF
Gold                |   #FFD700
GoldenRod           |   #DAA520
Gray                |   #808080
Grey                |
Green               |   #008000
GreenYellow         |   #ADFF2F
HoneyDew            |   #F0FFF0
HotPink             |   #FF69B4
IndianRed           |   #CD5C5C
Indigo              |   #4B0082
Ivory               |   #FFFFF0
Khaki               |   #F0E68C
Lavender            |   #E6E6FA
LavenderBlush       |   #FFF0F5
LawnGreen           |   #7CFC00
LemonChiffon        |   #FFFACD
LightBlue           |   #ADD8E6
LightCoral          |   #F08080
LightCyan           |   #E0FFFF
LightGoldenRodYellow|   #FAFAD2
LightGray           |   #D3D3D3
LightGrey           |
LightGreen          |   #90EE90
LightPink           |   #FFB6C1
LightSalmon         |   #FFA07A
LightSeaGreen       |   #20B2AA
LightSkyBlue        |   #87CEFA
LightSlateGray      |   #778899
LightSlateGrey      |
LightSteelBlue      |   #B0C4DE
LightYellow         |   #FFFFE0
Lime                |   #00FF00
LimeGreen           |   #32CD32
Linen               |   #FAF0E6
Magenta             |   #FF00FF
Maroon              |   #800000
MediumAquaMarine    |   #66CDAA
MediumBlue          |   #0000CD
MediumOrchid        |   #BA55D3
MediumPurple        |   #9370DB
MediumSeaGreen      |   #3CB371
MediumSlateBlue     |   #7B68EE
MediumSpringGreen   |   #00FA9A
MediumTurquoise     |   #48D1CC
MediumVioletRed     |   #C71585
MidnightBlue        |   #191970
MintCream           |   #F5FFFA
MistyRose           |   #FFE4E1
Moccasin            |   #FFE4B5
NavajoWhite         |   #FFDEAD
Navy                |   #000080
OldLace             |   #FDF5E6
Olive               |   #808000
OliveDrab           |   #6B8E23
Orange              |   #FFA500
OrangeRed           |   #FF4500
Orchid              |   #DA70D6
PaleGoldenRod       |   #EEE8AA
PaleGreen           |   #98FB98
PaleTurquoise       |   #AFEEEE
PaleVioletRed       |   #DB7093
PapayaWhip          |   #FFEFD5
PeachPuff           |   #FFDAB9
Peru                |   #CD853F
Pink                |   #FFC0CB
Plum                |   #DDA0DD
PowderBlue          |   #B0E0E6
Purple              |   #800080
RebeccaPurple       |   #663399
Red                 |   #FF0000
RosyBrown           |   #BC8F8F
RoyalBlue           |   #4169E1
SaddleBrown         |   #8B4513
Salmon              |   #FA8072
SandyBrown          |   #F4A460
SeaGreen            |   #2E8B57
SeaShell            |   #FFF5EE
Sienna              |   #A0522D
Silver              |   #C0C0C0
SkyBlue             |   #87CEEB
SlateBlue           |   #6A5ACD
SlateGray           |   #708090
SlateGrey           |
Snow                |   #FFFAFA
SpringGreen         |   #00FF7F
SteelBlue           |   #4682B4
Tan                 |   #D2B48C
Teal                |   #008080
Thistle             |   #D8BFD8
Tomato              |   #FF6347
Turquoise           |   #40E0D0
Violet              |   #EE82EE
Wheat               |   #F5DEB3
White               |   #FFFFFF
WhiteSmoke          |   #F5F5F5
Yellow              |   #FFFF00
YellowGreen         |   #9ACD32
*/

string color::StringtoHEX(string name){
    // make this case independent
    //string name = (char*)std::transform(inputname.begin(), inputname.end(), inputname.begin(), ::tolower);
    const char *c = name.c_str();
    string return_hex;
    if(c[0] != '\#'){
        switch(c[0]){
            cout << "Searching css colors" << endl;
        case 'a':
            if(name == "aliceblue"){
                return_hex = "#F0F8FF";
                break;
            }
            if(name == "antiquewhite"){
                return_hex = "#FAEBD7";
                break;
            }
            if(name == "aqua"){
                return_hex = "#00FFFF";
                break;
            }
            if(name == "aquamarine"){
                return_hex = "#7FFFD4";
                break;
            }
            if(name == "azure"){
                return_hex = "#F0FFFF";
                break;
            }
            break;
        case 'b':
            if(name == "beige"){
                return_hex = "#F5F5DC";
                break;
            }
            if(name == "bisque"){
                return_hex = "#FFE4C4";
                break;
            }
            if(name == "black"){
                return_hex = "#000000";
                break;
            }
            if(name == "blanchedalmond"){
                return_hex = "#FFEBCD";
                break;
            }
            if(name == "blue"){
                return_hex = "#0000FF";
                break;
            }
            if(name == "blueviolet"){
                return_hex = "#8A2BE2";
                break;
            }
            if(name == "brown"){
                return_hex = "#A52A2A";
                break;
            }
            if(name == "blue"){
                return_hex = "#DEB887";
                break;
            }
            break;
        case 'c':
            if(name == "cadetblue"){
                return_hex = "#5F9EA0";
                break;
            }
            if(name == "chartreuse"){
                return_hex = "#7FFF00";
                break;
            }
            if(name == "chocolate"){
                return_hex = "#D2691E";
                break;
            }
            if(name == "coral"){
                return_hex = "#FF7F50";
                break;
            }
            if(name == "cornflowerblue"){
                return_hex = "#6495ED";
                break;
            }
            if(name == "cornsilk"){
                return_hex = "#FFF8DC";
                break;
            }
            if(name == "crimson"){
                return_hex = "#DC143C";
                break;
            }
            if(name == "cyan"){
                return_hex = "#00FFFF";
                break;
            }
        case 'd':
            if(name == "darkblue"){
                return_hex = "#00008B";
                break;
            }
            if(name == "darkcyan"){
                return_hex = "#008B8B";
                break;
            }
            if(name == "darkgoldenrod"){
                return_hex = "#B8860B";
                break;
            }
            if(name == "darkgray" || name == "darkgrey"){
                return_hex = "#A9A9A9";
                break;
            }
            if(name == "darkgreen"){
                return_hex = "#006400";
                break;
            }
            if(name == "darkkhaki"){
                return_hex = "#BDB76B";
                break;
            }
            if(name == "darkmagenta"){
                return_hex = "#8B008B";
                break;
            }
            if(name == "darkolivegreen"){
                return_hex = "#556B2F";
                break;
            }
            if(name == "darkorange"){
                return_hex = "#FF8C00";
                break;
            }
            if(name == "darkorchid"){
                return_hex = "#9932CC";
                break;
            }
            if(name == "darkred"){
                return_hex = "#8B0000";
                break;
            }
            if(name == "darksalmon"){
                return_hex = "#E9967A";
                break;
            }
            if(name == "darkseagreen"){
                return_hex = "#8FBC8F";
                break;
            }
            if(name == "darkslateblue"){
                return_hex = "#483D8B";
                break;
            }
            if(name == "darkslategray" || name == "darkslategrey"){
                return_hex = "#2F4F4F";
                break;
            }
            if(name == "darkturquoise"){
                return_hex = "#00CED1";
                break;
            }
            if(name == "darkviolet"){
                return_hex = "#9400D3";
                break;
            }
            if(name == "darkpink"){
                return_hex = "#FF1493";
                break;
            }
            if(name == "darkskyblue"){
                return_hex = "#00BFFF";
                break;
            }
            if(name == "dimgray" || name == "dimgrey"){
                return_hex = "#696969";
                break;
            }
            if(name == "dodgerblue"){
                return_hex = "#1E90FF";
                break;
            }
        case 'f':
            if(name == "firebrick"){
                return_hex = "#B22222";
                break;
            }
            if(name == "floralwhite"){
                return_hex = "#FFFAF0";
                break;
            }
            if(name == "forestgreen"){
                return_hex = "#228B22";
                break;
            }
            if(name == "fuchsia"){
                return_hex = "#FF00FF";
                break;
            }
        case 'g':
            if(name == "gainsboro"){
                return_hex = "#DCDCDC";
                break;
            }
            if(name == "ghostwhite"){
                return_hex = "#F8F8FF";
                break;
            }
            if(name == "gold"){
                return_hex = "#FFD700";
                break;
            }
            if(name == "goldenrod"){
                return_hex = "#DAA520";
                break;
            }
            if(name == "gray" || name == "grey"){
                return_hex = "#808080";
                break;
            }
            if(name == "green"){
                return_hex = "#008000";
                break;
            }
            if(name == "greenyellow"){
                return_hex = "#ADFF2F";
                break;
            }
        case 'h':
            if(name == "honeydew"){
                return_hex = "#F0FFF0";
                break;
            }
            if(name == "hotpink"){
                return_hex = "#FF69B4";
                break;
            }
        case 'i':
            if(name == "indianred"){
                return_hex = "#CD5C5C";
                break;
            }
            if(name == "indigo"){
                return_hex = "#4B0082";
                break;
            }
            if(name == "ivory"){
                return_hex = "#FFFFF0";
                break;
            }
        case 'k':
            if(name == "khaki"){
                return_hex = "#F0E68C";
                break;
            }
        case 'l':
            if(name == "lavender"){
                return_hex = "#E6E6FA";
                break;
            }
            if(name == "lavenderblush"){
                return_hex = "#FFF0F5";
                break;
            }
            if(name == "lawngreen"){
                return_hex = "#7CFC00";
                break;
            }
            if(name == "lemonchiffon"){
                return_hex = "#FFFACD";
                break;
            }
            if(name == "lightblue"){
                return_hex = "#ADD8E6";
                break;
            }
            if(name == "lightcoral"){
                return_hex = "#F08080";
                break;
            }
            if(name == "lightcyan"){
                return_hex = "#E0FFFF";
                break;
            }
            if(name == "lightgoldenrodyellow"){
                return_hex = "#FAFAD2";
                break;
            }
            if(name == "lightgray" || name == "lightgrey"){
                return_hex = "#D3D3D3";
                break;
            }
            if(name == "lightgreen"){
                return_hex = "#90EE90";
                break;
            }
            if(name == "lightpink"){
                return_hex = "#FFB6C1";
                break;
            }
            if(name == "lightsalmon"){
                return_hex = "#FFA07A";
                break;
            }
            if(name == "lightseagreen"){
                return_hex = "#20B2AA";
                break;
            }
            if(name == "lightskyblue"){
                return_hex = "#87CEFA";
                break;
            }
            if(name == "lightslategray" || name == "lightslategrey"){
                return_hex = "#778899";
                break;
            }
            if(name == "lightsteelblue"){
                return_hex = "#B0C4DE";
                break;
            }
            if(name == "lightyellow"){
                return_hex = "#FFFFE0";
                break;
            }
            if(name == "lime"){
                return_hex = "#00FF00";
                break;
            }
            if(name == "limegree"){
                return_hex = "#32CD32";
                break;
            }
            if(name == "linen"){
                return_hex = "#FAF0E6";
                break;
            }
        case 'm':
            if(name == "magenta"){
                return_hex = "#FF00FF";
                break;
            }
            if(name == "maroon"){
                return_hex = "#800000";
                break;
            }
            if(name == "mediumaquamarine"){
                return_hex = "#66CDAA";
                break;
            }
            if(name == "mediumblue"){
                return_hex = "#0000CD";
                break;
            }
            if(name == "mediumorchid"){
                return_hex = "#BA55D3";
                break;
            }
            if(name == "mediumpurple"){
                return_hex = "#9370DB";
                break;
            }
            if(name == "mediumseagreen"){
                return_hex = "#3CB371";
                break;
            }
            if(name == "mediumslateblue"){
                return_hex = "#7B68EE";
                break;
            }
            if(name == "mediumspringgreen"){
                return_hex = "#00FA9A";
                break;
            }
            if(name == "mediumturquoise"){
                return_hex = "#48D1CC";
                break;
            }
            if(name == "mediumvioletred"){
                return_hex = "#C71585";
                break;
            }
            if(name == "midnightblue"){
                return_hex = "#191970";
                break;
            }
            if(name == "mintcream"){
                return_hex = "#F5FFFA";
                break;
            }
            if(name == "mistyrose"){
                return_hex = "#FFE4E1";
                break;
            }
            if(name == "moccasin"){
                return_hex = "#FFE4B5";
                break;
            }
        case 'n':
            if(name == "navajowhite"){
                return_hex = "#FFDEAD";
                break;
            }
            if(name == "navy"){
                return_hex = "#000080";
                break;
            }
        case 'o':
            if(name == "oldlace"){
                return_hex = "#FDF5E6";
                break;
            }
            if(name == "olive"){
                return_hex = "#808000";
                break;
            }
            if(name == "olivedrab"){
                return_hex = "#6B8E23";
                break;
            }
            if(name == "orange"){
                return_hex = "#FFA500";
                break;
            }
            if(name == "orangered"){
                return_hex = "#FF4500";
                break;
            }
            if(name == "orchid"){
                return_hex = "#DA70D6";
                break;
            }
        case 'p':
            if(name == "palegoldenrod"){
                return_hex = "#EEE8AA";
                break;
            }
            if(name == "palegreen"){
                return_hex = "#98FB98";
                break;
            }
            if(name == "paleturquoise"){
                return_hex = "#AFEEEE";
                break;
            }
            if(name == "palevioletred"){
                return_hex = "#DB7093";
                break;
            }
            if(name == "papayawhip"){
                return_hex = "#FFEFD5";
                break;
            }
            if(name == "peachpuff"){
                return_hex = "#FFDAB9";
                break;
            }
            if(name == "peru"){
                return_hex = "#CD853F";
                break;
            }
            if(name == "pink"){
                return_hex = "#FFC0CB";
                break;
            }
            if(name == "plum"){
                return_hex = "#DDA0DD";
                break;
            }
            if(name == "powderblue"){
                return_hex = "#B0E0E6";
                break;
            }
            if(name == "purple"){
                return_hex = "#800080";
                break;
            }
        case 'r':
            if(name == "rebeccapurple"){
                return_hex = "#663399";
                break;
            }
            if(name == "red"){
                return_hex = "#FF0000";
                break;
            }
            if(name == "rosybrown"){
                return_hex = "#BC8F8F";
                break;
            }
            if(name == "royalblue"){
                return_hex = "#4169E1";
                break;
            }
        case 's':
            if(name == "saddlebrown"){
                return_hex = "#8B4513";
                break;
            }
            if(name == "salmon"){
                return_hex = "#FA8072";
                break;
            }
            if(name == "sandybrown"){
                return_hex = "#F4A460";
                break;
            }
            if(name == "seagreen"){
                return_hex = "#2E8B57";
                break;
            }
            if(name == "seashell"){
                return_hex = "#FFF5EE";
                break;
            }
            if(name == "sienna"){
                return_hex = "#A0522D";
                break;
            }
            if(name == "silver"){
                return_hex = "#C0C0C0";
                break;
            }
            if(name == "skyblue"){
                return_hex = "#87CEEB";
                break;
            }
            if(name == "slateblue"){
                return_hex = "#6A5ACD";
                break;
            }
            if(name == "slategray" || name == "slategrey"){
                return_hex = "#708090";
                break;
            }
            if(name == "snow"){
                return_hex = "#FFFAFA";
                break;
            }
            if(name == "springgreen"){
                return_hex = "#00FF7F";
                break;
            }
            if(name == "steelblue"){
                return_hex = "#4682B4";
                break;
            }
        case 't':
            if(name == "tan"){
                return_hex = "#D2B48C";
                break;
            }
            if(name == "teal"){
                return_hex = "#008080";
                break;
            }
            if(name == "thistle"){
                return_hex = "#D8BFD8";
                break;
            }
            if(name == "tomato"){
                return_hex = "#FF6347";
                break;
            }
            if(name == "turquoise"){
                return_hex = "#40E0D0";
                break;
            }
        case 'v':
            if(name == "violet"){
                return_hex = "#EE82EE";
                break;
            }
        case 'w':
            if(name == "wheat"){
                return_hex = "#F5DEB3";
                break;
            }
            if(name == "white"){
                return_hex = "#FFFFFF";
                break;
            }
            if(name == "whitesmoke"){
                return_hex = "#F5F5F5";
                break;
            }
        case 'y':
            if(name == "yellow"){
                return_hex = "#FFFF00";
                break;
            }
            if(name == "yellowgreen"){
                return_hex = "#9ACD32";
                break;
            }
        }
    }
    else{
        return_hex = name;
    }
    cout << "Hex is : " << return_hex << endl;
    return return_hex;
};
