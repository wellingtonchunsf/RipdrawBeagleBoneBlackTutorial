/* fiveb.c  Version 1.0T 8/1/14 Ripdraw Tutorial application that puts up 5 button images
 *
 *
 * Sample Ripdraw Tutorial application program to put up five simple images onto layer 1
 *
 * Steps
 *   - initialize 		RdInterfaceInit()
 *   - reset 			Rd_Reset()			Display will go blank here
 *   - enable layer 		Rd_SetLayerEnable()
 *   - set background color  	Rd_SetLayerBackColor()
 *   - load images from flash	Rd_ImageLoad()
 *   - write images to layer	Rd_ImageWrite()
 *   - compose layers to page	Rd_ComposeLayersToPage()	Images will appear on display here
 *   - set page to screen	Rd_PageToScreen()
 *   - close off interface 	RdInterfaceClose(rd_interface)
 *   - done
 */

#include <stdio.h>
#include "ripdraw.h"

int main(int argc, char **argv)
{

	#define STATUS_OK 0

	int ret;			/* return value from all Ripdraw library calls, zero is STATUS_OK */
	RD_INTERFACE* rd_interface;	/* Handle to the Ripdraw display */
	RD_ID layer;			/* Layers, 1 to 7 */
	RD_ID page;			/* Page 1 or 2, each page contains 7 layers */

    
	/* image id and write id storage for each image */
	RD_ID image_id_blue = 0;
	RD_ID write_id_blue = 0;

	RD_ID image_id_orange = 0;
	RD_ID write_id_orange = 0;

	RD_ID image_id_green = 0;
	RD_ID write_id_green = 0;

	RD_ID image_id_yellow = 0;
	RD_ID write_id_yellow = 0;

	RD_ID image_id_red = 0;
	RD_ID write_id_red = 0;
	 
	
	/*
	 * Initializd the Ripdraw library
	 * Connect the system port to a Ripdraw display interface handle
	 * if RD_interfaceInit returns a NULL handle, RDInterfaceInit() failed 
	 *
	 * The Ripdraw display interface handle is used direct all Ripdraw commands to the specific Ripdraw display
	 *
	 * For the Beagle board, the com port shows up as "/dev/ttyACMO"
	 * For windows platforms it may be COM10
	 * rd_interface = RdInterfaceInit("\\\\.\\COM10");
	 */

	/* change this line to the name of the USB device that matches your system */
	rd_interface = RdInterfaceInit("/dev/ttyACM0");
	if (rd_interface == NULL) return; /* if handle is NULL, the init failed */

	/* Issue reset to Ripdraw display
	* if you are single stepping, the screen will go blank
	*/
	ret = Rd_Reset(rd_interface);
	if (ret !=  STATUS_OK ) return ret;

	/* 
	 * Enable layer 1 on Ripdraw display
	 * There are seven layers begining with 1
	 * Layer numbers are numbered the same as "floor numbers", 1 is the lowest, 7 is the highest
	 * The user sees layers from the "top" down to the lowest layer, hence the higher layer can cover a lower layer
	 *
	 * This example is only using layer 1, so we only enable layer 1
	 * The same command is used to disable the layer 
	 */
	layer =1;
	ret = Rd_SetLayerEnable(rd_interface, layer, RD_TRUE);
	if (ret != STATUS_OK) return ret;
	
	/*
	 * Set background color for this layer
	 *
	 * Rd_Color() is short function that packs the red, green, blue and alpha values into a structure
	 *
	 * color values  RGB= 0xFF is white,  RGB = 0x00 is black 
	 *
	 */
	#define	RED_BACK	0x00
	#define	GREEN_BACK	0x00
	#define	BLUE_BACK	0xff	
	#define ALPHA		0xff	

	ret =Rd_SetLayerBackColor(rd_interface, layer, Rd_Color(RED_BACK, GREEN_BACK, BLUE_BACK,ALPHA));
	if (ret != STATUS_OK) return ret;

	/*
	 * For each of the images that are in the Ripdraw flash, load from flash into memory using the filename 
	 * Rd_ImageLoad returns an image_id, image_id is the handled to image,  image only needs to be loaded once
	 *
	 * Images MUST be already loaded into the Ripdraw flash, typically by the emulator
	 *
	 *
	 */
	ret = Rd_ImageLoad(rd_interface, "button - large round bubble - blue", &image_id_blue);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageLoad(rd_interface, "button - large round bubble - orange", &image_id_orange);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageLoad(rd_interface, "button - large round bubble - green", &image_id_green);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageLoad(rd_interface, "button - large round bubble - yellow", &image_id_yellow);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageLoad(rd_interface, "red-on", &image_id_red);
	if (ret != STATUS_OK) return ret;
	
	/*
	 * For each of the images that are now in memory, write the image using the image_id to a specific position in a specific layer 
	 * Rd_ImageWrite returns an write_id, write_id the handled to written image
	 * The write_id is used to manipulate this written image on the layer
	 * You can Rd_ImageWrite() an image multiple times to various or same layers, each time a unique write_id is returned so that each written image
	 * can be individually manipulated
	 *
	 * Rd_Position() is a short function to pack X,Y into data structure
	 * The x,y positon is the position for the upper left hand corner of the image
	 * 
	 * If you are single stepping, the image will not yet show up on the display
	 */
	ret = Rd_ImageWrite(rd_interface, layer, image_id_blue, Rd_Position(0, 0), &write_id_blue);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageWrite(rd_interface, layer, image_id_orange, Rd_Position(879, 454), &write_id_orange);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageWrite(rd_interface, layer, image_id_green, Rd_Position(875, 2), &write_id_green);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageWrite(rd_interface, layer, image_id_yellow, Rd_Position(2, 451), &write_id_yellow);
	if (ret != STATUS_OK) return ret;

	ret = Rd_ImageWrite(rd_interface, layer, image_id_red, Rd_Position(440, 240), &write_id_red);
	if (ret != STATUS_OK) return ret;

	/*
	 * Compose all layers to a page and everything should show up
	 *
	 * All images on the each layer is composed into one image on a page 
	 * The image if is composed to page 1, will be displayed
	 */
	page = 1;
	ret = Rd_ComposeLayersToPage(rd_interface, page);
	if (ret != STATUS_OK) return ret;

	/* 
	 * Page to Screen
	 *
	 * Rd_PageToScreen() connects page to the screen
	 *
	 * At startup, page 1 is already connected to the screen, so when you Rd_ComposeLayersToPage() to page 1, the display will show the composed images
	 * If you Rd_ComposeLayersToPage() to page 2, the display NOT will show the composed images until you Rd_PageToScreen() to page 2
	 * You can also use Rd_PageToScreen() to quickly switch between pages on the display
	 */ 
	ret = Rd_PageToScreen(rd_interface,page);
	if (ret != STATUS_OK) return ret;

	/* 
	 * close off the interface to clean things up for the OS
	 */
	ret = RdInterfaceClose(rd_interface);
	return 0;
}
