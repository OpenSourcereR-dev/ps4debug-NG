
#ifndef _PTRACE_H
#define _PTRACE_H

#include <ps4.h>
#include "sparse.h"
#include "kdbg.h"

#define	PT_TRACE_ME	0
#define	PT_READ_I	1
#define	PT_READ_D	2

#define	PT_WRITE_I	4
#define	PT_WRITE_D	5

#define	PT_CONTINUE	7
#define	PT_KILL		8
#define	PT_STEP		9
#define	PT_ATTACH	10
#define	PT_DETACH	11
#define PT_IO		12
#define	PT_LWPINFO	13
#define PT_GETNUMLWPS	14
#define PT_GETLWPLIST	15
#define PT_CLEARSTEP	16
#define PT_SETSTEP	17
#define PT_SUSPEND	18
#define PT_RESUME	19
#define	PT_TO_SCE	20
#define	PT_TO_SCX	21
#define	PT_SYSCALL	22
#define	PT_FOLLOW_FORK	23
#define PT_GETREGS      33
#define PT_SETREGS      34
#define PT_GETFPREGS    35
#define PT_SETFPREGS    36
#define PT_GETDBREGS    37
#define PT_SETDBREGS    38
#define	PT_VM_TIMESTAMP	40
#define	PT_VM_ENTRY     41

#define __LOW(v)	((v) & 0377)
#define __HIGH(v)	(((v) >> 8) & 0377)

#define WNOHANG         1
#define WUNTRACED       2

#define WIFEXITED(s)	(__LOW(s) == 0)
#define WEXITSTATUS(s)	(__HIGH(s))
#define WTERMSIG(s)	(__LOW(s) & 0177)
#define WIFSIGNALED(s)	((((unsigned int)(s)-1) & 0xFFFF) < 0xFF)
#define WIFSTOPPED(s) (__LOW(s) == 0177)
#define WSTOPSIG(s)	(__HIGH(s) & 0377)

#define	SIGHUP	1
#define	SIGINT	2
#define	SIGQUIT	3
#define	SIGILL	4
#define	SIGTRAP	5
#define	SIGABRT	6
#define	SIGIOT	SIGABRT
#define	SIGEMT	7
#define	SIGFPE	8
#define	SIGKILL	9
#define	SIGBUS	10
#define	SIGSEGV	11
#define	SIGSYS	12
#define	SIGPIPE	13
#define	SIGALRM	14
#define	SIGTERM	15
#define	SIGURG	16
#define	SIGSTOP	17
#define	SIGTSTP	18
#define	SIGCONT	19
#define	SIGCHLD	20
#define	SIGTTIN	21
#define	SIGTTOU	22
#define	SIGIO	23
#define	SIGXCPU	24
#define	SIGXFSZ	25
#define	SIGVTALRM 26
#define	SIGPROF	27
#define SIGWINCH 28
#define SIGINFO	29
#define SIGUSR1 30
#define SIGUSR2 31

struct ptrace_io_desc {
    int	piod_op;
    void *piod_offs;
    void *piod_addr;
    uint64_t piod_len;
};

TYPE_BEGIN(struct ptrace_lwpinfo, 0x98);
TYPE_FIELD(uint32_t pl_lwpid, 0);
TYPE_FIELD(char pl_tdname[24], 0x80);
TYPE_END();

int ptrace(int req, int pid, void *addr, int data);
int wait4(int wpid, int *status, int options, void *rusage);

#endif
