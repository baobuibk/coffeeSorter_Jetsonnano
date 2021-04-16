/***********************************/
/* @Nguyen Duc An	           */
/* @release_date 11th 2021         */
/* @version 1.0                    */
/* @email ducannguyen96@gmail.com  */
/***********************************/

#include "uart.h"
#include <stdio.h>
#include <unistd.h>       // Used for UART
#include <sys/fcntl.h>    // Used for UART
#include <termios.h>      // Used for UART
#include <string>
#include "afproto.h"


using namespace std;

Uart :: Uart (){
//  int ii, jj, kk;
  const char *uart_target = "/dev/ttyTHS1";

  // SETUP SERIAL WORLD

  struct termios  port_options;   // Create the structure

  tcgetattr(fid, &port_options);	// Get the current attributes of the Serial port


  //------------------------------------------------
  //  OPEN THE UART
  //------------------------------------------------
  // The flags (defined in fcntl.h):
  //	Access modes (use 1 of these):
  //		O_RDONLY - Open for reading only.
  //		O_RDWR   - Open for reading and writing.
  //		O_WRONLY - Open for writing only.
  //	    O_NDELAY / O_NONBLOCK (same function)
  //               - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
  //                 if there is no input immediately available (instead of blocking). Likewise, write requests can also return
  //				   immediately with a failure status if the output can't be written immediately.
  //                 Caution: VMIN and VTIME flags are ignored if O_NONBLOCK flag is set.
  //	    O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.fid = open("/dev/ttyTHS1", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode

  fid = open(uart_target, O_RDWR | O_NOCTTY );

  tcflush(fid, TCIFLUSH);
  tcflush(fid, TCIOFLUSH);

  usleep(1000000);  // 1 sec delay

  if (fid == -1)
  {
    printf("**Error - Unable to open UART**.  \n=>Ensure it is not in use by another application\n=>Ensure proper privilages are granted to accsess /dev/.. by run as a sudo\n");
  }

  //------------------------------------------------
  // CONFIGURE THE UART
  //------------------------------------------------
  // flags defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html
  //	Baud rate:
  //         - B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200,
  //           B230400, B460800, B500000, B576000, B921600, B1000000, B1152000,
  //           B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
  //	CSIZE: - CS5, CS6, CS7, CS8
  //	CLOCAL - Ignore modem status lines
  //	CREAD  - Enable receiver
  //	IGNPAR = Ignore characters with parity errors
  //	ICRNL  - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
  //	PARENB - Parity enable
  //	PARODD - Odd parity (else even)

  port_options.c_cflag &= ~PARENB;            // Disables the Parity Enable bit(PARENB),So No Parity
  port_options.c_cflag &= ~CSTOPB;            // CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit
  port_options.c_cflag &= ~CSIZE;	            // Clears the mask for setting the data size
  port_options.c_cflag |=  CS8;               // Set the data bits = 8
  port_options.c_cflag &= ~CRTSCTS;           // No Hardware flow Control
  port_options.c_cflag |=  CREAD | CLOCAL;                  // Enable receiver,Ignore Modem Control lines
  port_options.c_iflag &= ~(IXON | IXOFF | IXANY);          // Disable XON/XOFF flow control both input & output
  port_options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Non Cannonical mode
  port_options.c_oflag &= ~OPOST;                           // No Output Processing

  port_options.c_lflag = 0;               //  enable raw input instead of canonical,

  port_options.c_cc[VMIN]  = VMINX;       // Read at least 1 character
  port_options.c_cc[VTIME] = 0;           // Wait indefinetly

  cfsetispeed(&port_options,BAUDRATE);    // Set Read  Speed
  cfsetospeed(&port_options,BAUDRATE);    // Set Write Speed

  // Set the attributes to the termios structure
  int att = tcsetattr(fid, TCSANOW, &port_options);

  if (att != 0 )
  {
    printf("\nERROR in Setting port attributes");
  }
  else
  {
    printf("\nSERIAL Port Good to Go.\n");
  }

  // Flush Buffers
  tcflush(fid, TCIFLUSH);
  tcflush(fid, TCIOFLUSH);

  usleep(500000);   // 0.5 sec delay


}



//--------------------------------------------------------------
//
//			SENDING UART (test here later)
//--------------------------------------------------------------

void Uart :: sendUart(uint8 *data,uint16 data_size)
{	
	if (fid != -1)
	{
		int count = write(fid, data, data_size);		//Filestream, bytes to write, number of bytes to write
		printf("Count = %d\n", count);
		if (count < 0)  printf("UART TX error\n");
  	}

}




//--------------------------------------------------------------
//	ENCODING DATA AND TRANSMITING TO NANO JETSON
void Uart::Uart2kit(uint16 shooting_time, uint8 channel)
{
//	uint16  shooting_time = 0x1309;
//        uint8   channel =       0x11;
        uint16  lenbuff =       3;
//        Uart    test;

        uint8   msb_shooting_time = (shooting_time >> 8) & 0xFF;
        uint8   lsb_shooting_time = (shooting_time >> 0) & 0xFF;

        const char      buff[3] = {channel, msb_shooting_time,lsb_shooting_time};
        char            encode_buff[20];                                                //using for store data that is encoded
        uint8           encode_buff_Uart[20];                                           // data will be sent through Uart
        uint16          p_endcode_len;							// length of data after encoded

        afproto_frame_data(buff, lenbuff ,encode_buff, &p_endcode_len);


        for (uint8 i=0; i< p_endcode_len;i++)
        {
                encode_buff_Uart[i] = (uint8)encode_buff[i];
                printf("%x \n", encode_buff_Uart[i]);
        }



       sendUart(encode_buff_Uart,p_endcode_len);
//        test.closeUart();

}


