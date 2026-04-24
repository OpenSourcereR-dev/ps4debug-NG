
#ifndef BASE64_H
#define BASE64_H

#include "types.h"
#include "libc.h"

unsigned char *base64_encode(const unsigned char *src, size_t len, size_t *out_len);
unsigned char *base64_decode(const unsigned char *src, size_t len, size_t *out_len);

#endif
