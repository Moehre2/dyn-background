#include <stdio.h>
#include "resolution.h"

int main(int argc, char **argv) {
    resolution res;
    if(resolution_getResolution(&res))
        printf("%dx%d\n", res.width, res.height);
    else
        fprintf(stderr, "Error: Cannot get display size");
    return 0;
}
