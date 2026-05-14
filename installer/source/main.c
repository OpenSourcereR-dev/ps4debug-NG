// SPDX-License-Identifier: GPL-3.0-only

#include "syscall.h"
#include "installer.h"

int _main(void) {
    return syscall(11, runinstaller);
}
