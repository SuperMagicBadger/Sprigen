#include <Sprites.h>
#include <algorithm>

#include "Spinner.h"


#define file_prefix "../res/"
#define file_postfix ".meta"

#define include_metatag "[include]"
#define sheet_metatag "[sheet]"
#define file_metatag "[file]"
#define sprite_metatag "[sprite]"
#define floater_metatag "[floater]"


//sprite---------------------------------------------------
Sprite::Sprite(SpriteBody* sb) {
    setBody(sb);
}
Sprite::Sprite(FloatingSpriteBody* fb) {
    setBody(fb);
}
Sprite::~Sprite() { }
void Sprite::onRender(SDL_Surface* s) {
    switch (body_type) {
        case bt_body:
            body->onRender(s, pos_rect);
            break;
        case bt_floatbody:
            break;
    }
}
void Sprite::setBody(SpriteBody* b) {
    body_type = bt_body;
    floatBody = NULL;
    body = b;
    setDims(b->getDims().w, b->getDims().h);
}
void Sprite::setBody(FloatingSpriteBody* fb) {
    body_type = bt_floatbody;
    body = NULL;
    floatBody = fb;
    setDims(fb->getDims().w, fb->getDims().h);
}
//sprite===================================================

//sprite body----------------------------------------------
SpriteBody::SpriteBody(SDL_Surface* spriteSheet, SDL_Rect spriteLocation) {
    source = spriteSheet;
    bounds = spriteLocation;
}
void SpriteBody::onRender(SDL_Surface* target, SDL_Rect& targetpos) {
    SDL_BlitSurface(source, &bounds, target, &targetpos);
}
void SpriteBody::setImage(SDL_Surface* spriteSheet, SDL_Rect spriteLocation) {
    source = spriteSheet;
    bounds = spriteLocation;
}
void SpriteBody::setImage(SpriteBody* s) {
    source = s->source;
    bounds = s->bounds;
}
SDL_Rect SpriteBody::getDims() {
    return bounds;
}
//sprite body==============================================

//floating sprite body-------------------------------------
FloatingSpriteBody::FloatingSpriteBody(SDL_Surface* sheet, SDL_Rect start, int _width, int _height, int _w_step, int _h_step) {
    source = sheet;
    bounds = start;
    width = _width;
    height = _height;
    w_step = _w_step;
    h_step = _h_step;

}
void FloatingSpriteBody::onRender(SDL_Surface* surface, SDL_Rect& targetPos, int frame) {
    SDL_Rect spriteSpot = bounds;
    int h_count = height / h_step;
    int w_count = width / w_step;

    int h_spot = frame / w_count;
    int w_spot = frame - (h_spot * w_count);

    spriteSpot.x += w_spot * w_step;
    spriteSpot.y += h_spot * h_step;

    SDL_BlitSurface(source, &bounds, surface, &targetPos);
}
SDL_Rect FloatingSpriteBody::getDims() {
    return bounds;
}
//floating sprite body=====================================

//sprite sheet---------------------------------------------
SpriteSheet::SpriteSheet(string file) {
    image = IMG_Load(file.c_str());
}
SpriteSheet::SpriteSheet(SDL_Surface* surface) {
    image = surface;
}
SpriteSheet::~SpriteSheet() {
    SDL_FreeSurface(image);
    map<string, SpriteBody*>::iterator bitr;
    map<string, FloatingSpriteBody*>::iterator fbitr;

    for (bitr = bodies.begin(); bitr != bodies.end(); bitr++) {
        delete bitr->second;
    }
    bodies.clear();
    for (fbitr = floatingBodies.begin(); fbitr != floatingBodies.end(); fbitr++) {
        delete fbitr->second;
    }
    floatingBodies.clear();
}
void SpriteSheet::createBody(string name, SDL_Rect placement) {
    bodies[name] = new SpriteBody(image, placement);
}
void SpriteSheet::createFloatingBody(string name, SDL_Rect start, int width, int height, int w_step, int h_step) {
    floatingBodies[name] = new FloatingSpriteBody(image, start, width, height, w_step, h_step);
}
SpriteBody* SpriteSheet::getBody(string name) {
    if (bodies.find(name) == bodies.end()) return NULL;
    return bodies[name];
}
FloatingSpriteBody* SpriteSheet::getFloatingBody(string name) {
    if (floatingBodies.find(name) == floatingBodies.end()) return NULL;
    return floatingBodies[name];
}
//sprite sheet=============================================

