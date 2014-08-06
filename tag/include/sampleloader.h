/* 
  sampleloader.h
  header fil


*/
#define IMAGE_NAME_LENGTH 30	/* maximun size of ascii file name length */
#define TOUCH_NAME_LENGTH 30	/* maximun size of ascii file name length */
#define STATUS_OK 0
#define OFF 0
#define ON  1
#define ENDLIST  -1

	/* image_object with info to load, write and manipulate the image */
	struct image_object	
	{
		char image_name[IMAGE_NAME_LENGTH];	/* ascii name of image */
		int image_layer;			/* layer number for image */
		int image_x;				/* X position for image */
		int image_y;				/* Y position for image */
		int image_id;				/* image id returned from Rd_ImageLoad() */
		int image_write_id;			/* image write id returned from Rd_ImageWrite() */
		int debounce;				/* debounce count for touch */
	};

	/* touch_object with info to load, write and manipulate the touch */
	struct touch_object	
	{
		char touch_name[TOUCH_NAME_LENGTH];	/* ascii name of touch */
		int touch_x;				/* X position for touch */
		int touch_y;				/* Y position for touch */
		int touch_x_size;			/* X size for touch */
		int touch_y_size;			/* Y size for touch */
		int touch_id;				/* touch_id returned from Rd_TouchMapShape() */
	};

