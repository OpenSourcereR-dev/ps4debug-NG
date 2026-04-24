
#include "debug.h"
#include "console.h"

int g_debugging;
struct server_client *curdbgcli;
struct debug_context *curdbgctx;

ScePthreadMutex g_debug_mutex;
int g_stepping_lwpid;

int connect_debugger(struct debug_context *dbgctx, struct sockaddr_in *client) {
    struct sockaddr_in server;
    int r;

    g_debugging = 1;

    server.sin_len = sizeof(server);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = client->sin_addr.s_addr;
    server.sin_port = sceNetHtons(DEBUG_PORT);
    memset(server.sin_zero, NULL, sizeof(server.sin_zero));

    dbgctx->dbgfd = sceNetSocket("interrupt", AF_INET, SOCK_STREAM, 0);
    if(dbgctx->dbgfd <= 0) {
        return 1;
    }

    r = sceNetConnect(dbgctx->dbgfd, (struct sockaddr *)&server, sizeof(server));
    if(r) {
        return 1;
    }

    return 0;
}

void debug_cleanup(struct debug_context *dbgctx) {

    if (curdbgcli) {
        curdbgcli->debugging = 0;
    }
    g_debugging = 0;
    curdbgcli = NULL;
    curdbgctx = NULL;

    if (dbgctx && dbgctx->dbgfd > 0) {
        sceNetSocketClose(dbgctx->dbgfd);
        dbgctx->dbgfd = 0;
    }
}

int console_print_handle(int fd, struct cmd_packet *packet) {
    uint32_t *lenp;
    uint32_t length;
    void *data;

    lenp = (uint32_t *)packet->data;
    if (!lenp) {
        net_send_int32(fd, CMD_DATA_NULL);
        return 1;
    }

    length = *lenp;
    data = net_alloc_buffer(length);
    if (!data) {
        net_send_int32(fd, CMD_DATA_NULL);
        return 1;
    }

    memset(data, NULL, length);
    net_recv_all(fd, data, length, 1);
    syscall(112, 2, data);
    net_send_int32(fd, CMD_SUCCESS);
    free(data);
    return 0;
}

int console_notify_handle(int fd, struct cmd_packet *packet) {
    struct cmd_console_notify_packet *np;
    void *data;

    np = (struct cmd_console_notify_packet *)packet->data;
    if (!np) {
        net_send_int32(fd, CMD_DATA_NULL);
        return 1;
    }

    data = net_alloc_buffer(np->length);
    if (!data) {
        net_send_int32(fd, CMD_DATA_NULL);
        return 1;
    }

    memset(data, NULL, np->length);
    net_recv_all(fd, data, np->length, 1);
    sceSysUtilSendSystemNotificationWithText(np->messageType, data);
    net_send_int32(fd, CMD_SUCCESS);
    free(data);
    return 0;
}

int console_reboot_handle(int fd, struct cmd_packet *packet) {
    if (g_debugging) {
        debug_cleanup(curdbgctx);
        sceNetSocketClose(fd);
    }
    syscall(112, 1, 0);

    return 1;
}

int console_handle(int fd, struct cmd_packet *packet) {
    switch(packet->cmd) {
        case CMD_CONSOLE_REBOOT:
            return console_reboot_handle(fd, packet);
        case CMD_CONSOLE_PRINT:
            return console_print_handle(fd, packet);
        case CMD_CONSOLE_NOTIFY:
            return console_notify_handle(fd, packet);
        case CMD_CONSOLE_INFO:

            net_send_int32(fd, CMD_SUCCESS);
            return 0;
        case CMD_CONSOLE_END:

            return 1;
    }

    return 1;
}
