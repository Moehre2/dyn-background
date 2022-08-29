#include <stdint.h>

#ifndef RENDER_H
#define RENDER_H

typedef struct {
    uint8_t r, g, b;
} rgb;

typedef struct {
    rgb top, bottom;
} background;

#endif
