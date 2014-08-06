Readme file for tag.c Version 1.0T 8/1/14 Ripdraw Tutorial application that uses touch x y position from the touch.

Application simulates a game of tag between two buttons
Move the gold buttom away from the red button with your finger

The code was generated using the gcc version 4.8.1, Yagarto tool chain and Eclipses IDE.

The demo program is distributed in the following directory structure

tage directory
   include			*.h for main program
   object 			object file directory
   source			source files
   ripdraw_portal		files from ripdraw portal, contains image files

ripdraw_core directory
   ripdraw.c  		ripdraw c library source
   ripdraw-serial.c	ripdraw serial port driver
   ripdraw.h 		ripdraw header file

A makefile is included in the distribution.

An executable is included, but his hardwired to /dev/tty/ACM0 and will work without changes if your USB is the same.

The tag.c is the main program that loads up the display with two buttons and then polls for touches and moves the button to the new location.  The other button chases the first button, simulating a game of tag.  It also provides an example on how to debounce a touch, extract a XY data from at a touch and move an image.

The gettouch.c file shows how to read a touch events and it process multiple packets from a single event. It parses the touch area name and touch coordinates. This version of getttouch() version 1.1T passes the x y coordinates back to calling routine

The enableloadwrite.c file contains a function to enable a layer, load an image to memory and write an image into a layer based on a table.

The image files must be preloaded into the Ripdraw display via the emulator before you run this program.


