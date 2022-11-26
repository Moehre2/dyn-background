#include <stdio.h>
#include "resolution.h"
#include "render.h"

int main(int argc, char **argv) {
    char *outputfile = "/home/moritz/.config/dyn-background.svg";
    resolution res;

    if(!resolution_getResolution(&res)) {
        fprintf(stderr, "Error: Cannot get display size\n");
        return 1;
    }
    if(!render_render(outputfile, res.width, res.height)) {
        fprintf(stderr, "Error: Render failed\n");
        return 1;
    }
    printf("Rendered!\n");
    if(!render_setWallpaper(outputfile)) {
        fprintf(stderr, "Error: Cannot set wallpaper");
        return 1;
    }
    return 0;
}