/*
//==============================================================

void Uart :: sendUart(uint8 *msg){
  //--------------------------------------------------------------
  // TRANSMITTING BYTES
  //--------------------------------------------------------------
  uint8 tx_buffer[20];
  uint8 *p_tx_buffer;

  p_tx_buffer = &tx_buffer[0];

  // so that i have the number of bytes to write
  // by doing p_tx - tx
  for (int i = 0; i < 20; i++) {
    *p_tx_buffer++ = msg[i];
  }
  //printf("%x%x%x%x%x\n",p_tx_buffer[0],p_tx_buffer[1],p_tx_buffer[2],p_tx_buffer[3],p_tx_buffer[4]);
  printf("fid 1=%d\n", fid );

  if (fid != -1)
  {
    int count = write(fid, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));               //Filestream, bytes to write, number of bytes to write

//  usleep(1000);   // .001 sec delay

    printf("Count = %d\n", count);

    if (count < 0)  printf("UART TX error\n");
  }

//  usleep(1000000);  // 1 sec delay


}

*/





//--------------------------------------------------------------
// TRANSMITTING BYTES WITH LOGICAL FEED BACK
//--------------------------------------------------------------

bool  Uart :: sendUart_fb(unsigned char *msg){

  unsigned char tx_buffer[20];
  unsigned char *p_tx_buffer;

  p_tx_buffer = &tx_buffer[0];

  // so that i have the number of bytes to write
  // by doing p_tx - tx
  for (int i = 0; i < 20; i++) {
    *p_tx_buffer++ = msg[i];
  }
  //printf("%x%x%x%x%x\n",p_tx_buffer[0],p_tx_buffer[1],p_tx_buffer[2],p_tx_buffer[3],p_tx_buffer[4]);
  printf("fid 1=%d\n", fid );
  

  if (fid != -1)
  {
    int count = write(fid, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write

    usleep(1000);   // .001 sec delay

    printf("Count = %d\n", count);

    if (count < 0)  
    {
	    printf("UART TX error\n");
	    return false;
    }
    return true;
  }
  else
  {
	  return false;
  }

  usleep(1000000);  // 1 sec delay


}
void Uart :: readUart(){

  //--------------------------------------------------------------
  // RECEIVING BYTES - AND BUILD MESSAGE RECEIVED
  //--------------------------------------------------------------
  unsigned char rx_buffer[VMINX];
  bool          pickup = true;
  int ii;
  int           rx_length;
  int           nread = 0;

  tcflush(fid, TCIOFLUSH);

  usleep(1000);   // .001 sec delay

  printf("Ready to receive message.\n");


  for (ii=0; ii<NSERIAL_CHAR; ii++)  serial_message[ii]=' ';


  while (pickup && fid != -1)
  {
    nread++;

    rx_length = read(fid, (void*)rx_buffer, VMINX);   // Filestream, buffer to store in, number of bytes to read (max)

    printf("Event %d, rx_length=%d, Read=%s\n",  nread, rx_length, rx_buffer );

    if (rx_length < 0)
    {
      //An error occured (will occur if there are no bytes)
    }

    if (rx_length == 0)
    {
      //No data waiting
    }

    if (rx_length>=0)
    {
      if (nread<=NSERIAL_CHAR){
        serial_message[nread-1] = rx_buffer[0];   // Build message 1 character at a time
        printf("%x ",serial_message[nread-1]);
      }

      if (rx_buffer[0]=='#')   pickup=false;                               // # symbol is terminator
    }
  }

  printf("\nMessage Received:");

}

void Uart :: closeUart(){
  //-------------------------------------------
  //  CLOSE THE SERIAL PORT
  //-------------------------------------------
  close(fid);
}
/*
int main(int argc, char *argv[]) {
  Uart u;
  int i;
  unsigned char m[256];
  m[0]= (unsigned char) 1;
  m[1]= (unsigned char) 0;
  m[2]= (unsigned char) 0;
  m[3]= (unsigned char) 0;
  m[4]= (unsigned char) 1;
  m[5]= (unsigned char) '#';
  m[6]= (unsigned char) '\0';
  while (1) {
    u.sendUart(m);
    printf("sent\n");

    //feed back function test
    if(u.sendUart_fb(m))
    {
	    printf("data send with feed back\n");
    }
    else
    {
	    printf("data failed to send with feedback\n");
    }
    // end of feed back function test
   
    usleep(10000);
    u.readUart();
    while (u.serial_message[i]!='#') {
      printf("%x ",u.serial_message[i]);
      i++;
    }
    printf("\n");
  }
  return 0;
}
*/
