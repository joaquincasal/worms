#ifndef __WORMNOTIFICATION__
#define __WORMNOTIFICATION__

#include "server_INotification.h"

class WormNotification : public INotification {
private:
    ClientHandler* client;
    size_t id;
    size_t life_points;
    int x;
    int y;
    int angle;
    bool is_facing_right;

    WormNotification(const WormNotification&) = delete;
    WormNotification& operator=(const WormNotification&) = delete;
public:
    WormNotification(ClientHandler* client, size_t id, size_t life_points,\
                      int x, int y, int angle, bool is_facing_right);

    void run();

    ~WormNotification() = default;
};


#endif //__WORMNOTIFICATION__