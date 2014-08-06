/* enableloadwrite.c  Version 1.0T 8/1/14 Ripdraw Tutorial application uses touch and clears buttons from the screen 
 * 
 * enableloadwrite(rd_interface, index to table, enable layer flag, enable load flag, enable write flag)
 *
 */
#include "ripdraw.h"
#include "sampleloader.h"

/* keep track of layer enable status */
int layerstatus[7] = 
{
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
};

int enableloadwrite(RD_INTERFACE* rd_interface, int index, int enableflag, int load_option, int write_option)
{
	extern int layerstatus[];
	extern struct image_object image_list[];
	int ret;
	RD_ID localid_image;
	RD_ID id_imagewrite;

	/* Manipulate layer on incoming image object based on incoming enableflag and current status
	 * If current layer is off (RD_FALSE) and enablflag is true, enable layer, layer has not been enabled yet
	 * if current layer is on  (RD_TRUE) and enableflag is true, layer is already enable, skip and don't enable again
	 * if current layer is on  (RD_TURE and enableflag is false, disable layer
	 */

	ret = STATUS_OK; /* set ret status to ok incase we don't do anything */
	if ((((layerstatus[(image_list[index].image_layer)]) == RD_FALSE) && (enableflag)) ||  ((!enableflag) && ((layerstatus[(image_list[index].image_layer)]== (RD_TRUE)))))
	{
		printf("\nLayer %d status %d", image_list[index].image_layer, enableflag);
	        layerstatus[image_list[index].image_layer] = enableflag;		/* set status to layer based on flag */ 
		ret = Rd_SetLayerEnable(rd_interface, image_list[index].image_layer, enableflag); /* enable or disable based on incoming flag layer only once for each layer */
		if (ret != STATUS_OK) return ret;
	}

	/* load image if load_option is selected */
	if (load_option)
	{
		/* Load image based on incoming image object  */
		printf("\nLoading image %s", image_list[index].image_name);
		ret = Rd_ImageLoad(rd_interface, image_list[index].image_name, &localid_image);
		if (ret != STATUS_OK) return ret;
		image_list[index].image_id = localid_image;   /* store image_id from Rd_ImageLoad backinto object*/
	}

	/* write image if write_option is selected */
	if (write_option)
	{
		/* Write the image based on the incoming image object */
		printf("\nImagewrite");
		ret = Rd_ImageWrite(rd_interface,image_list[index].image_layer,localid_image, Rd_Position(image_list[index].image_x, image_list[index].image_y), &id_imagewrite);
		if (ret != STATUS_OK) return ret;
		image_list[index].image_write_id = id_imagewrite;   /* store image_id from Rd_ImageLoad backinto object*/
	}

	return ret;
}
