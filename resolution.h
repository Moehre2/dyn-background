#include <sys/types.h>

#ifndef RESOLUTION_H
#define RESOLUTION_H

typedef struct {
    uint width, height;
} resolution;

int resolution_getResolution(resolution *res);

#endif
