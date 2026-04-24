
#ifndef CFG_H
#define CFG_H

#include "libc.h"

#ifndef CFG_HANDLER_LINENO
#define CFG_HANDLER_LINENO 0
#endif

#if CFG_HANDLER_LINENO
typedef int (*cfg_handler)(void* user, const char* name, const char* value, int lineno);
#else
typedef int (*cfg_handler)(void* user, const char* name, const char* value);
#endif

typedef char* (*cfg_reader)(char* str, int num, void* stream);

int cfg_parse(const char* filename, cfg_handler handler, void* user);

int cfg_parse_file(FILE* file, cfg_handler handler, void* user);

int cfg_parse_stream(cfg_reader reader, void* stream, cfg_handler handler, void* user);

int cfg_parse_string(const char* string, cfg_handler handler, void* user);

#ifndef CFG_ALLOW_MULTILINE
#define CFG_ALLOW_MULTILINE 0
#endif

#ifndef CFG_ALLOW_BOM
#define CFG_ALLOW_BOM 0
#endif

#ifndef CFG_ALLOW_INLINE_COMMENTS
#define CFG_ALLOW_INLINE_COMMENTS 1
#endif
#ifndef CFG_INLINE_COMMENT_PREFIXES
#define CFG_INLINE_COMMENT_PREFIXES ";"
#endif

#ifndef CFG_USE_STACK
#define CFG_USE_STACK 1
#endif

#ifndef CFG_MAX_LINE
#define CFG_MAX_LINE 200
#endif

#ifndef CFG_ALLOW_REALLOC
#define CFG_ALLOW_REALLOC 0
#endif

#ifndef CFG_INITIAL_ALLOC
#define CFG_INITIAL_ALLOC 200
#endif

#ifndef CFG_STOP_ON_FIRST_ERROR
#define CFG_STOP_ON_FIRST_ERROR 0
#endif

#endif
