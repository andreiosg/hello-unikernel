#ifndef UDP_SERVER_ECHO_H
#define UDP_SERVER_ECHO_H

#include <uv.h>

uv_udp_t *init_echo_udp_server(uv_loop_t *loop, const char *address,
                               uint16_t port);

#endif /* UDP_SERVER_ECHO_H */
