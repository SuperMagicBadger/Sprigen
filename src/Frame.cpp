#include <Frame.h>
#include <iostream>

//constructors-----------------------------------
FrameManager* FrameManager::singleton = NULL;
FrameManager* FrameManager::getSingleton(){
    if(singleton == NULL){
        singleton = new FrameManager();
    }
    return singleton;
}
FrameManager::FrameManager(){
    
}
FrameManager::~FrameManager(){
    
}
//constructor====================================
//control----------------------------------------
void FrameManager::bind(std::string frame){
    if(frames.find(frame) != frames.end()){
        frames[frame]->bind();
    } else {
        std::cout << "no such frame\n";
    }
}
void FrameManager::release(std::string frame){
    if(frames.find(frame) != frames.end()){
        frames[frame]->release();
    }
}
//control========================================
//manips-----------------------------------------
void FrameManager::addFrame(std::string frameName, Frame* frame){
    if(frames.find(frameName) == frames.end()){
        frames[frameName] = frame;
    }
}
Frame* FrameManager::remFrame(std::string frameName){
    Frame* f = NULL;
    if(frames.find(frameName) != frames.end()){
        f = frames[frameName];
        frames.erase(frameName);
    }
    return f;
}
//manips=========================================
//access-----------------------------------------
Frame* FrameManager::getFrame(std::string frame){
    Frame* f = NULL;
    if(frames.find(frame) != frames.end()){
        f = frames[frame];
    }
    return f;
}
//access=========================================