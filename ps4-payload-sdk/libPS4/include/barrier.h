// SPDX-License-Identifier: GPL-3.0-only

#ifndef BARRIER_H
#define BARRIER_H

int mutexInit(const char *name, unsigned int attributes);
int mutexDestroy(int mutex);

#endif
