/* gettouch.c  Version 1.0T 8/1/14 Ripdraw Tutorial application uses touch and clears buttons from the screen 
 * 
 * gettouch() extracts the touch area name and returns to the calling routine for it to use an an index into the table 
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


int gettouch(RD_INTERFACE* rd_interface, int* side)
{
	int ii;
	int i;
	int ret = 0;
	int x_y = 0;
    	count = 0;  

	*side = 0xff;    /* set side to poll return of nothing to read */
	/* Poll for an event, return if none*/
	ret = Rd_EventMessage(rd_interface,&events,&count);
    	if (ret != 0) return ret;

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
				
				// Read first 2 byte, which is length of coordinates
				RD_UWORD size = *((RD_UWORD*)data);
				
				for (ii=0; ii < size; ii=ii+2) 
				{
					data += 2; /* bump to coordinates */
					RD_UWORD x_y = *((RD_UWORD*)data);
					printf ("%x ",x_y);
				}
				//data += BYTE_2,pointer increment by two for touch coordinates data
				//touch coordinates data, see touch data sheet
				//data pointer increment for label length
				data = data + 2;
				

				// read 2 byte of label length
				RD_UWORD len = *((RD_UWORD*)data);
			
				//increment pointer 2 byte for label string. 
				data += 2;

				//copy label string in label 
				memcpy(label, data, len);

				//append NULL character at the end.
				*(label + len) =(char) NULL;
				*side = *data; /* return first character of touch area name */

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
