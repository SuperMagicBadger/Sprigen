#include <ConfigFile.h>
#include <iostream>
#include <string.h>
using namespace std;

#define screen_x_tag "screenx"
#define screen_y_tag "screeny"
#define color_depth_tag "colordepth"

ConfigFile::ConfigFile(std::string filename){
    
    //init vars
    windowX = 640;
    windowY = 480;
    colorDepth = 32;
    
    ifstream file(filename.c_str());
    string line;
    
    while(!file.eof()){
        file >> line;
        if(line.compare(screen_x_tag) == 0){
            file >> windowX;
            cout << "set screen x to " << windowX << "\n";
        } else if (line.compare(screen_y_tag) == 0){
            file >> windowY;
            cout << "set screen y to " << windowY << "\n";
        } else if (line.compare(color_depth_tag) == 0){
            file >> colorDepth;
            cout << "color depth set to " << colorDepth << endl;
            
        }
    }
}
