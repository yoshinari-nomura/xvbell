/// xvbell --- Flash X screen from command line.
///
/// Copyright (C) 2020 Yoshinari Nomura <nom@quickhack.net>
/// All rights reserved.
///
/// Created: 2020-04-11
/// Version: 1.0
/// License: MIT
///
/// * Compile
///   gcc -Wall -Wextra -Werror -o xvbell xvbell.c -lX11
///
/// * Usage
///   xvbell [color_name]
///
/// * Example
///   xvbell green
///
#include <X11/Xlib.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long name_to_pixel(Display *display, char *color_name)
{
  int scr = XDefaultScreen(display);
  Colormap cmap = XDefaultColormap(display, scr);
  XColor c1, c2;

  if (XAllocNamedColor(display, cmap, color_name, &c1, &c2)) {
    return c1.pixel;
  }
  return WhitePixel(display, scr);
}

int main(int argc, char *argv[])
{
  Display *dpy = XOpenDisplay(NULL);

  if (!dpy)
    exit(-1);

  int scr = XDefaultScreen(dpy);

  char *color_name = "white";
  if (argc > 1) color_name = argv[1];

  XSetWindowAttributes attr;
  attr.background_pixel  = name_to_pixel(dpy, color_name);
  attr.override_redirect = True;
  attr.save_under        = True;

  Window win = XCreateWindow(
                 dpy,
                 XRootWindow(dpy, scr), // parent
                 0, 0, // x, y
                 DisplayWidth(dpy, scr),
                 DisplayHeight(dpy, scr),
                 0, // border_width
                 XDefaultDepth(dpy, scr),
                 InputOutput, // class
                 XDefaultVisual(dpy, scr),
                 CWBackPixel | CWOverrideRedirect | CWSaveUnder,
                 &attr);

  XMapRaised(dpy, win);
  XFlush(dpy);
  usleep(100000); // 0.1 sec = 100,000
  XUnmapWindow(dpy, win);
  exit(0);
}
