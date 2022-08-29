#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include "resolution.h"

int resolution_getResolution(resolution *res) {
    Display *dpy;
    XRRScreenResources *screen;
    XRRCrtcInfo *crtc_info;

    res->width = 0;
    res->height = 0;
    dpy = XOpenDisplay(0);
    screen = XRRGetScreenResources(dpy, DefaultRootWindow(dpy));
    if(screen->crtcs) {
        crtc_info = XRRGetCrtcInfo(dpy, screen, screen->crtcs[0]);
        res->width = crtc_info->width;
        res->height = crtc_info->height;
        XRRFreeCrtcInfo(crtc_info);
    }
    XRRFreeScreenResources(screen);
    return screen->crtcs ? 1 : 0;
}
