#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

typedef struct SceCameraStartParameter {
  uint32_t size;
  uint32_t unknown1;
  uint32_t unknown2;
  void *unknown3;
} SceCameraStartParameter;

typedef struct SceCameraFrameData {
  uint32_t size;
  uint32_t unknown1;
  uint32_t unknown2[32];
  void *pleft[4];
  void *pright[4];
  uint32_t sizeleft[4];
  uint32_t sizeright[4];
  uint32_t statusleft;
  uint32_t statusright;
  uint32_t unknown3[70];
} SceCameraFrameData;

typedef struct SceCameraDeviceInfo {
  uint32_t size;
  uint32_t revision;
  uint32_t unknown1;
  uint32_t unknown2;
} SceCameraDeviceInfo;

typedef struct SceCameraConfig {
  uint32_t size;
  uint32_t unknown[100];
} SceCameraConfig;

extern int (*sceCameraOpen)(int userid, int type, int index, void *);
extern int (*sceCameraClose)(int handle);
extern int (*sceCameraIsAttached)(int index);
extern int (*sceCameraGetFrameData)(int handle, SceCameraFrameData *frame);
extern int (*sceCameraStart)(int handle, SceCameraStartParameter *param);
extern int (*sceCameraStop)(int handle);
extern int (*sceCameraGetDeviceInfo)(int handle, SceCameraDeviceInfo *info);
extern int (*sceCameraGetDeviceConfig)(int handle, SceCameraConfig *config);
extern int (*sceCameraGetConfig)(int handle, SceCameraConfig *config);
extern int (*sceCameraSetConfig)(int handle, SceCameraConfig *config);

void initCamera(void);

#endif
