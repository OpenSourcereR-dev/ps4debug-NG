// SPDX-License-Identifier: GPL-3.0-only

#include "kernel.h"
#include "module.h"

#include "libc.h"

static void  *(*_p_malloc)(size_t);
static void   (*_p_free)(void *);
static void  *(*_p_calloc)(size_t, size_t);
static void  *(*_p_realloc)(void *, size_t);
static void  *(*_p_memalign)(size_t, size_t);
static void  *(*_p_memset)(void *, int, size_t);
static void  *(*_p_memcpy)(void *, const void *, size_t);
static void  *(*_p_memmove)(void *, const void *, size_t);
static int    (*_p_memcmp)(const void *, const void *, size_t);
static char  *(*_p_strcpy)(char *, const char *);
static char  *(*_p_strncpy)(char *, const char *, size_t);
static char  *(*_p_strcat)(char *, const char *);
static char  *(*_p_strncat)(char *, const char *, size_t);
static size_t (*_p_strlen)(const char *);
static int    (*_p_strcmp)(const char *, const char *);
static int    (*_p_strncmp)(const char *, const char *, size_t);
static char  *(*_p_strchr)(const char *, int);
static char  *(*_p_strrchr)(const char *, int);
static char  *(*_p_strstr)(const char *, const char *);
static char  *(*_p_strerror)(int);
static void   (*_p_bcopy)(const void *, void *, size_t);
static unsigned long long (*_p_strtoull)(const char *, char **, int);
static int    (*_p_vsnprintf)(char *, size_t, const char *, va_list);
static int    (*_p_vsscanf)(const char *, const char *, va_list);

char *(*strtok)(char *restrict s1, const char *restrict s2);
char *(*strdup)(const char *s);
char *(*index)(const char *s, int c);
char *(*rindex)(const char *s, int c);
int (*isdigit)(int c);
int (*atoi)(const char *s);
size_t (*strlcpy)(char *dst, const char *src, size_t size);
void *(*_Getpctype)();
unsigned long (*_Stoul)(const char *, char **, int);

void (*srand)(unsigned int seed);
int (*rand)(void);

char *(*asctime)(const struct tm *tm);
char *(*asctime_r)(const struct tm *tm, char *buf);
char *(*ctime)(const time_t *timep);
char *(*ctime_r)(const time_t *timep, char *buf);
time_t (*time)(time_t *tloc);
struct tm *(*gmtime)(const time_t *timep);
struct tm *(*gmtime_s)(const time_t *timep, struct tm *result);
struct tm *(*localtime)(const time_t *timep);
struct tm *(*localtime_r)(const time_t *timep, struct tm *result);
time_t (*mktime)(struct tm *tm);

DIR *(*opendir)(const char *filename);
struct dirent *(*readdir)(DIR *dirp);
int (*readdir_r)(DIR *dirp, struct dirent *entry, struct dirent **result);
long (*telldir)(const DIR *dirp);
void (*seekdir)(DIR *dirp, long loc);
void (*rewinddir)(DIR *dirp);
int (*closedir)(DIR *dirp);
int (*dirfd)(DIR *dirp);
char *(*getprogname)();

FILE *(*fopen)(const char *filename, const char *mode);
size_t (*fread)(void *ptr, size_t size, size_t count, FILE *stream);
size_t (*fwrite)(const void *ptr, size_t size, size_t count, FILE *stream);
int (*fseek)(FILE *stream, long int offset, int origin);
long int (*ftell)(FILE *stream);
int (*fclose)(FILE *stream);
int (*fprintf)(FILE *stream, const char *format, ...);

void  *malloc(size_t n)                          { return _p_malloc(n); }
void   free(void *p)                             { _p_free(p); }
void  *calloc(size_t n, size_t s)                { return _p_calloc(n, s); }
void  *realloc(void *p, size_t s)                { return _p_realloc(p, s); }
void  *memalign(size_t a, size_t s)              { return _p_memalign(a, s); }
void  *memset(void *d, int v, size_t n)          { return _p_memset(d, v, n); }
void  *memcpy(void *d, const void *s, size_t n)  { return _p_memcpy(d, s, n); }
void  *memmove(void *d, const void *s, size_t n) { return _p_memmove(d, s, n); }
int    memcmp(const void *a, const void *b, size_t n) { return _p_memcmp(a, b, n); }
char  *strcpy(char *d, const char *s)            { return _p_strcpy(d, s); }
char  *strncpy(char *d, const char *s, size_t n) { return _p_strncpy(d, s, n); }
char  *strcat(char *d, const char *s)            { return _p_strcat(d, s); }
char  *strncat(char *d, const char *s, size_t n) { return _p_strncat(d, s, n); }
size_t strlen(const char *s)                     { return _p_strlen(s); }
int    strcmp(const char *a, const char *b)      { return _p_strcmp(a, b); }
int    strncmp(const char *a, const char *b, size_t n) { return _p_strncmp(a, b, n); }
char  *strchr(const char *s, int c)              { return _p_strchr(s, c); }
char  *strrchr(const char *s, int c)             { return _p_strrchr(s, c); }
char  *strstr(const char *a, const char *b)      { return _p_strstr(a, b); }
char  *strerror(int e)                           { return _p_strerror(e); }
void   bcopy(const void *s, void *d, size_t n)   { _p_bcopy(s, d, n); }
unsigned long long int strtoull(const char *s, char **e, int b) { return _p_strtoull(s, e, b); }

