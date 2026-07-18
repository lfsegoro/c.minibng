#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "http.h"

static int g_port;

static void *http_server(void *arg)
{
    (void)arg;

    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return NULL;
    }

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(g_port);

    if (bind(server_fd,
             (struct sockaddr *)&addr,
             sizeof(addr)) < 0) {

        perror("bind");

        close(server_fd);

        return NULL;
    }

    if (listen(server_fd, 10) < 0) {

        perror("listen");

        close(server_fd);

        return NULL;
    }

    printf("[HTTP] Listening on port %d\n", g_port);

    while (1) {

        sleep(60);
    }

    close(server_fd);

    return NULL;
}

void http_start(int port)
{
    pthread_t tid;

    g_port = port;

    pthread_create(&tid,
                   NULL,
                   http_server,
                   NULL);

    pthread_detach(tid);
}