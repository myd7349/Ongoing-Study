#include <stdlib.h>

#include <uv.h>

#include "../../clog.h"


#define INPUT_MAX_LEN (1024)


typedef struct
{
    uv_write_t req;
    uv_buf_t   buf;
} write_req_t;


void on_write(uv_write_t *req, int status)
{
    if (status == 0)
    {
        write_req_t *req_param = (write_req_t *)req;

    }
    else
    {
        ERR("Failed to send data to Echo server: %s(%s)", uv_strerror(status), uv_err_name(status));
        free(req);
    }
}


void on_connect(uv_connect_t *connect, int status)
{
    if (status == 0)
    {
        char input[INPUT_MAX_LEN];
        fgets(input, INPUT_MAX_LEN, stdin);
        size_t length = strnlen(input, INPUT_MAX_LEN);
        if (input[length - 1] == '\n')
        {
            input[length - 1] = '\0';
            length -= 1;
        }

        write_req_t *req_param = malloc(sizeof(write_req_t));
        if (req_param == NULL)
        {
            uv_close(connect, NULL);
            ERR("Failed to allocate memory for req_param");
            return;
        }

        req_param->buf = uv_buf_init(input, length);

        status = uv_write(&req_param->req, connect->handle, &req_param->buf, 1, on_write);
        if (status != 0)
        {
            uv_close(connect, NULL);
            ERR("uv_write failed: %s(%s)", uv_strerror(status), uv_err_name(status));
            free(req_param->buf.base);
            free(req_param);
        }
    }
    else
    {
        ERR("Failed to connect to Echo server: %s(%s)", uv_strerror(status), uv_err_name(status));
        free(connect);
    }
}


int main(int argc, char *argv[])
{
    uv_loop_t *loop = uv_default_loop();
    if (loop == NULL)
    {
        ERR("Failed to create default uv loop.");
        return EXIT_FAILURE;
    }

    uv_tcp_t *socket = malloc(sizeof(uv_tcp_t));
    if (socket == NULL)
    {
        ERR("malloc failed.");
        uv_loop_close(loop);
        free(loop);
        return EXIT_FAILURE;
    }
    uv_tcp_init(loop, socket);

    uv_connect_t *connect = malloc(sizeof(uv_connect_t));
    if (connect == NULL)
    {
        ERR("malloc failed.");
        free(socket);
        uv_loop_close(loop);
        free(loop);
        return EXIT_FAILURE;
    }

    error = uv_tcp_connect(connect, socket, (const struct sockaddr *)&server, on_connect);
    if (error == 0)
        error = uv_run(loop, UV_RUN_DEFAULT);
    else
        ERR("uv_tcp_connect failed: %s(%s)", uv_strerror(error), uv_err_name(error));

    uv_close(connect, NULL);
    free(connect);
    free(socket);
    uv_loop_close(loop);
    free(loop);

    return error;
}


// References:
// https://github.com/nikhilm/uvbook/blob/master/code/dns/main.c
