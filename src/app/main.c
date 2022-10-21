#include <stdlib.h>

#include <uv.h>

#include "constants.h"
#include "udp/udp-server-echo.h"
#include "json/json-parser.h"

static uv_udp_t *udp_socket = NULL;

static void on_walk_cleanup(uv_handle_t *handle, void *data)
{
    (void)data;
    uv_close(handle, NULL);
}

static void on_server_exit()
{
    fprintf(stderr, "%s: server cleanup\n", __func__);
    // clean all stuff
    uv_stop(uv_default_loop());
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_walk(uv_default_loop(), on_walk_cleanup, NULL);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    free(udp_socket);
    json_print_parsed(GOODBYE_JSON);
    exit(0);
}

static void on_signal(uv_signal_t *signal, int signum)
{
    (void)signum;
    fprintf(stderr, "\n%s: signal recieved\n", __func__);

    uv_signal_stop(signal);
    if (udp_socket)
        uv_close((uv_handle_t *)udp_socket, on_server_exit);
    else
        on_server_exit();
}

static inline void init_signal(uv_loop_t *loop, uv_signal_t *signal, int signum)
{
    uv_signal_init(loop, signal);
    uv_signal_start(signal, on_signal, signum);
}

int main(int argc, const char **argv)
{
    (void)argc;
    (void)argv;

    json_print_parsed(HELLO_JSON);

    uv_loop_t *loop = uv_default_loop();

    uv_signal_t sigkill, sigterm, sigint;
    init_signal(loop, &sigkill, SIGKILL);
    init_signal(loop, &sigterm, SIGTERM);
    init_signal(loop, &sigint, SIGINT);

    udp_socket = init_echo_udp_server(loop, ADDRESS, PORT);

    return uv_run(loop, UV_RUN_DEFAULT);
}
