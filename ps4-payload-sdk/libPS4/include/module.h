#ifndef MODULE_H
#define MODULE_H

#include "types.h"

#define RESOLVE(module, name) getFunctionAddressByName(module, #name, &name)

struct moduleInfo {
  size_t size;
  char name[32];
  char padding1[0xe0];
  void *codeBase;
  unsigned int codeSize;
  void *dataBase;
  unsigned int dataSize;
  char padding2[0x3c];
};

extern int (*sceSysmoduleLoadModule)(int id);

int getFunctionAddressByName(int loadedModuleID, char *name, void *destination);
int getLoadedModules(int *destination, int max, int *count);
int getModuleInfo(int loadedModuleID, struct moduleInfo *destination);
int loadModule(const char *name, int *idDestination);
int unloadModule(int id);

void initModule(void);

#endif
