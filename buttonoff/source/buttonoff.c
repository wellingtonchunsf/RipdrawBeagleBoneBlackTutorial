/* buttonoff.c  Version 1.0T 8/1/14 Ripdraw Tutorial application uses touch and clears buttons from the screen 
 *
 * buttonoff.c
 * 
 *
 * Demo program for Ripdraw Display
 * The program will look at the image_list structure for the
 *    - image name
 *    - layer to write it to
 *    - x position
 *    - y positon
 *    - imageid is for storage of imageid from Rd_ImageLoad()
 *    - imagewrite_id is for storage of imagewrite_id from Rd_ImageWrite()
 * 
 */


#include <stdio.h>
#include "ripdraw.h"
#include "sampleloader.h"

#define STATUS_OK 0
#define SLEEPTIME 1	/* amount of time to sleep so user can see transitions */
#define POLLSLEEP 1	/* amount of time to sleep before polling again*/

#define LAYER_START 1
#define LAYER_END  7
#define TOUCH_DEBOUNCE -4 /* always a negative number, when count down to zero, then accept touch */

/* 
 * image_list is an application lookup table to load and keep track of mutiple images
 *
 * load the image_list with 
 * 	image name, 
 * 	layer, 
 * 	x position, y positon, 
 * 	imageid 
 * 	imagewrite id, 
 * 	debounce count 
 */
	struct image_object image_list[] =
	{
		{"yellow-on",		1,		0,0,		0,0,0},\
		{"violet-on",		1,		0,150,		0,0,0},\
		{"red-on",		1,		0,300,		0,0,0},\
		{"pink-on",		1,		0,450,		0,0,0},\
		{"peacock-blue-on",	2,		150,0,		0,0,0},\
		{"orange-on",		2,		150,150,	0,0,0},\
		{"green-on",		2,		150,300,	0,0,0},\
		{"gold-button",		2,		150,450,	0,0,0},\
		{"yellow-on",		3,		300,0,		0,0,0},\
		{"violet-on",		3,		300,150,	0,0,0},\
		{"red-on",		3,		300,300,	0,0,0},\
		{"pink-on",		3,		300,450,	0,0,0},\
		{"peacock-blue-on",	4,		450,0,		0,0,0},\
		{"orange-on",		4,		450,150,	0,0,0},\
		{"green-on",		4,		450,300,	0,0,0},\
		{"gold-button",		4,		450,450,	0,0,0},\
		{"yellow-on",		5,		600,0,		0,0,0},\
		{"violet-on",		5,		600,150,	0,0,0},\
		{"red-on",		5,		600,300,	0,0,0},\
		{"pink-on",		5,		600,450,	0,0,0},\
		{"peacock-blue-on",	6,		750,0,		0,0,0},\
		{"orange-on",		6,		750,150,	0,0,0},\
		{"green-on",		6,		750,300,	0,0,0},\
		{"gold-button",		6,		750,450,	0,0,0},\
		{"yellow-on",		7,		900,0,		0,0,0},\
		{"violet-on",		7,		900,150,	0,0,0},\
		{"red-on",		7,		900,300,	0,0,0},\
		{"pink-on",		7,		900,450,	0,0,0},\
		{"STOP",ENDLIST,0,0,	0,0,0},\
		{"STOP",ENDLIST,0,0,	0,0}     /* Setting layer = ENDLIST, denotes end of list this must be last entry in list */
	};

/* 
 * touch_list is an application lookup table to load and keep track of touch area 
 *
 * load the touch_list with 
 * 	touch area name, 
 * 	x position, y positon, 
 * 	x size, y size id 
 * 	touch id 
 *
 * each touch area maps directly over the button images in the image_list[]
 * each touch area name is "ascii sequential" and when you mask off the "ascii" offset, the value can use to index into the image_list[] to the corresponding image 
 * 	
 */
	struct touch_object touch_list[] =
	{
		{"0",		0,0,		150,150,	0},\
		{"1",		0,150,		150,150, 	0},\
		{"2",		0,300,		150,150,	0},\
		{"3",		0,450,		150,150,	0},\
		{"4",		150,0,		150,150,	0},\
		{"5",		150,150,	150,150,	0},\
		{"6",		150,300,	150,150,	0},\
		{"7",		150,450,	150,150,	0},\
		{"8",		300,0,		150,150,	0},\
		{"9",		300,150,	150,150,	0},\
		{":",		300,300,	150,150,	0},\
		{";",		300,450,	150,150,	0},\
		{"<",		450,0,		150,150,	0},\
		{"=",		450,150,	150,150,	0},\
		{">",		450,300,	150,150,	0},\
		{"?",		450,450,	150,150,	0},\
		{"@",		600,0,		150,150,	0},\
		{"A",		600,150,	150,150,	0},\
		{"B",		600,300,	150,150,	0},\
		{"C",		600,450,	150,150,	0},\
		{"D",		750,0,		150,150,	0},\
		{"E",		750,150,	150,150,	0},\
		{"F",		750,300,	150,150,	0},\
		{"G",		750,450,	150,150,	0},\
		{"H",		900,0,		124,150,	0},\
		{"I",		900,150,	124,150,	0},\
		{"J",		900,300,	124,150,	0},\
		{"K",		900,450,	124,150,	0},\
		{"STOP",	0,0,		0,0,		ENDLIST} /* Setting id  = ENDLIST, denotes end of list this must be last entry in list */
	};

