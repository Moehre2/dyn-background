#include <stdio.h>
#include "resolution.h"
#include "render.h"

int main(int argc, char **argv) {
    resolution res;
    if(!resolution_getResolution(&res)) {
        fprintf(stderr, "Error: Cannot get display size\n");
        return 1;
    }
    render_render("/home/moritz/.config/dyn-background.svg", res.width, res.height);
    printf("Rendered!\n");
    return 0;
}
