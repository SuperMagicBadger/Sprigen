#include "Drawing.h"
#include "Spinner.h"
#include <SDL_draw.h>


//Drawing Frame------------------------------------------------------
//constructors---------------
DrawingFrame::DrawingFrame(SDL_Surface* surface) {
    sdl_surf = surface;
}
DrawingFrame::~DrawingFrame() {
}
//manips---------------------
void DrawingFrame::addDrawable(Drawable* dr) {
    draw_items.push_back(dr);
    addEventChild(dr);
}
//frame----------------------
void DrawingFrame::bind() {
    Spin::getSingleton()->addRenderable(this);
    Spin::getSingleton()->addEventable(this);
}
void DrawingFrame::release() {
    setRenderableRemove();
    setEventRemove();
}
//renderable-----------------
void DrawingFrame::onRender(SDL_Surface* surf) {
    for (int i = 0; i < draw_items.size(); i++) {
        draw_items[i]->draw(this);
    }
}
//event handler--------------
bool DrawingFrame::onEvent(SDL_Event* evt) {
    passEvent(evt);
}
//Drawing Frame======================================================

//square-------------------------------------------------------------
Square::Square(int x, int y, int w, int h) {
    setPosition(x, y);
    setDims(w, h);
}
void Square::draw(DrawingFrame* frame) {
}
bool Square::onEvent(SDL_Event* evt){
    
}
//square=============================================================