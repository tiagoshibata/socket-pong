#ifndef PONG_SHARED_SOCKET_H
#define PONG_SHARED_SOCKET_H

typedef struct {
    int width;
    int height;
    int player_width;
} init_packet;

int connect_to(const char *addr, const char *port);

#endif
