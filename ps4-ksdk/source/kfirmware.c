
#include "kfirmware.h"

unsigned short cachedFirmware = 0;

unsigned short kget_firmware_from_base(uint64_t kernbase) {
    if (cachedFirmware) {
        return cachedFirmware;
    }

    const uint8_t *p   = (const uint8_t *)(kernbase + 0x1300000);
    const uint8_t *end = (const uint8_t *)(kernbase + 0x2200000);

    for (; p < end; ++p) {
        if (p[0] == 's' && p[1] == '/' && p[2] == 'r' && p[3] == 'e' &&
            p[4] == 'l' && p[5] == 'e' && p[6] == 'a' && p[7] == 's' &&
            p[8] == 'e' && p[9] == '_') {
            unsigned short v =
                (unsigned short)(1000U * (p[10] - '0') +
                                  100U * (p[11] - '0') +
                                   10U * (p[13] - '0') +
                                   1U  * (p[14] - '0'));
            cachedFirmware = v;
            return v;
        }
    }

    cachedFirmware = 0;
    return 0;
}
