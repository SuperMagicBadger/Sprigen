/* 
 * File:   ConfigFile.h
 * Author: Cow
 *
 * Created on January 23, 2013, 6:17 PM
 */

#ifndef CONFIGFILE_H
#define	CONFIGFILE_H

#include <String>
#include <fstream>

class ConfigFile{
public:
    ConfigFile(std::string str);
    
    int windowX;
    int windowY;
    int colorDepth;
};

#endif	/* CONFIGFILE_H */

