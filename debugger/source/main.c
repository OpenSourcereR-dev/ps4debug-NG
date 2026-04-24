
#include <ps4.h>
#include "ptrace.h"
#include "server.h"
#include "debug.h"
#include "protocol.h"
#include "net.h"

int _main(void) {

    initKernel();
    initLibc();
    initPthread();
    initNetwork();
    initSysUtil();

    sceKernelSleep(2);

    sys_console_cmd(SYS_CONSOLE_CMD_JAILBREAK, NULL);

    mkdir("/update/PS4UPDATE.PUP", 0777);
    mkdir("/update/PS4UPDATE.PUP.net.temp", 0777);

    int retry = 0;
    char ip_buf[16];

    while (1) {
        memset(ip_buf, 0, sizeof(ip_buf));
        net_get_ip_address(ip_buf);

        if (strlen(ip_buf) > 4) {

            sceSysUtilSendSystemNotificationWithText(222, "ps4debug-NG by OSR v1.2.1\nBased on source by golden\n\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0Inspired by\nCtn, SiSTRo & DeathRGH\n\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xC2\xA0\xE2\x9D\xA4\xE2\x9D\xA4\xE2\x9D\xA4\xE2\x9D\xA4");
            retry = 0;
            start_server();
            continue;
        }

        int next = retry + 1;
        if (retry == 0) {

            sceSysUtilSendSystemNotificationWithText(222, "ps4debug-ng by OpenSourcerer v1.2.1 disconnected.");
            sceKernelSleep(2);
        } else if (next <= 99) {
            sceKernelSleep(2);
        } else {
            sceKernelSleep(1000);
        }
        retry = next;
    }

    return 0;
}