//sprite factory-------------------------------------------
SpriteFactory* SpriteFactory::singleton;
//constructors
SpriteFactory::SpriteFactory() { }
SpriteFactory::~SpriteFactory() { }
SpriteFactory* SpriteFactory::getSingleton() {
    if (singleton == NULL) {
        singleton = new SpriteFactory();
    }
    return singleton;
}
//generators
void SpriteFactory::loadSheet(const string& sheetname) {
    //varblok------
    string metaname;
    string imagename;
    string token;
    string name;
    ifstream file;
    SDL_Surface* imageSurface = NULL;
    SDL_Rect rect;
    SpriteSheet* working_sheet = NULL;
    int floaterW, floaterH, floaterWStep, floaterHStep;
    //varblok======

    //load the meta file
    metaname = file_prefix + sheetname + file_postfix;
    file.open(metaname.c_str(), ifstream::in);

    if (!file.good()) {
        cout << "could not open file: " << metaname << endl;
    } else {
        cout << "opened file: " << metaname << endl;
    }
    //==================

    //parse the file
    while (file.good()) {
        //grab a token
        file >> token;
        cout << "--" << token << " " << endl;
        //and process
        if (token.compare(sprite_metatag) == 0) { //sprite
            file >> name >> rect.x >> rect.y >> rect.w >> rect.h;
            cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << endl;
            if (working_sheet != NULL) {
                cout << "adding sprite " << name << endl;
                working_sheet->createBody(name, rect);
                cout << "adding sprite " << name << endl;
            } else {
                cout << "did not load sprite, no working sheet" << name << endl;
            }
        } else if (token.compare(floater_metatag) == 0) { //floater
            file >> name >> rect.x >> rect.y >> rect.w >> rect.h;
            file >> floaterW >> floaterH >> floaterWStep >> floaterHStep;
            cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << endl;
            if (working_sheet != NULL) {
                working_sheet->createFloatingBody(name, rect, floaterW, floaterH, floaterWStep, floaterHStep);
            } else {
                cout << "did not load floater, no woeking sheet: " << name << endl;
            }
        } else if (token.compare(file_metatag) == 0) { //file
            file >> imagename;
            imageSurface = IMG_Load((file_prefix + imagename).c_str());
            if (imageSurface == NULL) {
                cout << "bad image file: " << imagename << endl;
            } else {
                cout << "loaded image file: " << imagename << endl;
            }
        } else if (token.compare(sheet_metatag) == 0) { //sheet
            file >> name;
            if (imageSurface != NULL) {
                working_sheet = new SpriteSheet(imageSurface);
                if (sheets.find(name) != sheets.end()) {
                    delete sheets[name];
                }
                sheets[name] = working_sheet;
            } else {
                cout << "did not load sheet, no image loaded: " << name << endl;
            }
        } else if (token.compare(include_metatag) == 0) { //include
            file >> name;
            loadSheet(name);
        }
    }
    //parse=========

    //clean up
    file.close();
    //clean===

}
void SpriteFactory::unloadSheet(const std::string& sheetName) {
    if (sheets.find(sheetName) != sheets.end()) {
        delete sheets[sheetName];
        sheets.erase(sheetName);
    }
}
SpriteBody* SpriteFactory::getSpriteBody(const string& groupname, const string& spritename) {
    if (sheets.find(groupname) != sheets.end()) {
        return sheets[groupname]->getBody(spritename);
    } else {
        cout << "no such sheet\n";
        return NULL;
    }
}
FloatingSpriteBody* SpriteFactory::getFloatingSpriteBody(const string& sheet, const string& sprite) {
    if (sheets.find(sheet) != sheets.end()) {
        return sheets[sheet]->getFloatingBody(sprite);
    } else {
        cout << "no such sheet\n";
        return NULL;
    }
}
Sprite* SpriteFactory::createSprite(const string& sheet, const string& sprite) {
    if (getSpriteBody(sheet, sprite) != NULL) {
        return new Sprite(getSpriteBody(sheet, sprite));
    } else if (getFloatingSpriteBody(sheet, sprite) != NULL) {
        return new Sprite(getFloatingSpriteBody(sheet, sprite));
    } else {
        cout << "no such sprite\n";
    }
    return NULL;
}
//sprtie factory===========================================
