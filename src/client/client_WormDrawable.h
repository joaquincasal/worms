#ifndef __WORMDRAWABLE__
#define __WORMDRAWABLE__

#include "client_IDrawable.h"
#include <string>
#include "client_ConsoleDrawer.h"
class ConsoleDrawer;

class WormDrawable : public IDrawable {
private:
    size_t id;
    size_t life_points;
    double x;
    double y;
    int angle;
    bool is_facing_right;

    WormDrawable(const WormDrawable&) = delete;
    WormDrawable& operator=(const WormDrawable&) = delete;
public:
    WormDrawable(size_t id, size_t life_points, double x, double y, int angle, bool is_facing_right);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);

    size_t get_id();
    size_t get_life_points();
    double get_x();
    double get_y();
    int get_angle();
    bool get_is_facing_right();
    ~WormDrawable() = default;
};


#endif //__WORMDRAWABLE__