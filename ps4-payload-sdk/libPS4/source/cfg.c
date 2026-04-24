
#include "cfg.h"

#define MAX_NAME 50

#define EOF '\00'

static inline int fgetc_file(FILE* fp) {
  char c;
  if (fread(&c, 1, 1, fp) == 0) {
    return (EOF);
  }
  return (c);
}

static char* fgets(char* dst, int max, FILE* fp) {
  int c = EOF;
  char* p;

  for (p = dst, max--; max > 0; max--) {
    if ((c = fgetc_file(fp)) == EOF) {
      break;
    }
    *p++ = c;
    if (c == '\n') {
      break;
    }
  }
  *p = 0;
  if (p == dst || c == EOF) {
    return NULL;
  }
  return (p);
}

bool isspace(int c) {
  return c == ' ' || c == '\t';
}

typedef struct {
  const char* ptr;
  size_t num_left;
} cfg_parse_string_ctx;

static char* rstrip(char* s) {
  char* p = s + strlen(s);
  while (p > s && isspace((unsigned char)(*--p))) {
    *p = '\0';
  }
  return s;
}

static char* lskip(const char* s) {
  while (*s && isspace((unsigned char)(*s))) {
    s++;
  }
  return (char*)s;
}

static char* find_chars_or_comment(const char* s, const char* chars) {
#if CFG_ALLOW_INLINE_COMMENTS
  int was_space = 0;
  while (*s && (!chars || !strchr(chars, *s)) && !(was_space && strchr(CFG_INLINE_COMMENT_PREFIXES, *s))) {
    was_space = isspace((unsigned char)(*s));
    s++;
  }
#else
  while (*s && (!chars || !strchr(chars, *s))) {
    s++;
  }
#endif
  return (char*)s;
}

static char* strncpy0(char* dest, const char* src, size_t size) {
  strncpy(dest, src, size);
  dest[size - 1] = '\0';
  return dest;
}

int cfg_parse_stream(cfg_reader reader, void* stream, cfg_handler handler, void* user) {

#if CFG_USE_STACK
  char line[CFG_MAX_LINE];
  int max_line = CFG_MAX_LINE;
#else
  char* line;
  int max_line = CFG_INITIAL_ALLOC;
#endif
#if CFG_ALLOW_REALLOC
  char* new_line;
  int offset;
#endif
  char prev_name[MAX_NAME] = "";

  char* start;
  char* end;
  char* name;
  char* value;
  int lineno = 0;
  int error = 0;

#if !CFG_USE_STACK
  line = (char*)malloc(CFG_INITIAL_ALLOC);
  if (!line) {
    return -2;
  }
#endif

#if CFG_HANDLER_LINENO
#define HANDLER(u, n, v) handler(u, n, v, lineno)
#else
#define HANDLER(u, n, v) handler(u, n, v)
#endif

  while (reader(line, max_line, stream) != NULL) {
#if CFG_ALLOW_REALLOC
    offset = strlen(line);
    while (offset == max_line - 1 && line[offset - 1] != '\n') {
      max_line *= 2;
      if (max_line > CFG_MAX_LINE) {
        max_line = CFG_MAX_LINE;
      }
      new_line = realloc(line, max_line);
      if (!new_line) {
        free(line);
        return -2;
      }
      line = new_line;
      if (reader(line + offset, max_line - offset, stream) == NULL) {
        break;
      }
      if (max_line >= CFG_MAX_LINE) {
        break;
      }
      offset += strlen(line + offset);
    }
#endif

    lineno++;

    start = line;
#if CFG_ALLOW_BOM
    if (lineno == 1 && (unsigned char)start[0] == 0xEF && (unsigned char)start[1] == 0xBB && (unsigned char)start[2] == 0xBF) {
      start += 3;
    }
#endif
    start = lskip(rstrip(start));

    if (*start == ';' || *start == '#') {

    }
#if CFG_ALLOW_MULTILINE
    else if (*prev_name && *start && start > line) {

      if (!HANDLER(user, prev_name, start) && !error)
        error = lineno;
    }
#endif
    else if (*start) {

      end = find_chars_or_comment(start, "=:");
      if (*end == '=' || *end == ':') {
        *end = '\0';
        name = rstrip(start);
        value = end + 1;
#if CFG_ALLOW_INLINE_COMMENTS
        end = find_chars_or_comment(value, NULL);
        if (*end) {
          *end = '\0';
        }
#endif
        value = lskip(value);
        rstrip(value);

        strncpy0(prev_name, name, sizeof(prev_name));
        if (!HANDLER(user, name, value) && !error) {
          error = lineno;
        }
      } else if (!error) {

        error = lineno;
      }
    }

#if CFG_STOP_ON_FIRST_ERROR
    if (error) {
      break;
    }
#endif
  }

#if !CFG_USE_STACK
  free(line);
#endif

  return error;
}

int cfg_parse_file(FILE* file, cfg_handler handler, void* user) {
  return cfg_parse_stream((cfg_reader)fgets, file, handler, user);
}

int cfg_parse(const char* filename, cfg_handler handler, void* user) {
  FILE* file;
  int error;

  file = fopen(filename, "r");
  if (!file) {
    return -1;
  }
  error = cfg_parse_file(file, handler, user);
  fclose(file);
  return error;
}

static char* cfg_reader_string(char* str, int num, void* stream) {
  cfg_parse_string_ctx* ctx = (cfg_parse_string_ctx*)stream;
  const char* ctx_ptr = ctx->ptr;
  size_t ctx_num_left = ctx->num_left;
  char* strp = str;
  char c;

  if (ctx_num_left == 0 || num < 2) {
    return NULL;
  }

  while (num > 1 && ctx_num_left != 0) {
    c = *ctx_ptr++;
    ctx_num_left--;
    *strp++ = c;
    if (c == '\n') {
      break;
    }
    num--;
  }

  *strp = '\0';
  ctx->ptr = ctx_ptr;
  ctx->num_left = ctx_num_left;
  return str;
}

int cfg_parse_string(const char* string, cfg_handler handler, void* user) {
  cfg_parse_string_ctx ctx;

  ctx.ptr = string;
  ctx.num_left = strlen(string);
  return cfg_parse_stream((cfg_reader)cfg_reader_string, &ctx, handler, user);
}
