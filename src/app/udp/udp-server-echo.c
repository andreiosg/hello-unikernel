/*
 * Copyright (c) 2019 Anatolii Kurotych
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "udp-server-echo.h"
#include <stdlib.h>

// called after the data was sent
static void on_send(uv_udp_send_t *req, int status)
{
    free(req);
    if (status) {
        fprintf(stderr, "%s error: %s\n", __func__, uv_strerror(status));
    }
}

static void on_read(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf,
                    const struct sockaddr *addr, unsigned flags)
{

    (void)flags;
    if (nread < 0) {
        fprintf(stderr, "%s error: %s\n", __func__, uv_err_name(nread));
        uv_close((uv_handle_t *)req, NULL);
        free(buf->base);
        return;
    }

    if (nread > 0) {
        char sender[17] = {0};
        uv_ip4_name((const struct sockaddr_in *)addr, sender, 16);
        fprintf(stderr, "Recv From %s\n", sender);

        uv_udp_send_t *res = malloc(sizeof(uv_udp_send_t));
        uv_buf_t buff = uv_buf_init(buf->base, nread);
        uv_udp_send(res, req, &buff, 1, addr, on_send);
    }

    free(buf->base);
}

static void alloc_buffer(uv_handle_t *handle, size_t suggested_size,
                         uv_buf_t *buf)
{
    (void)handle;
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}

uv_udp_t *init_echo_udp_server(uv_loop_t *loop, const char *address,
                               uint16_t port)
{
    uv_udp_t *recv_socket = malloc(sizeof(uv_udp_t));
    struct sockaddr_in recv_addr;
    uv_ip4_addr(address, port, &recv_addr);

    uv_udp_init(loop, recv_socket);

    uv_udp_bind(recv_socket, (const struct sockaddr *)&recv_addr,
                UV_UDP_REUSEADDR);
    uv_udp_recv_start(recv_socket, alloc_buffer, on_read);

    return recv_socket;
}
