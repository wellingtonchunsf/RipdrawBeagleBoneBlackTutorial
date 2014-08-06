Readme file for fiveb.c Version 1.0T 8/1/14 Ripdraw Tutorial application that puts up 5 button images on layer 1.

The application demonstrates via C code the following steps:
  - initialize 			RdInterfaceInit()
  - reset 				Rd_Reset()			
					Display will go blank here
  - enable layer 			Rd_SetLayerEnable()
  - set background color  	Rd_SetLayerBackColor()
  - load images from flash	Rd_ImageLoad()
  - write images to layer	Rd_ImageWrite()
  - compose layers to page	Rd_ComposeLayersToPage()	
					Images will appear on display here
 - set page to screen		Rd_PageToScreen()
 - close off interface 	RdInterfaceClose(rd_interface)
 - done

The code was generated using the gcc version 4.8.1, Yagarto tool chain and Eclipses IDE.

The demo program is distributed in the following directory structure

five buttons directory
   include			*.h for main program, in this case there are none
   object 			object file directory
   source			source files
   ripdraw_portal		files from ripdraw portal, contains image files

ripdraw_core directory
   ripdraw.c  		ripdraw c library source
   ripdraw-serial.c	ripdraw serial port driver
   ripdraw.h 		ripdraw header file

A makefile is included in the distribution.
An executable is included, but his hardwired to /dev/tty/ACM0 and will work without changes if your USB is the same.

The image files must be preloaded into the Ripdraw display via the emulator before you run this program.

