/* gettouch.c  Version 1.1T 8/2/14 Ripdraw Tutorial application uses touch and clears buttons from the screen 
 * 
 * gettouch() extracts and returns the the touch area name and the XY position to the calling routine
 *
 * only touch screen events are processed
 * multiple packets can be recevied in one event, we read all packets, but overwrite all packets and just return on the last one
 *
 */
#include "ripdraw.h"
#include "sampleloader.h"

/* ================================================================== */
/* gettouch*/

    	RD_EVENT* events;
    	RD_UWORD count;
    	RD_UWORD icount;
    	RD_UWORD count;
	char label[256];

int gettouch(RD_INTERFACE* rd_interface, int* side, int* new_x, int* new_y)
{
	int bounce;
	int ii;
	int i;
	int ret = 0;
	RD_UWORD junk_raw;
	RD_UWORD x_raw;
	RD_UWORD y_raw;
	RD_UWORD xy_save;
	int xpos;
	int ypos;

    	count = 0;  

	*side = 0xff;    /* set side to poll return of nothing to read */
	/* Poll for an event, return if none*/
	ret = Rd_EventMessage(rd_interface,&events,&count);
    	if (ret != 0) return ret;

	bounce=0;  /*set bound to zero, accept incoming touches */
	if (count ==0 ) return ret;  /* a count of zero means poll returns no events */

	icount = count;  /*save inital packet count */
	// (count > 0) means if any packet receive then it will do further process
   	if (count > 0)
	{
		//access number of packet received.
		for (i=0; i < count; i++)
		{
			//if touch event then it will procees further
			if (events[i].event_type != 1) printf("Nontouch event %d\n", i);
			if (events[i].event_type == 1)
			{
				//data is now pointer to buffer which contain touch data.
				RD_BYTE* data = events[i].data;
				
				// Read first 2 byte, which is length of cordinates
				RD_UWORD size = *((RD_UWORD*)data);
				
				/* first word is junk, read and toss */
				data += 2; /* bump to coordinates */
				junk_raw = *((RD_UWORD*)data);
				printf ("%x ",junk_raw);

				/* read raw X value */
				data += 2; /* bump to coordinates */
				x_raw = *((RD_UWORD*)data);
				printf ("%x ",x_raw);

				/* mask of four garbage bits */
				x_raw = x_raw & 0xff0f;
				xy_save = x_raw; 

				/* swap 8 MSB with 8 LSB */
				x_raw = x_raw << 8;
				xy_save = xy_save >> 8;

				/* put together swapped bytes */
				xpos = x_raw | xy_save;


				/* read raw y value */
				data += 2; /* bump to coordinates */
				y_raw = *((RD_UWORD*)data);
				printf ("%x ",y_raw);
					

				/* swap 8 MSB with 8 LSB */
				xy_save = y_raw; 

				y_raw = y_raw << 8;
				xy_save = xy_save >> 8;

				/* put together swapped bytes */
				ypos = y_raw | xy_save;

				printf ("\n x position %d %xh",xpos,xpos);
				printf ("\n y position %d %xh\n",ypos,ypos);

				*new_x = xpos;
				*new_y = ypos;

				//data pointer increment for label length
				data = data + 2;
				
				// read 2 byte of label length
				RD_UWORD len = *((RD_UWORD*)data);
			
				//increment pointer 2 byte for label string. 
				data += 2;

				printf("\n length %d\n", len);
				if (len <= 1 ) {
				//copy label string in label 
				memcpy(label, data, len);

				//append NULL character at the end.
				*(label + len) =(char) NULL;
				*side = *data; /* return first character of touch area name */

				//Print the label.
				if (bounce)
				{
					printf("label: %s icount: %d count: %d bounced\n", label, icount, i);
				}
				else
				{
					printf("label: %s icount: %d count: %d  \n", label, icount, i );
				}
				bounce = 1; /* bounce touches until empty */
				}
			}
			//free that event.data.
			RdFreeData((RD_BYTE*)events[i].data);
		}
		count = 0;
		//free all events structures.
	RdFreeData((RD_EVENT*)events);
	return ret;
	}
}
