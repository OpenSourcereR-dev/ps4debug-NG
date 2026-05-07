
#include "console.h"
#include "debug.h"

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
