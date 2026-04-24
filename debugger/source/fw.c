
#include <ps4.h>
#include "fw.h"

uint16_t get_fw_version(void) {
    static uint16_t cached = 0;
    if (cached) {
        return cached;
    }

    SceKernelSystemSwVersion info;
    memset(&info, 0, sizeof(info));
    info.size = sizeof(info);

    if (sceKernelGetSystemSwVersion(&info) != 0) {
        return (uint16_t)-1;
    }

    uint32_t v = info.version;
    uint8_t major_byte = (uint8_t)((v >> 24) & 0xFF);
    uint8_t minor_byte = (uint8_t)((v >> 16) & 0xFF);
    uint8_t major = (uint8_t)(((major_byte >> 4) & 0x0F) * 10 + (major_byte & 0x0F));
    uint8_t minor = (uint8_t)(((minor_byte >> 4) & 0x0F) * 10 + (minor_byte & 0x0F));

    cached = (uint16_t)(major * 100 + minor);
    return cached;
}
