#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "render.h"

static background backgrounds[NUM_OF_BACKGROUNDS] = {
    {
        .top    = { .r =   0, .g =  33, .b =  81 },
        .bottom = { .r =   0, .g =  19, .b =  32 }
    },
    {
        .top    = { .r =   0, .g =  50, .b = 102 },
        .bottom = { .r =   0, .g =  20, .b =  31 }
    },
    {
        .top    = { .r =   0, .g =  58, .b = 103 },
        .bottom = { .r =   1, .g =  23, .b =  37 }
    },
    {
        .top    = { .r =   0, .g =  58, .b = 103 },
        .bottom = { .r =   1, .g =  27, .b =  45 }
    },
    {
        .top    = { .r =   1, .g =  92, .b = 134 },
        .bottom = { .r =   1, .g =  23, .b =  37 }
    },
    {
        .top    = { .r =   8, .g = 103, .b = 148 },
        .bottom = { .r =   5, .g =  39, .b =  62 }
    },
    {
        .top    = { .r =  19, .g = 151, .b = 183 },
        .bottom = { .r =   9, .g =  71, .b =  99 }
    },
    {
        .top    = { .r = 105, .g = 206, .b = 196 },
        .bottom = { .r =  19, .g = 123, .b = 155 }
    },
    {
        .top    = { .r = 235, .g = 235, .b = 179 },
        .bottom = { .r =  87, .g = 202, .b = 201 }
    },
    {
        .top    = { .r = 253, .g = 220, .b =  74 },
        .bottom = { .r = 149, .g = 209, .b = 191 }
    },
    {
        .top    = { .r = 252, .g = 187, .b =  72 },
        .bottom = { .r = 229, .g = 234, .b = 136 }
    },
    {
        .top    = { .r = 255, .g = 163, .b = 101 },
        .bottom = { .r = 255, .g = 224, .b =  92 }
    },
    {
        .top    = { .r = 251, .g = 156, .b =  80 },
        .bottom = { .r = 255, .g = 224, .b =  92 }
    },
    {
        .top    = { .r = 252, .g = 147, .b =  77 },
        .bottom = { .r = 255, .g = 224, .b =  92 }
    },
    {
        .top    = { .r = 239, .g = 121, .b =  64 },
        .bottom = { .r = 255, .g = 206, .b =  87 }
    },
    {
        .top    = { .r = 238, .g =  96, .b = 115 },
        .bottom = { .r = 248, .g = 158, .b =  77 }
    },
    {
        .top    = { .r = 195, .g =  80, .b = 135 },
        .bottom = { .r = 243, .g = 126, .b =  96 }
    },
    {
        .top    = { .r =  80, .g =  39, .b = 119 },
        .bottom = { .r = 203, .g =  87, .b = 128 }
    },
    {
        .top    = { .r =  48, .g =  24, .b = 108 },
        .bottom = { .r = 102, .g =  48, .b = 121 }
    },
    {
        .top    = { .r =  36, .g =  22, .b =  95 },
        .bottom = { .r =  61, .g =  30, .b = 112 }
    },
    {
        .top    = { .r =  24, .g =  36, .b =  86 },
        .bottom = { .r =  48, .g =  29, .b = 104 }
    },
    {
        .top    = { .r =   6, .g =  14, .b =  54 },
        .bottom = { .r =  32, .g =  43, .b = 103 }
    },
    {
        .top    = { .r =   6, .g =  14, .b =  54 },
        .bottom = { .r =   1, .g =  33, .b =  79 }
    }
};

int getBgIndex(void) {
    const int minutesPerDay = 1440;
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return ((timeinfo->tm_hour * 60 + timeinfo->tm_min) * NUM_OF_BACKGROUNDS) / minutesPerDay;
}

int exists(const char *path, const char *filename) {
    char *filepath;
    int res;

    filepath = (char *) malloc(strlen(path) + strlen(filename) + 1);
    strcpy(filepath, path);
    strcat(filepath, "/");
    strcat(filepath, filename);
    res = access(filepath, X_OK);
    free(filepath);
    return (res != -1);
}

int which(char *command, char *outputpath) {
    char *paths;
    int i, j;

    paths = getenv("PATH");
    strcpy(outputpath, paths);
    for(i = 0, j = 0; *(paths + i) != '\0'; i++, j++) {
        if(*(paths + i) == ':') {
            *(outputpath + j) = '\0';
            if(exists(outputpath, command)) {
                strcpy(outputpath, "/");
                strcat(outputpath, command);
                return 1;
            }
            j = -1;
        } else
            *(outputpath + j) = *(outputpath + i);
    }
    return 0;
}

int render_render(char *outputfile, uint width, uint height) {
    FILE *fp;
    int bgIndex;

    bgIndex = getBgIndex();
    fp = fopen(outputfile, "w+");
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><svg width=\"%d\" height=\"%d\"><defs><linearGradient id=\"grad1\" x1=\"0%%\" y1=\"0%%\" x2=\"0%%\" y2=\"100%%\">", width, height);
    fprintf(fp, "<stop offset=\"0%%\" style=\"stop-color:rgb(%d,%d,%d);stop-opacity:1\" />", backgrounds[bgIndex].top.r, backgrounds[bgIndex].top.g, backgrounds[bgIndex].top.b);
    fprintf(fp, "<stop offset=\"100%%\" style=\"stop-color:rgb(%d,%d,%d);stop-opacity:1\" />", backgrounds[bgIndex].bottom.r, backgrounds[bgIndex].bottom.g, backgrounds[bgIndex].bottom.b);
    fprintf(fp, "</linearGradient></defs><rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"url(#grad1)\" /></svg>", width, height);
    fclose(fp);
    return 1;
}

int render_setWallpaper(char *outputfile) {
    size_t filepathLength = strlen(getenv("PATH")) + 11;
    char *filepath = malloc(filepathLength);
    char *outputuri = malloc(strlen(outputfile) + 8);
    strcpy(outputuri, "file://");
    strcat(outputuri, outputfile);
    which("gsettings", filepath);
    char *args[] = {filepath, "set", "org.gnome.desktop.background", "picture-uri", outputuri, NULL};
    int res = execve(filepath, args, __environ);
    free(outputuri);
    free(filepath);
    return res;
}
