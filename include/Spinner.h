/* 
 * File:   Playground.h
 * Author: Cow
 *
 * Created on January 22, 2013, 6:02 PM
 */

#ifndef PLAYGROUND_H
#define	PLAYGROUND_H

#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <Virtuals.h>
#include <Sprites.h>
#include <ConfigFile.h>
#include <SDL_ttf.h>
#include <Button.h>

class Spin{
public:
    //constructor
    static Spin* getSingleton();
    Spin();
    ~Spin();
    //control
    int go();
    void stop();
    bool init();
    bool deinit();
    int render(void* dummy);
    int logic(void* dummy);
    int event(void* dummy);
    //manips
    bool addRenderable(Renderable* renderable);
    Renderable* remRenderable(Renderable* renderable);
    bool addLogicable(Updateable* logicable);
    Updateable* remLogicable(Updateable* logicable);
    bool addEventable(EventHandler* eventable);
    EventHandler* remEventable(EventHandler* eventable);
    void setGraphicsPeriod(int period);
    void setLogicPeriod(int period);
    void setSize(int width, int height);
    //access
    SDL_Rect getWindowDimensions();
    const SDL_Surface& getWindow();
    
private:
    //data
    static Spin* singleton;
    ConfigFile cfg;
    //flow
    bool inited;
    bool running;
    //threading
    int logicPeriod;
    int graphicsPeriod;
    SDL_Thread* logicThread;
    //sdl graphics
    int windowX;
    int windowY;
    SDL_Surface* window;
    std::vector<Renderable*> renderItems;
    //input
    std::vector<EventHandler*> eventItems;
    //logic
    std::vector<Updateable*> updateItems;
};


#endif	/* PLAYGROUND_H */