int main(int argc, char **argv)
{
	int touch_side;
	int image_id;
	int write_id;

	int i;
	int ii;
	int ret;
	
	RD_ID layer;
	RD_ID touch_id;
	RD_UWORD x;
	RD_UWORD y;
	RD_UWORD xsize;
	RD_UWORD ysize;
	RD_INTERFACE* rd_interface;

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
	 * creat touch map  
	 * do this for every element of the list
	 * stop when element has touch_id = ENDLIST
	*/
	for (i=0; touch_list[i].touch_id != ENDLIST; i++)
	{
		/* fetch the x, y position for the touch area from the table */
		x = touch_list[i].touch_x;
		y = touch_list[i].touch_y;

		/* fetch the size of the touch area from the table */
		xsize = touch_list[i].touch_x_size;
		ysize = touch_list[i].touch_y_size;

		/* create the rectangle touch area, provide the position, size and name of touch area,  returns touch id */
		ret = Rd_TouchMapRectangle(rd_interface, Rd_Position(x,y),Rd_Size(xsize,ysize),(char *) &touch_list[i].touch_name,&touch_id);
		if (ret != STATUS_OK) return ret;

		/* save touch_id for each area back into the table */
		touch_list[i].touch_id = touch_id;
	}

	/*
	 * Set background color for this layer
	 *
	 * Rd_Color() is short function that packs the red, green, blue and alpha values into a structure
	 * color values  RGB= 0xFF is white,  RGB = 0x00 is black 
	 *
	 */
	#define	RED_BACK	0xff
	#define	GREEN_BACK	0xff
	#define	BLUE_BACK	0x00	
	#define ALPHA		0xff	

	layer = 1;
	ret = Rd_SetLayerEnable(rd_interface,layer, RD_TRUE);
	if (ret != STATUS_OK) return ret;

	ret =Rd_SetLayerBackColor(rd_interface, layer, Rd_Color(RED_BACK, GREEN_BACK, BLUE_BACK,ALPHA));
	if (ret != STATUS_OK) return ret;
	/* 
	 * enable layer, load image and write it 
	 * do this for every element of the list
	 * stop when element has image_layer = ENDLIST
	 *
	 *
	 * enableloadwriter(rd_interface, index into table, flag for enable layer, flag for load image, flag for write) 
	*/
	for (i=0; image_list[i].image_layer != ENDLIST; i++)
	{
		ret = enableloadwrite(rd_interface, i, RD_TRUE, RD_TRUE, RD_TRUE);
		if (ret != STATUS_OK) return ret;
	}


	/* compose all layers to page 1 so everything shows up at once */
	ret = Rd_ComposeLayersToPage(rd_interface, 1);
	if (ret != STATUS_OK) return ret;

	ret = Rd_PageToScreen(rd_interface,1);
	if (ret != STATUS_OK) return ret;

	/* get touch event */
	touch_side = 1;
	while(1) 
	{
		ret = gettouch(rd_interface, &touch_side);
		if (ret != STATUS_OK) return ret;
		usleep(POLLSLEEP);  /* sleep before repolling */

		/* touch_side is not equal to 0xff if a touch was returned */
		if (touch_side != 0xff)
		{
			touch_side= touch_side -0x30;/* strip of ascii offset and use the value to index into the image */
			printf("Got touch from %d\n",touch_side);

			/* get the image id */
			image_id = image_list[touch_side].image_id; 

			/* get the image write id*/
			write_id = image_list[touch_side].image_write_id; 

			/* use touch_side to index to button and fetch debounce count
			 * debounce count is the number of "bounce counts" that we want before considering it a touch
			 */
			if (image_list[touch_side].debounce != 0 ) 
			{
				/* if debounce is not zero, increase towards zero and do nothing */
				++image_list[touch_side].debounce; 
			}
			else if (write_id >0) /* if image_write_id is greater than zero, image is up, delete it*/
			{
				/* delete image from layer */
				ret = Rd_ImageDelete(rd_interface, write_id);
				image_list[touch_side].debounce = TOUCH_DEBOUNCE; /* set debounce count down */
				image_list[touch_side].image_write_id = 0;	/* set image_write_id to zero, image not written */ 
			}

			ret = Rd_ComposeLayersToPage(rd_interface, 1);
			if (ret != STATUS_OK) return ret;
		}
	}
		
	/* close off the interface */
	ret = RdInterfaceClose(rd_interface);
	printf("Done!\n");
	return 0;
}