int vsnprintf(char *s, size_t n, const char *f, va_list ap) { return _p_vsnprintf(s, n, f, ap); }
int vsscanf(const char *s, const char *f, va_list ap)       { return _p_vsscanf(s, f, ap); }
int snprintf(char *s, size_t n, const char *f, ...) {
  va_list ap; va_start(ap, f);
  int r = _p_vsnprintf(s, n, f, ap);
  va_end(ap);
  return r;
}
int sprintf(char *s, const char *f, ...) {
  va_list ap; va_start(ap, f);
  int r = _p_vsnprintf(s, (size_t)-1, f, ap);
  va_end(ap);
  return r;
}
int sscanf(const char *s, const char *f, ...) {
  va_list ap; va_start(ap, f);
  int r = _p_vsscanf(s, f, ap);
  va_end(ap);
  return r;
}

#define RESOLVE_P(module, name)      getFunctionAddressByName(module, #name, &_p_##name)
#define RESOLVE_AS(module, str, dst) getFunctionAddressByName(module, str, &(dst))

void initLibc(void) {
  int libc = sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, NULL, 0, 0, 0);

  RESOLVE_P(libc, malloc);
  RESOLVE_P(libc, free);
  RESOLVE_P(libc, calloc);
  RESOLVE_P(libc, realloc);
  RESOLVE_P(libc, memalign);
  RESOLVE_P(libc, memset);
  RESOLVE_P(libc, memcpy);
  RESOLVE_AS(libc, "memmove", _p_memmove);
  RESOLVE_P(libc, memcmp);
  RESOLVE_P(libc, strcpy);
  RESOLVE_P(libc, strncpy);
  RESOLVE_P(libc, strcat);
  RESOLVE_P(libc, strncat);
  RESOLVE_P(libc, strlen);
  RESOLVE_P(libc, strcmp);
  RESOLVE_P(libc, strncmp);
  RESOLVE_P(libc, strchr);
  RESOLVE_P(libc, strrchr);
  RESOLVE_P(libc, strstr);
  RESOLVE_P(libc, strerror);
  RESOLVE_P(libc, bcopy);
  RESOLVE_P(libc, strtoull);
  RESOLVE_AS(libc, "vsnprintf", _p_vsnprintf);
  RESOLVE_AS(libc, "vsscanf",   _p_vsscanf);

  RESOLVE(libc, strtok);
  RESOLVE(libc, strdup);
  RESOLVE(libc, index);
  RESOLVE(libc, rindex);
  RESOLVE(libc, isdigit);
  RESOLVE(libc, atoi);
  RESOLVE(libc, strlcpy);
  RESOLVE(libc, _Getpctype);
  RESOLVE(libc, _Stoul);

  RESOLVE(libc, srand);
  RESOLVE(libc, rand);

  RESOLVE(libc, asctime);
  RESOLVE(libc, asctime_r);
  RESOLVE(libc, ctime);
  RESOLVE(libc, ctime_r);
  RESOLVE(libc, time);
  RESOLVE(libc, gmtime);
  RESOLVE(libc, gmtime_s);
  RESOLVE(libc, localtime);
  RESOLVE(libc, localtime_r);
  RESOLVE(libc, mktime);

  RESOLVE(libc, opendir);
  RESOLVE(libc, readdir);
  RESOLVE(libc, readdir_r);
  RESOLVE(libc, telldir);
  RESOLVE(libc, seekdir);
  RESOLVE(libc, rewinddir);
  RESOLVE(libc, closedir);
  RESOLVE(libc, dirfd);

  RESOLVE(libc, getprogname);

  RESOLVE(libc, fopen);
  RESOLVE(libc, fread);
  RESOLVE(libc, fwrite);
  RESOLVE(libc, fseek);
  RESOLVE(libc, ftell);
  RESOLVE(libc, fclose);
  RESOLVE(libc, fprintf);
}
