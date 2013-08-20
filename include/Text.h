/* 
 * File:   Text.h
 * Author: Cow
 *
 * Created on April 9, 2013, 5:03 AM
 */

#ifndef TEXT_H
#define	TEXT_H

#include <Virtuals.h>
#include <map>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Line;
class TextBox;
class FontFactory;

class Line : public Renderable, public Placeable{
public:
    enum render_type{solid, shaded, blended};
public:
    //constructor
    Line(string text, TTF_Font* font, render_type rt, SDL_Color fg, SDL_Color bg);
    ~Line();
    //renderable
    void onRender(SDL_Surface* surf);
    //manips
    void setMessage(string message);
    void setFont(TTF_Font* f);
    void setRenderType(render_type rt);
    void setFG(SDL_Color fg);
    void setBG(SDL_Color bg);
    
private:
    void render();
    void unrender();
    
    SDL_Surface* text_surf;
    string message;
    SDL_Color fore_g, bck_g;
    TTF_Font* font;
    render_type render_t;
};

class FontFactory{
public:
    //constructors
    static FontFactory* getSingleton();
    ~FontFactory();
    //control
    bool loadFont(string fontname, int size);
    void remFont(string fontname, int size);
    void reset();    
    //access
    TTF_Font* getFont(string fontname, int size);
private:
    FontFactory();
    static FontFactory* single;
    
    map<string, TTF_Font*> fonts;
};

#endif	/* TEXT_H */

