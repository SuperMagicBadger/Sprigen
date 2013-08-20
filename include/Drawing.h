/* 
 * File:   Drawing.h
 * Author: Cow
 *
 * Created on April 3, 2013, 5:07 PM
 */

#ifndef DRAWING_H
#define	DRAWING_H

#include <SDL/SDL.h>
#include <vector>
#include <Frame.h>
#include <Virtuals.h>
#include <SDL_draw.h>
#include <SDL_draw.h>

using namespace std;

class DrawingFrame;
class Drawable;
class Square;
class Circle;

class DrawingFrame : public Frame, public Renderable, public EventHandler{
public:
    //constructors
    DrawingFrame(SDL_Surface* surface);
    ~DrawingFrame();
    //manips
    void addDrawable(Drawable* dr);
    //frame
    void bind();
    void release();
    //Renderable
    void onRender(SDL_Surface* surf);
    //event handler
    bool onEvent(SDL_Event* evt);
public:
    SDL_Surface* sdl_surf;
    vector<Drawable*> draw_items;
};

class Drawable : public Placeable, public EventHandler{
public:
    virtual void draw(DrawingFrame* frame) = 0;
private:
};

class Square : public Drawable{
public:
    Square(int x, int y, int w, int h);
    void draw(DrawingFrame* frame);
    bool onEvent(SDL_Event* evt);
private:
};
class Circle : public Drawable{
public:
private:
};
#endif	/* DRAWING_H */

