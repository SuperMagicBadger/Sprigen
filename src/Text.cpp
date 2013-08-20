
#include <Text.h>
#define file_prefix "../res/"
#define file_postfix ".ttf"

//Line-----------------------------------------------------
Line::Line(string text, TTF_Font* font, render_type r, SDL_Color fg, SDL_Color bg) {
    text_surf = NULL;
    setMessage(text);
    setFont(font);
    setRenderType(r);
    setFG(fg);
    setBG(bg);
}
Line::~Line() {
    unrender();
}
//renderable
void Line::onRender(SDL_Surface* surf) {
    render();
    SDL_Rect r = getRect();
    SDL_BlitSurface(text_surf, &(text_surf->clip_rect), surf, &r);
}
//manips
void Line::setMessage(string msg) {
    message = msg;
    unrender();
}
void Line::setFont(TTF_Font* f) {
    font = f;
    unrender();
}
void Line::setRenderType(render_type rt) {
    render_t = rt;
    unrender();
}
void Line::setFG(SDL_Color fg) { 
    fore_g = fg;
    unrender();
}
void Line::setBG(SDL_Color bg) {
    bck_g = bg;
    unrender();
}
//helpers
void Line::render() {
    if (text_surf == NULL) {
        switch (render_t) {
            case solid:
                text_surf = TTF_RenderText_Solid(font, message.c_str(), fore_g);
                break;
            case shaded:
                text_surf = TTF_RenderText_Shaded(font, message.c_str(), fore_g, bck_g);
                break;
            case blended:
                text_surf = TTF_RenderText_Blended(font, message.c_str(), fore_g);
                break;
        }
        setDims(text_surf->w, text_surf->h);
    }
}
void Line::unrender() {
    if(text_surf != NULL){
        SDL_FreeSurface(text_surf);
        text_surf = NULL;
    }
}
//Line=====================================================
//Text Box-------------------------------------------------
//Text Box=================================================
//Font Engine----------------------------------------------
FontFactory* FontFactory::single = NULL;
//constructors
FontFactory* FontFactory::getSingleton() {
    if (!single) {
        single = new FontFactory();
    }
    return single;
}
FontFactory::FontFactory() { }
FontFactory::~FontFactory() { }
//Control
bool FontFactory::loadFont(string fontname, int size) {
    char buff[2];
    TTF_Font* f = TTF_OpenFont((file_prefix + fontname + file_postfix).c_str(), size);
    fonts[fontname.append(itoa(size, buff, 10))] = f;
    return f != NULL;
}
void FontFactory::remFont(string fontname, int size) {
    char buff[2];
    TTF_CloseFont(fonts[fontname.append(itoa(size, buff, 10))]);
    fonts.erase(fontname.append(itoa(size, buff, 10)));
}
void FontFactory::reset() { }
//access
TTF_Font* FontFactory::getFont(string fontname, int size) {
    char buff[2];
    return fonts[fontname.append(itoa(size, buff, 10))];
}
//Font Engine==============================================