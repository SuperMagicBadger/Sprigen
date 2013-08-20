/* 
 * File:   Sprites.h
 * Author: Cow
 *
 * Created on January 31, 2013, 11:26 PM
 */

#ifndef SPRITES_H
#define	SPRITES_H

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <string>
#include <map>

#include <Virtuals.h>

using namespace std;

class Sprite;
class SpriteBody;
class FloatingSpriteBody;
class SpriteSheet;
class SpriteFactory;


class Sprite : public Renderable, public Placeable {
public:
    //constructor
    Sprite(SpriteBody* sb);
    Sprite(FloatingSpriteBody* fb);
    ~Sprite();
    //rendering
    void onRender(SDL_Surface* s);
    //manips
    void setBody(SpriteBody* b);
    void setBody(FloatingSpriteBody* fb);
    void setFrame(int i);
private:
    enum{
        bt_body,
        bt_floatbody
    } body_type;
    SpriteBody* body;
    FloatingSpriteBody* floatBody;
    int frame;
};

class SpriteBody {
public:
    //constructor
    SpriteBody(SDL_Surface* sheet, SDL_Rect spriteLocation);
    //rendering
    void onRender(SDL_Surface* target, SDL_Rect& targetPos);
    //manips
    void setImage(SDL_Surface* spriteSheet, SDL_Rect spriteLocation);
    void setImage(SpriteBody* s);
    //access
    SDL_Rect getDims();
private:
    SDL_Surface* source;
    SDL_Rect bounds;
};

class FloatingSpriteBody{
public:
    //constructor
    FloatingSpriteBody(SDL_Surface* sheet, SDL_Rect start, int width, int height, int w_step, int h_step);
    //rendering
    void onRender(SDL_Surface* surface, SDL_Rect& targetPos, int frame);
    //access
    SDL_Rect getDims();
private:
    SDL_Surface* source;
    SDL_Rect bounds;
    int width, height;
    int w_step, h_step;
};

class SpriteSheet {
public:
    //constructors
    SpriteSheet(string file);
    SpriteSheet(SDL_Surface* surface);
    ~SpriteSheet();
    //manips
    void createBody(string name, SDL_Rect placement);
    void createFloatingBody(string name, SDL_Rect start, int width, int height, int w_step, int h_step);
    //access
    SpriteBody* getBody(string name);
    FloatingSpriteBody* getFloatingBody(string name);
private:
    SDL_Surface* image;
    map<string, SpriteBody*> bodies;
    map<string, FloatingSpriteBody*> floatingBodies;
};

class SpriteFactory {
public:
    //constructors
    SpriteFactory();
    ~SpriteFactory();
    static SpriteFactory* getSingleton();
    //generators
    void loadSheet(const std::string& sheetname);
    void unloadSheet(const std::string& sheetName);
    //access
    SpriteBody* getSpriteBody(const string& sheet, const string& sprite);
    FloatingSpriteBody* getFloatingSpriteBody(const string& sheet, const string& sprite);
    Sprite* createSprite(const string& sheet, const string& sprite);
private:
    static SpriteFactory* singleton;
    map<string, SpriteSheet*> sheets;
    
};

#endif	/* SPRITES_H */

