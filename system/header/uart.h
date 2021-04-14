
/************************************/
/* Author: Duc An	            */
/* Date creating:  April 14	    */
/* @version 1.0                     */
/* @email ducannguyen96@gmail.com   */
/************************************/

#ifndef _UART_H
#define _UART_H

#include "type.h"

// Define Constants
//const char *uart_target = "/dev/ttyTHS1";
#define     NSERIAL_CHAR   256
#define     VMINX          1
#define     BAUDRATE       B115200


#define START_BIT       0x12
#define STOP_BIT        0x13
#define ESC             0x7D
#define OR_FLAG         0x20



class Uart {
private:
  /* data */
  int fid;
public:
  unsigned char serial_message[NSERIAL_CHAR];


  Uart ();
  void sendUart(uint8 *msg);
  bool sendUart_fb(unsigned char *msg);
  void readUart();
  void closeUart();

};
#endif
