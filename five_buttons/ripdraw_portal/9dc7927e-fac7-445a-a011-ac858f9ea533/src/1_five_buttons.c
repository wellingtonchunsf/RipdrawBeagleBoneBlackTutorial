/* 1_five_buttons.c
 * 
 * supports Windows/Linux only
 * supports little-endian CPU only
 * 
 */
#include "ripdraw.h"

/* ================================================================== */
/* load_1_five_buttons */

int load_1_five_buttons(RD_INTERFACE* rd_interface)
{
    int ret = 0;

    /* ================================================================== */
    /* release these loaded resource using proper release commands at last or not required */
    RD_ID image_button___large_round_bubble___blue = 0;
    RD_ID image_button___large_round_bubble___blue_1 = 0;
    RD_ID image_button___large_round_bubble___orange = 0;
    RD_ID image_button___large_round_bubble___orange_1 = 0;
    RD_ID image_button___large_round_bubble___green = 0;
    RD_ID image_button___large_round_bubble___green_1 = 0;
    RD_ID image_button___large_round_bubble___yellow = 0;
    RD_ID image_button___large_round_bubble___yellow_1 = 0;
    RD_ID image_red_on = 0;
    RD_ID image_red_on_1 = 0;


    ret = Rd_SetLayerEnable(rd_interface, 1, RD_TRUE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 1, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageLoad(rd_interface, "button - large round bubble - blue", &image_button___large_round_bubble___blue);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageWrite(rd_interface, 1, image_button___large_round_bubble___blue, Rd_Position(0, 0), &image_button___large_round_bubble___blue_1);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageLoad(rd_interface, "button - large round bubble - orange", &image_button___large_round_bubble___orange);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageWrite(rd_interface, 1, image_button___large_round_bubble___orange, Rd_Position(879, 454), &image_button___large_round_bubble___orange_1);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageLoad(rd_interface, "button - large round bubble - green", &image_button___large_round_bubble___green);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageWrite(rd_interface, 1, image_button___large_round_bubble___green, Rd_Position(875, 2), &image_button___large_round_bubble___green_1);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageLoad(rd_interface, "button - large round bubble - yellow", &image_button___large_round_bubble___yellow);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageWrite(rd_interface, 1, image_button___large_round_bubble___yellow, Rd_Position(2, 451), &image_button___large_round_bubble___yellow_1);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageLoad(rd_interface, "red-on", &image_red_on);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_ImageWrite(rd_interface, 1, image_red_on, Rd_Position(440, 240), &image_red_on_1);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerEnable(rd_interface, 2, RD_FALSE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 2, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerEnable(rd_interface, 3, RD_FALSE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 3, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerEnable(rd_interface, 4, RD_FALSE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 4, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerEnable(rd_interface, 5, RD_FALSE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 5, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerEnable(rd_interface, 6, RD_FALSE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 6, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerEnable(rd_interface, 7, RD_FALSE);
    if (ret < 0)
    {
        return ret;
    }
    ret = Rd_SetLayerBackColor(rd_interface, 7, Rd_Color(0xFF, 0xFF, 0xFF, 0x0));
    if (ret < 0)
    {
        return ret;
    }

    return ret;
}
