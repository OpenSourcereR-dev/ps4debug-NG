// SPDX-License-Identifier: GPL-3.0-only

#include <ps4.h>
#include "protocol.h"
#include "net.h"
#include "proc.h"
#include <keystone/keystone.h>
#include <stdint.h>

static uint32_t bounded_strlen(const char *s, uint32_t max) {
    uint32_t n = 0;
    while (n < max && s[n]) n++;
    return n;
}

static void send_err(int fd, uint32_t ks_err_code) {
    const char *m = ks_strerror((ks_err)ks_err_code);
    if (!m) m = "(unknown keystone error)";
    uint32_t mlen = bounded_strlen(m, 255);
    net_send_int32(fd, CMD_ERROR);
    struct cmd_proc_assemble_err hdr = { ks_err_code, mlen };
    net_send_all(fd, &hdr, (int)sizeof(hdr));
    if (mlen) net_send_all(fd, (void *)m, (int)mlen);
}

int proc_assemble_handle(int fd, struct cmd_packet *packet) {
    if (!packet->data || packet->datalen < CMD_PROC_ASSEMBLE_HDR_SIZE) {
        net_send_int32(fd, CMD_DATA_NULL);
        return 1;
    }

    const uint8_t *d  = (const uint8_t *)packet->data;
    uint64_t base     = *(const uint64_t *)(d + 0);
    uint32_t syntax   = *(const uint32_t *)(d + 8);
    uint32_t text_len = packet->datalen - CMD_PROC_ASSEMBLE_HDR_SIZE;

    char *text = (char *)malloc((size_t)text_len + 1);
    if (!text) { net_send_int32(fd, CMD_DATA_NULL); return 1; }
    memcpy(text, d + CMD_PROC_ASSEMBLE_HDR_SIZE, text_len);
    text[text_len] = '\0';

    ks_engine *ks = NULL;
    ks_err err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
    if (err != KS_ERR_OK || ks == NULL) {
        free(text);
        send_err(fd, (uint32_t)err);
        return 1;
    }
    if (syntax != 0) {
        ks_option(ks, KS_OPT_SYNTAX, (size_t)syntax);
    }

    unsigned char *enc = NULL;
    size_t enc_size = 0, insn_count = 0;
    int rc = ks_asm(ks, text, base, &enc, &enc_size, &insn_count);
    free(text);

    if (rc != KS_ERR_OK) {
        ks_err e = ks_errno(ks);
        if (enc) ks_free(enc);
        ks_close(ks);
        send_err(fd, (uint32_t)e);
        return 1;
    }

    net_send_int32(fd, CMD_SUCCESS);
    struct cmd_proc_assemble_ok hdr = { (uint32_t)enc_size, (uint32_t)insn_count };
    net_send_all(fd, &hdr, (int)sizeof(hdr));
    if (enc_size) net_send_all(fd, enc, (int)enc_size);

    ks_free(enc);
    ks_close(ks);
    return 0;
}
