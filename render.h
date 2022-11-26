#include <stdint.h>
#include <sys/types.h>

#ifndef RENDER_H
#define RENDER_H

#define NUM_OF_BACKGROUNDS 23

typedef struct {
    uint8_t r, g, b;
} rgb;

typedef struct {
    rgb top, bottom;
} background;

int render_render(char *outputfile, uint width, uint height);
int render_setWallpaper(char *outputfile);

#endif
