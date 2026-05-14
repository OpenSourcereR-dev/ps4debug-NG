// SPDX-License-Identifier: GPL-3.0-only

#ifndef LIBC_H
#define LIBC_H

#include "types.h"
#include "file.h"
#include <stdarg.h>

typedef struct DIR DIR;
typedef int FILE;

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

void  *malloc(size_t size);
void   free(void *ptr);
void  *calloc(size_t num, size_t size);
void  *realloc(void *ptr, size_t size);
void  *memalign(size_t boundary, size_t size);
void  *memset(void *destination, int value, size_t num);
void  *memcpy(void *destination, const void *source, size_t num);
void  *memmove(void *destination, const void *source, size_t num);
int    memcmp(const void *s1, const void *s2, size_t n);
char  *strcpy(char *destination, const char *source);
char  *strncpy(char *destination, const char *source, size_t num);
char  *strcat(char *dest, const char *src);
char  *strncat(char *dest, const char *src, size_t n);
size_t strlen(const char *s);
int    strcmp(const char *s1, const char *s2);
int    strncmp(const char *s1, const char *s2, size_t n);
char  *strchr(const char *s, int c);
char  *strrchr(const char *s, int c);
char  *strstr(const char *str1, const char *str2);
char  *strerror(int errnum);
void   bcopy(const void *s1, void *s2, size_t n);
unsigned long long int strtoull(const char *str, char **endptr, int base);
int    sprintf(char *str, const char *format, ...);
int    snprintf(char *str, size_t size, const char *format, ...);
int    vsnprintf(char *str, size_t size, const char *format, va_list ap);
int    sscanf(const char *str, const char *format, ...);
int    vsscanf(const char *str, const char *format, va_list ap);

extern char *(*strtok)(char *restrict s1, const char *restrict s2);
extern char *(*strdup)(const char *s);
extern char *(*index)(const char *s, int c);
extern char *(*rindex)(const char *s, int c);
extern int (*isdigit)(int c);
extern int (*atoi)(const char *s);
extern size_t (*strlcpy)(char *dst, const char *src, size_t size);
extern void *(*_Getpctype)();
extern unsigned long (*_Stoul)(const char *, char **, int);

extern void (*srand)(unsigned int seed);
extern int (*rand)(void);

extern char *(*asctime)(const struct tm *tm);
extern char *(*asctime_r)(const struct tm *tm, char *buf);
extern char *(*ctime)(const time_t *timep);
extern char *(*ctime_r)(const time_t *timep, char *buf);
extern time_t (*time)(time_t *tloc);
extern struct tm *(*gmtime)(const time_t *timep);
extern struct tm *(*gmtime_s)(const time_t *timep, struct tm *result);
extern struct tm *(*localtime)(const time_t *timep);
extern struct tm *(*localtime_r)(const time_t *timep, struct tm *result);
extern time_t (*mktime)(struct tm *tm);

extern DIR *(*opendir)(const char *filename);
extern struct dirent *(*readdir)(DIR *dirp);
extern int (*readdir_r)(DIR *dirp, struct dirent *entry, struct dirent **result);
extern long (*telldir)(const DIR *dirp);
extern void (*seekdir)(DIR *dirp, long loc);
extern void (*rewinddir)(DIR *dirp);
extern int (*closedir)(DIR *dirp);
extern int (*dirfd)(DIR *dirp);
extern char *(*getprogname)();

extern FILE *(*fopen)(const char *filename, const char *mode);
extern size_t (*fread)(void *ptr, size_t size, size_t count, FILE *stream);
extern size_t (*fwrite)(const void *ptr, size_t size, size_t count, FILE *stream);
extern int (*fseek)(FILE *stream, long int offset, int origin);
extern long int (*ftell)(FILE *stream);
extern int (*fclose)(FILE *stream);
extern int (*fprintf)(FILE *stream, const char *format, ...);

void initLibc(void);

#endif
