/* 
 * File:   Frame.h
 * Author: Cow
 *
 * Created on February 11, 2013, 7:01 PM
 */

#ifndef FRAME_H
#define	FRAME_H

#include <string>
#include <map>

class Frame{
public:
    virtual void bind() = 0;
    virtual void release() = 0;
};

class FrameManager{
public:
    //constructor
    static FrameManager* getSingleton();
    FrameManager();
    ~FrameManager();
    //control
    void bind(std::string frame);
    void release(std::string frame);
    //manips
    void addFrame(std::string frameName, Frame* frame);
    Frame* remFrame(std::string frameName);
    //access
    Frame* getFrame(std::string frame);
private:
    static FrameManager* singleton;
    std::map<std::string, Frame*> frames;
};

#endif	/* FRAME_H */

