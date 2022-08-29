#include <sys/types.h>

#define XRANDR "xrandr"
#define PATH_LENGTH 512
#define XRANDR_OUTPUT_LENGTH 4096

typedef struct {
    uint width, height;
} resolution;

int resolution_getResolution(resolution *res);
