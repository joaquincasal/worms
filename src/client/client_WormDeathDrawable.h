#ifndef __WORMDEATHDRAWABLE__
#define __WORMDEATHDRAWABLE__

#include "client_IDrawable.h"
#include <string>
#include "client_ConsoleDrawer.h"
#include "client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class WormDeathDrawable : public IDrawable {
private:
    size_t id;

    WormDeathDrawable(const WormDeathDrawable&) = delete;
    WormDeathDrawable& operator=(const WormDeathDrawable&) = delete;
public:
    WormDeathDrawable(size_t id);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

    size_t get_id();
    ~WormDeathDrawable() = default;
};


#endif //__WORMDEATHDRAWABLE__
