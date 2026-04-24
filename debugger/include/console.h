
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <ps4.h>
#include "protocol.h"
#include "net.h"
#include "debug.h"

int kern_base_handle(int fd, struct cmd_packet *packet);
int kern_read_handle(int fd, struct cmd_packet *packet);
int kern_write_handle(int fd, struct cmd_packet *packet);

int kern_handle(int fd, struct cmd_packet *packet);

#endif
