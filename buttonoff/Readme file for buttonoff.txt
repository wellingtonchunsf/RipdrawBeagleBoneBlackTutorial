Readme file for buttonoff.c Version 1.0T 8/1/14 Ripdraw Tutorial application that uses touch and clears the button from the screen.



The code was generated using the gcc version 4.8.1, Yagarto tool chain and Eclipses IDE.

The demo program is distributed in the following directory structure

buttonoff directory
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

The buttonoff.c is the main program that loads up the display with buttons and
then polls for touches on the button and deletes the button on the touched
area.  It also provides an example on how to debounce a touch.

The gettouch.c file shows how to read a touch events and it process multiple packets from a single event. It parses the touch area name and touch coordinates

The enableloadwrite.c file contains a function to enable a layer, load an image to memory and write an image into a layer based on a table.

The image files must be preloaded into the Ripdraw display via the emulator before you run this program.


