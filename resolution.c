#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "resolution.h"

int xrandrExists(const char *path) {
    char xrandrPath[PATH_LENGTH];
    strcpy(xrandrPath, path);
    strcat(xrandrPath, "/");
    strcat(xrandrPath, XRANDR);
    return (access(xrandrPath, X_OK) != -1);
}

int checkAccessibility(void) {
    char *paths;
    char path[PATH_LENGTH];
    int i, j;
    paths = getenv("PATH");
    strcpy(path, paths);
    for(i = 0, j = 0; *(paths + i) != '\0'; i++, j++) {
        if(*(paths + i) == ':') {
            *(path + j) = '\0';
            if(xrandrExists(path))
                return 1;
            j = -1;
        } else
            *(path + j) = *(path + i);
    }
    return 0;
}

void executeCommand(void) {
    char *args[] = {"/bin/sh", "-c", XRANDR, NULL};
    execve("/bin/sh", args, __environ);
}

int resolution_getResolution(resolution *res) {
    pid_t pid;
    char shm_name[100];
    char xrandr_output[XRANDR_OUTPUT_LENGTH];
    int xrandr_output_fd;
    if(!checkAccessibility()) {
        printf("No xrandr to get screen resolution...\n");
        return -1;
    }
    snprintf(shm_name, 100, "/dyn-background resolution [%x]", (unsigned) getpid());
    xrandr_output_fd = shm_open(shm_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    pid = fork();
    if(pid == -1) {
        printf("Could not fork for executing xrandr...\n");
        close(xrandr_output_fd);
        shm_unlink(shm_name);
        return -2;
    } else if(pid == 0) {
        stdout = fdopen(xrandr_output_fd, "w");
        printf("Test\n");
        executeCommand();
    } else {
        waitpid(pid, NULL, 0);
        close(xrandr_output_fd);
        shm_unlink(xrandr_output);
    }
}
