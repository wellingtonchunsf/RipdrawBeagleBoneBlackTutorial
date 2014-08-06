/* tag.c  Version 1.0T 8/1/14 Ripdraw Tutorial application that uses the x,y position from touch.  
 * Application simulates a game of tag between two buttons
 * Move the gold buttom away from the red button with your finger
 *
 * tag.c
 *
 * The program will look at the image_list structure for the
 *    - image name
 *    - layer to write it to
 *    - x position
 *    - y positon
 *    - imageid is for storage of imageid from Rd_ImageLoad()
 *    - imagewrite_id is for storage of imagewrite_id from Rd_ImageWrite()
 * 
 *
 * NOTE gettouch.c version 1.1T is used for this build
 * gettouch.c modified to return x,y position of touch
 */


#include <stdio.h>
#include "ripdraw.h"
#include "sampleloader.h"

#define SLEEPTIME 1	/* amount of time to sleep so user can see transitions */
#define POLLSLEEP 1	/* amount of time to sleep before polling again*/

#define LAYER_START 1
#define LAYER_END  7
#define TOUCH_DEBOUNCE -4 /* always a negetive number, when count down to zero, then accept touch */


#define FINGER 0 	/* hard code index for finger image */
#define CHASE 1		/* hard code index for chase image */

#define DELTA_X	4	/* chase delta values */
#define DELTA_Y 4	/* chase delta values */
 
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
 *
 *
 *  List has been ended after first two buttons, leave other buttons for convience
 */
	struct image_object image_list[] =
	{
		{"gold-button",		6,		514-75,300-75,		0,0,0},\
		{"red-on",		1,		0,0,		0,0,0},\
		{"STOP",ENDLIST,0,0,	0,0,0},\
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
 * load the touch_list with the touch image name, x position, y positon, x size, y size id and page id 
 *
 * edit table for just one touch area that covers the entire screen, leave other touch areas for convience
 * */
	struct touch_object touch_list[] =
	{
		{"0",		0,0,		1024,600,	0},\
		{"STOP",	0,0,		0,0,		ENDLIST}, /* Setting id  = ENDLIST, denotes end of list this must be last entry in list */
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
	int i;
	int ii;
	int ret;
	int x;
	int y;
	int xx;
	int yy;
	int x_chase;
	int y_chase;
	int xsize;
	int ysize;
	int touch_side;
	int image_id;
	int write_id;

/* move good declarations below this line */
	RD_INTERFACE* rd_interface;
	RD_ID layer;
	RD_ID touch_id;

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
	 * create touch map  
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
	#define	RED_BACK	0x00
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
		ret = gettouch(rd_interface, &touch_side, &x,&y);
		if (ret != STATUS_OK) return ret;
		usleep(POLLSLEEP);  /* sleep before repolling */


		/* get current position of FINGER into table so that CHASE can find it */
		xx = image_list[FINGER].image_x; 
		yy = image_list[FINGER].image_y; 
		printf ("\n finger x position %d %xh",xx,xx);
		printf ("\n finger y position %d %xh\n",yy,yy);
		
		/* get current position of CHASE */
		x_chase = image_list[CHASE].image_x; 
		y_chase = image_list[CHASE].image_y; 

		/* move chase button to follow finger */
		if (xx < x_chase) {
			x_chase = x_chase - DELTA_X;
		}
		else 
		{
			if (xx != x_chase)x_chase = x_chase + DELTA_X;

		}
		if (yy < y_chase) {
			y_chase = y_chase - DELTA_Y;
		}
		else {
			if (yy!=y_chase) y_chase = y_chase + DELTA_Y;
		}


		/* limit move to protect edges */
		if (x_chase <=0 ) x_chase = 1;
		if (x_chase >=1024) x_chase = 1023;
		if (y_chase<=0) y_chase =1;
		if (y_chase>=600) y_chase=599;

		/* update CHASE positon */
		image_list[CHASE].image_x = x_chase; 
		image_list[CHASE].image_y = y_chase; 
		printf ("\n chase x position %d %xh",x_chase,x_chase);
		printf ("\n chase y position %d %xh\n",y_chase,y_chase);

		/* move object to new position */
		/* get the image write id and compose*/
		write_id = image_list[CHASE].image_write_id; 
		ret = Rd_ImageMove(rd_interface, write_id ,Rd_Position(x_chase,y_chase)); 
		if (ret != STATUS_OK) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
		if (ret != STATUS_OK) return ret;

		/* touch_side is not equal to 0xff if a touch was returned */
		if (touch_side != 0xff)
		{
			printf ("\n follow x position %d %xh",x,x);
			printf ("\n follow y position %d %xh\n",y,y);

			touch_side= touch_side -0x30;/* strip of ascii offset and use the value to index into the image */
			printf("Got touch from %d\n",touch_side);

			/* get the image id */
			image_id = image_list[FINGER].image_id; 

			/* get the image write id*/
			write_id = image_list[FINGER].image_write_id; 

			/* center the touch to the middle of object */
			x = x - 75;
			y = y - 75;

			/* limit move to protect edges */
			if (x <=0 ) x = 1;
			if (x >=1024) x = 1023;
			if (y<=0) y =1;
			if (y>=600) y=599;


			/* move object to new position */
			ret = Rd_ImageMove(rd_interface, write_id ,Rd_Position(x,y)); 
			if (ret != STATUS_OK) return ret;
				
			/* store current position of FINGER into table so that CHASE can find it */
			image_list[FINGER].image_x = x; 
			image_list[FINGER].image_y = y; 

		
			ret = Rd_ComposeLayersToPage(rd_interface, 1);
			if (ret != STATUS_OK) return ret;
		}
	}
		
	/* close off the interface */
	ret = RdInterfaceClose(rd_interface);
	return 0;
}
