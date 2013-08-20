#include <Button.h>
#include <iostream>

#define rest sprites[_rest]
#define hover sprites[_hover]
#define press sprites[_press]
#define disable sprites[_disable]


//constructor------------------------------------
Button::Button(SpriteBody* restSprite) {
    //bind sprites
    rest = restSprite;
    press = hover = disable = NULL;
    //set dimensions
    if (rest != NULL) {
        SDL_Rect r = rest->getDims();
        setDims(r.w, r.h);
    } else {
        setDims(0, 0);
    }
    //initialize misc
    actionHandler = NULL;
    eh_remove = false;
    ren_remove = false;
    toggleable = false;
    state = activeSprite = _rest;
}
Button::~Button() { }
//control----------------------------------------
void Button::showRest() {
    activeSprite = _rest;
    state = _rest;
}
void Button::showPress() {
    if (press != NULL) {
        activeSprite = _press;
    }
    state = _press;
}
void Button::showHover() {
    if (hover != NULL) {
        activeSprite = _hover;
    }
    state = _hover;
}
void Button::showDisable() {
    if (disable != NULL) {
        activeSprite = _disable;
    }
    state = _disable;
}
//manips-----------------------------------------
void Button::setRest(SpriteBody* s) {
    rest = s;
}
void Button::setPress(SpriteBody* s) {
    press = s;
}
void Button::setHover(SpriteBody* s) {
    hover = s;
}
void Button::setDisable(SpriteBody* s) {
    disable = s;
}
bool Button::inBounds(int x, int y) {
    if (x < pos_rect.x || x > pos_rect.w + pos_rect.x) {
        return false;
    }
    if (y < pos_rect.y || y > pos_rect.h + pos_rect.y) {
        return false;
    }
    return true;
}
void Button::setActionHandler(ButtonAction* action) {
    actionHandler = action;
}
void Button::setTogleable(bool tg) {
    toggleable = tg;
}
//access-----------------------------------------
buttonState Button::getState() {
    return state;
}
//virtuals---------------------------------------
void Button::onRender(SDL_Surface* surf) {
    if (sprites[activeSprite] != NULL) {
        sprites[activeSprite]->onRender(surf, pos_rect);
    }
}
bool Button::onEvent(SDL_Event* evt) {
    switch (evt->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (getState() == _hover && inBounds(evt->button.x, evt->button.y)) {
                showPress();
                if (actionHandler != NULL) {
                    actionHandler->onPress();
                }
                return KILL_EVENT; //remove event from queue
            }
            if (toggleable && inBounds(evt->button.x, evt->button.y) && getState() == _press) {
                showHover();
                if (actionHandler != NULL) {
                    actionHandler->onRelease();
                }
                return KILL_EVENT;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (getState() == _press) {
                if (inBounds(evt->button.x, evt->button.y) && !toggleable) {
                    showHover();
                } else if (!toggleable) {
                    showRest();
                }
                if (!toggleable && actionHandler != NULL) {
                    actionHandler->onRelease();
                }
                return KILL_EVENT;
            }
            break;
        case SDL_MOUSEMOTION:
            if (getState() == _rest && inBounds(evt->motion.x, evt->motion.y)) {
                showHover();
                if (actionHandler != NULL) {
                    actionHandler->onEnter();
                }
                return KILL_EVENT;
            } else if (getState() == _hover && !inBounds(evt->motion.x, evt->motion.y)) {
                showRest();
                if (actionHandler != NULL) {
                    actionHandler->onExit();
                }
                return KILL_EVENT;
            }
            break;
    }

    return KEEP_EVENT; //keep the event in queue
}
//helpers----------------------------------------