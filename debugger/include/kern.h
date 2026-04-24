
#ifndef _KERN_H
#define _KERN_H

#include <ps4.h>
#include "protocol.h"
#include "net.h"
#include "debug.h"

int debug_process_stop_handle(int fd, struct cmd_packet *packet);

int debug_attach_handle(int fd, struct cmd_packet *packet);
int debug_attach_handle_svc(struct server_client *svc, struct cmd_packet *packet);
int debug_detach_handle(int fd, struct cmd_packet *packet);

int dispatch_debug_events(void);

void debug_full_teardown(struct server_client *svc);
int debug_set_breakpoint_handle(int fd, struct cmd_packet *packet);
int debug_set_watchpoint_handle(int fd, struct cmd_packet *packet);
int debug_get_thread_list_handle(int fd, struct cmd_packet *packet);
int debug_suspend_thread_handle(int fd, struct cmd_packet *packet);
int debug_resume_thread_handle(int fd, struct cmd_packet *packet);
int debug_getregs_handle(int fd, struct cmd_packet *packet);
int debug_setregs_handle(int fd, struct cmd_packet *packet);
int debug_getfpregs_handle(int fd, struct cmd_packet *packet);
int debug_setfpregs_handle(int fd, struct cmd_packet *packet);
int debug_getdbregs_handle(int fd, struct cmd_packet *packet);
int debug_setdbregs_handle(int fd, struct cmd_packet *packet);
int debug_continue_handle(int fd, struct cmd_packet *packet);
int debug_thread_info_handle(int fd, struct cmd_packet *packet);
int debug_step_handle(int fd, struct cmd_packet *packet);
int debug_step_thread_handle(int fd, struct cmd_packet *packet);

int debug_handle(int fd, struct cmd_packet *packet);

extern int g_pending_sig_pid;
extern int g_pending_signal;

#endif
