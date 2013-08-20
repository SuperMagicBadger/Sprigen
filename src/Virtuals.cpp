#include <Virtuals.h>
#include <vector>

//renderable-------------------------------------
void Renderable::setVisible(bool vis) {
    visible = vis;
}
bool Renderable::getVisible() {
    return visible;
}
void Renderable::setRenderableRemove() {
    ren_remove = true;
}
bool Renderable::doRenderableRemove() {
    return ren_remove;
}
void Renderable::addRenderableChild(Renderable* r) {
    if (r != NULL) {
        r_children.push_back(r);
    }
}
void Renderable::passRender(SDL_Surface* s) {
    if (r_children.empty()) return;
    std::vector<Renderable*>::iterator itr = r_children.begin();
    while (itr != r_children.end()) {
        if ((*itr)->doRenderableRemove()) {
            (*itr)->ren_remove = false;
            delete *itr;
            r_children.erase(itr);
            continue;
        }
        (*itr)->onRender(s);
        itr++;
    }
}
//renderable=====================================

//event handler----------------------------------
void EventHandler::setEventRemove() {
    eh_remove = true;
}
bool EventHandler::doEventRemove() {
    return eh_remove;
}
void EventHandler::addEventChild(EventHandler* eh) {
    if (eh != NULL) eh_children.push_back(eh);
}
void EventHandler::passEvent(SDL_Event* evt) {
    if (eh_children.empty()) return;
    std::vector<EventHandler*>::iterator itr = eh_children.begin();
    while (itr != eh_children.end()) {
        if ((*itr)->doEventRemove()) {
            (*itr)->eh_remove = false;
            delete *itr;
            eh_children.erase(itr);
            continue;
        }
        if (!(*itr)->onEvent(evt)) {
            break;
        }
        itr++;
    }
}
//event handler==================================

//updateable-------------------------------------
void Updateable::addUpdateChild(Updateable* u) {
    if (u != NULL) up_children.push_back(u);
}
void Updateable::setUpdateRemove() {
    up_remove = false;
}
bool Updateable::doUpdateRemove() {
    return up_remove;
}
void Updateable::passUpdate(int miliD) {
    if (up_children.empty()) return;
    std::vector<Updateable*>::iterator itr = up_children.begin();
    while (itr != up_children.end()) {
        if ((*itr)->doUpdateRemove()) {
            (*itr)->up_remove = false;
            delete *itr;
            up_children.erase(itr);
            continue;
        }
        (*itr)->passUpdate(miliD);
        itr++;
    }
}
//updateable=====================================

//placeable--------------------------------------
void Placeable::setPosition(int _x, int _y) {
    pos_rect.x = _x;
    pos_rect.y = _y;
}
void Placeable::setCenterPosition(int _x, int _y) {
    setPosition(_x - (getW() / 2), _y - (getH() / 2));
}
void Placeable::setDims(int w, int h) {
    if (w >= 0 && h >= 0) {
        pos_rect.w = w;
        pos_rect.h = h;
    }
}
void Placeable::move(int deltaX, int deltaY) {
    pos_rect.x += deltaX;
    pos_rect.y += deltaY;
}
SDL_Rect Placeable::getRect() {
    return pos_rect;
}
int Placeable::getX() {
    return pos_rect.x;
}
int Placeable::getY() {
    return pos_rect.y;
}
int Placeable::getW() {
    return pos_rect.w;
}
int Placeable::getH() {
    return pos_rect.h;
}
int Placeable::getCenterX() {
    return (pos_rect.w / 2) +pos_rect.x;
}
int Placeable::getCenterY() {
    return (pos_rect.h / 2) +pos_rect.y;
}
bool Placeable::inBounds(int x, int y) {
    if (x > pos_rect.w + pos_rect.x || x < pos_rect.x) {
        return false;
    }
    if (y > pos_rect.h + pos_rect.y || y < pos_rect.y) {
        return false;
    }
    return true;
}
//placeable======================================
