#include <Spinner.h>

//hidden helpers-------------
int logicHelper(void* state) {
    Spin* engine = (Spin*) state;
    return engine->logic(NULL);
}
//hidden helpers=============

//constructor----------------
Spin* Spin::singleton = NULL;
Spin* Spin::getSingleton() {
    if (singleton == NULL) {
        singleton = new Spin();
    }
    return singleton;
}
Spin::Spin() :
cfg("config") {
    running = inited = false;
    logicPeriod = 10;
    graphicsPeriod = 10;
}
Spin::~Spin() { }
//constructor=================

//initialization--------------
bool Spin::init() {
    if (inited) return false;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if (TTF_Init() < 0) return false;
    //create viewport
    window = SDL_SetVideoMode(cfg.windowX, cfg.windowY, cfg.colorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    if (window == NULL) return false;
    //finalizing
    inited = true;
    running = true;
    return true;
}
bool Spin::deinit() {
    if (!inited) return false;
    TTF_Quit();
    SDL_Quit();
    std::cout.flush();
    inited = false;
    return true;
}
//initialization==============

//control---------------------
int Spin::go() {
    int start_ticks, end_ticks;

    logicThread = SDL_CreateThread(logicHelper, this);

    while (running) {
        start_ticks = SDL_GetTicks();
        event(NULL);
        render(NULL);
        end_ticks = SDL_GetTicks();
        std::cout.flush();
        if (graphicsPeriod > (end_ticks - start_ticks)) {
            SDL_Delay(graphicsPeriod - (end_ticks - start_ticks));
        }
    }

    SDL_WaitThread(logicThread, NULL);

    std::cout << "hi";

}
void Spin::stop() {
    running = false;
}
int Spin::render(void* dummy) {
    SDL_Rect r;
    r.x = r.y = 0;
    r.w = window->w;
    r.h = window->h;
    SDL_FillRect(window, &window->clip_rect, SDL_MapRGB(window->format, 0, 0, 0));

    std::vector<Renderable*>::iterator itr = renderItems.begin();
    while (itr != renderItems.end()) {
        //check to make sure he hasn't suicided
        if ((*itr)->doRenderableRemove()) {
            renderItems.erase(itr);
            continue;
        }
        (*itr)->onRender(window);
        itr++;
    }

    SDL_Flip(window);
    return 0;
}
int Spin::event(void* dummy) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        //engine gets first pick
        if (e.type == SDL_QUIT) {
            std::cout << "ITS KILLIN TIME\n";
            running = false;
            return 0;
        } else if (e.type == SDL_VIDEORESIZE) {
            setSize(e.resize.w, e.resize.h);
        }
        //and these loosers get the leftovers
        std::vector<EventHandler*>::iterator itr = eventItems.begin();
        while (itr != eventItems.end()) {
            //check to make sure he hasn't suicided
            if ((*itr)->doEventRemove()) {
                eventItems.erase(itr);
                continue;
            }
            if (!(*itr)->onEvent(&e)) {
                break;
            }
            itr++;
        }
    }
    return 0;
}
int Spin::logic(void* dummy) {
    int start_ticks;
    int end_ticks;

    while (running) {
        std::vector<Updateable*>::iterator itr;
        itr = updateItems.begin();

        while (itr != updateItems.end()) {
            if ((*itr)->doUpdateRemove()) {
                updateItems.erase(itr);
                continue;
            }
            (*itr)->onUpdate(1);
            itr++;
        }

        if (logicPeriod > (end_ticks - start_ticks))
            SDL_Delay(logicPeriod - (end_ticks - start_ticks));
    }
    std::cout << "Ending logic!\n";
    return 0;
}
//control====================
//manips---------------------
bool Spin::addRenderable(Renderable* renderable) {
    if (renderable != NULL) {
        renderItems.push_back(renderable);
    }
}
Renderable* Spin::remRenderable(Renderable* renderable) {
    Renderable* ret = NULL;
    std::vector<Renderable*>::iterator killer;
    for (killer = renderItems.begin(); killer != renderItems.end(); killer++) {
        if (*killer == renderable) {
            ret = *killer;
            renderItems.erase(killer);
            break;
        }
    }
    return ret;
}
bool Spin::addLogicable(Updateable* logicable) {
    if (logicable != NULL) {
        updateItems.push_back(logicable);
    }
}
Updateable* Spin::remLogicable(Updateable* logicable) {
    Updateable* ret = NULL;
    std::vector<Updateable*>::iterator killer;
    for (killer = updateItems.begin(); killer != updateItems.end(); killer++) {
        if (*killer == logicable) {
            ret = *killer;
            updateItems.erase(killer);
            break;
        }
    }
    return ret;
}
bool Spin::addEventable(EventHandler* eventable) {
    if (eventable != NULL) {
        eventItems.push_back(eventable);
    }
}
EventHandler* Spin::remEventable(EventHandler* eventable) {
    EventHandler* ret = NULL;
    std::vector<EventHandler*>::iterator killer;
    for (killer = eventItems.begin(); killer != eventItems.end(); killer++) {
        if (*killer == eventable) {
            ret = *killer;
            eventItems.erase(killer);
            break;
        }
    }
    return ret;
}
void Spin::setGraphicsPeriod(int period) {
    graphicsPeriod = period;
}
void Spin::setLogicPeriod(int period) {
    logicPeriod = period;
}
void Spin::setSize(int width, int height) {
    std::cout << width << " " << height << std::endl;
    window = SDL_SetVideoMode(width, height, cfg.colorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
}
//manips=====================
//access---------------------
SDL_Rect Spin::getWindowDimensions() {
    SDL_Rect ret;
    ret.x = ret.y = 0;
    ret.w = window->w;
    ret.h = window->h;
    return ret;
}
const SDL_Surface& Spin::getWindow() {
    return *window;
}
//access=====================