/* 
 * File:   Renderable.h
 * Author: Cow
 *
 * Created on January 23, 2013, 6:20 AM
 */

#ifndef VIRTUALS_H
#define	VIRTUALS_H

#include <SDL/SDL.h>
#include <vector>

#define KEEP_EVENT true
#define KILL_EVENT false

class Renderable {
public:
    Renderable(){ren_remove = false;}
    virtual void onRender(SDL_Surface* surf) = 0;
    void setVisible(bool vis);
    bool getVisible();
    void addRenderableChild(Renderable* r);
    void setRenderableRemove();
    bool doRenderableRemove();
protected:
    virtual void passRender(SDL_Surface* s);
    bool visible;
    bool ren_remove;
    std::vector<Renderable*> r_children;
};

class EventHandler {
public:
    //returning false will remove the event from the pool
    EventHandler(){eh_remove = false;}
    virtual bool onEvent(SDL_Event* evt) = 0;
    void addEventChild(EventHandler* eh);
    void setEventRemove();
    bool doEventRemove();
protected:
    virtual void passEvent(SDL_Event* evt);
    std::vector<EventHandler*> eh_children;
    bool eh_remove;
};

class Updateable {
public:
    Updateable(){up_remove = false;}
    virtual void onUpdate(int miliDelta) = 0;
    void addUpdateChild(Updateable* u);
    void setUpdateRemove();
    bool doUpdateRemove();
protected:
    virtual void passUpdate(int miliDelta);
    std::vector<Updateable*> up_children;
    bool up_remove;
};

class Placeable {
public:
    virtual void setPosition(int x, int y);
    virtual void setCenterPosition(int x, int y);
    virtual void setDims(int w, int h);
    virtual void move(int deltaX, int deltaY);
    virtual SDL_Rect getRect();
    virtual int getX();
    virtual int getY();
    virtual int getW();
    virtual int getH();
    virtual int getCenterX();
    virtual int getCenterY();
    virtual bool inBounds(int x, int y);
protected:
    SDL_Rect pos_rect;
};


#endif	/* VIRTUALS_H */

