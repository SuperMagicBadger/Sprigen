/* 
 * File:   Button.h
 * Author: Cow
 *
 * Created on February 6, 2013, 2:10 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <Virtuals.h>
#include <Sprites.h>

class Button;
class ButtonAction;

enum buttonState {
    _rest = 0, _press, _hover, _disable, _bs_size
};

class ButtonAction{
public:
    virtual void onPress(){}
    virtual void onRelease(){}
    virtual void onEnter(){}
    virtual void onExit(){}
};

class Button : public Renderable, public EventHandler, public Placeable {
public:
    //constructor
    Button(SpriteBody* s);
    ~Button();
    //control
    void showRest();
    void showPress();
    void showHover();
    void showDisable();
    void setTogleable(bool tg);
    //manips
    void setRest(SpriteBody* s);
    void setPress(SpriteBody* s);
    void setHover(SpriteBody* s);
    void setDisable(SpriteBody* s);
    void setActionHandler(ButtonAction* action);
    //access
    buttonState getState();
    //virtuals
    void onRender(SDL_Surface* surf);
    virtual bool onEvent(SDL_Event* evt);
private:
    //helpers
    bool inBounds(int x, int y);
    
    //vars
    bool enabled, toggleable;
    buttonState state, activeSprite;
    SpriteBody* sprites[_bs_size];
    ButtonAction* actionHandler;
    
};

#endif	/* BUTTON_H */

