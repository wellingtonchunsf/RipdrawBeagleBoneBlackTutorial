/* ripdraw-serial.c Version 1.0T 8/1/14  Ripdraw serial port driver for Ripdraw C library, tutorial
 * 
 * Source code for port driver.  
 *
 * These functions are the low level device specific functions that are called by the ripdraw.c library to send/receive data for the specific device
 *
 * 	int rd_extint_open(RD_INTERFACE* rd_interface, const char* port_name);
 *  	int rd_extint_close(RD_INTERFACE* rd_interface);
 *  	int rd_extint_write(RD_INTERFACE* rd_interface, RD_BYTE* data_ptr, int data_len);
 *  	int rd_extint_read(RD_INTERFACE* rd_interface, RD_BYTE* data_ptr, int data_len);
 * 
 * supports Windows/Linux only
 * supports little-endian CPU only
 * 
 */

#include "ripdraw.h"

typedef struct _RD_INTERFACE_SERIAL
{
    int handle;
} RD_INTERFACE_SERIAL;

/* ================================================================== */
/* open the serial port */
int rd_extint_open(RD_INTERFACE* rd_interface, char* port_name)
{
    speed_t speed = B115200;
   // speed_t speed = B230400;

    int handle;
    struct termios settings;

    if (rd_interface == NULL)
    {
        printf("interface should not NULL");
        return -1;
    }

    handle = open(port_name, O_RDWR | O_NOCTTY);
    if (handle < 0)
    {
        printf("port open failed");
        return -1;
    }

    if (tcgetattr(handle, &settings) < 0)

    {
        printf("port initialization failed");
        return -1;
    }

    /* set input mode to raw, no echo
    * set output mode to raw */
    cfmakeraw(&settings);

    /* blocking mode */
    //settings.c_cc[VMIN] = 1;
    ////settings.c_cc[VTIME] = 10;
    //settings.c_cc[VMIN] = 0;
    ////settings.c_cc[VTIME] = 0;
    
    settings.c_cc[VMIN] = 10;
    settings.c_cc[VTIME] = 10;

    settings.c_line = N_TTY;

    /* Set the baud rate for both input and output. */
    if ((cfsetispeed(&settings, speed) < 0) || (cfsetospeed(&settings, speed) < 0))
    {
        printf("port initialization failed");
        return -1;
    }

    /* set no parity, stop bits, data bits */
    settings.c_cflag &= ~PARENB;
    settings.c_cflag &= ~(CSTOPB | CRTSCTS);
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8;

    if (tcsetattr(handle, TCSANOW, &settings) < 0)
    {
        printf("port initialization failed");
        return -1;
    }

    tcflush(handle, TCIOFLUSH);

	rd_interface->extint = malloc(sizeof(RD_INTERFACE_SERIAL));
	if (!rd_interface->extint)
	{
		close(handle);
		printf("external interface data not allocated");
		return -1;
	}

    rd_interface->is_open = 1;
    ((RD_INTERFACE_SERIAL*)rd_interface->extint)->handle = handle;
    return 0;
}

/* ================================================================== */
/* close serial port */
int rd_extint_close(RD_INTERFACE* rd_interface)
{
	RD_INTERFACE_SERIAL* extint = (RD_INTERFACE_SERIAL*)rd_interface->extint;
    _RD_CHECK_INTERFACE();

    rd_interface->is_open = 0;
    close(extint->handle);
	free(extint);
	
	return 0;
}

/* ================================================================== */
/* write data to serial */
int rd_extint_write(RD_INTERFACE* rd_interface, RD_BYTE* data_ptr, int data_len)
{
	RD_INTERFACE_SERIAL* extint = (RD_INTERFACE_SERIAL*)rd_interface->extint;
    int total_write = 0;
    int bytes_write;
    _RD_CHECK_INTERFACE();

    do
    {
        bytes_write = write(extint->handle, data_ptr, data_len - total_write);
        // DMK
        /* {
   			int i;
			for(i = 0; i < (data_len - total_write); i++)
				printf("%02X ", data_ptr[i]);
        }
        */
        // DMK
        if (bytes_write < 0)
        {
            return bytes_write;
        }
        total_write += bytes_write;
        data_ptr += bytes_write;
    }
    while (total_write < data_len);
    return 0;
}

/* ================================================================== */
/* read data from serial */
int rd_extint_read(RD_INTERFACE* rd_interface, RD_BYTE* data_ptr, int data_len)
{
	RD_INTERFACE_SERIAL* extint = (RD_INTERFACE_SERIAL*)rd_interface->extint;
    int total_read = 0;
    int bytes_read;
    _RD_CHECK_INTERFACE();

    do
    {
        bytes_read = read(extint->handle, data_ptr, data_len - total_read);
        if (bytes_read < 0)
        {
            return bytes_read;
        }
        total_read += bytes_read;
        data_ptr += bytes_read;
    }
    while (total_read < data_len);
    return 0;
}
