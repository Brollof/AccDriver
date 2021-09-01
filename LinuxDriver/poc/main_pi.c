#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringSerial.h>

static void printXYZ(uint8_t *buf)
{
  int16_t x = buf[0] | (buf[1] << 8);
  int16_t y = buf[2] | (buf[3] << 8);
  int16_t z = buf[4] | (buf[5] << 8);

  printf("x: %d, y: %d, z: %d\n", x, y, z);
}
        

int main ()
{
  int serial_port;
  char c;

  if ((serial_port = serialOpen("/dev/serial0", 9600)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup() == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    serialClose(serial_port);
    return 1 ;
  }


  uint8_t buf[16] = {0};
  uint8_t i = 0;

  while (1)
  {
    int count = serialDataAvail(serial_port);
    while (count > 0)
    {
      count--;
      c = serialGetchar(serial_port);		/* receive character serially*/	
      if (c == 0xCE)
      {
        printXYZ(buf);
        i = 0;
        memset(buf, 0, sizeof(buf));
      }
      else
      {
        buf[i++] = c;
      }
    }
  }
  serialClose(serial_port);
}


