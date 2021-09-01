#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define START_BYTE  0xCC
#define END_BYTE    0xCE

static const char* serialName = "/dev/serial0";
static uint8_t rxBuf[16] = {0};
static uint8_t txBuf[] = "dupa from C rpi\n\r";

static void printXYZ(uint8_t *buf)
{
  int16_t x = buf[0] | (buf[1] << 8);
  int16_t y = buf[2] | (buf[3] << 8);
  int16_t z = buf[4] | (buf[5] << 8);

  printf("x: %d, y: %d, z: %d\n", x, y, z);
}

int main(void)
{
  printf("Start\n");

  int fd = open(serialName, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd < 0)
  {
    printf("Error opening device: %s\n", serialName);
    return 0;
  }

  // This is working
  // int bytesWrite = write(fd, txBuf, sizeof(txBuf));
  // printf("Bytes write count: %d\n", bytesWrite);

  fcntl(fd, F_SETFL, 0);
  

  uint8_t c = 0;
  int bytesRead = 0;
  int totalBytesRead = 0;
  uint8_t *p = rxBuf;
  uint8_t i = 0;

  do
  {
    bytesRead = read(fd, (void *)&c, 1);
    if (bytesRead > 0)
    {
      if (c == END_BYTE)
      {
        printXYZ(rxBuf);
        i = 0;
        memset(rxBuf, 0, sizeof(rxBuf));
      }
      else
      {
        rxBuf[i++] = c;
      }
    }
  } while (1);

  // printf("Bytes read count: %d\n", totalBytesRead);
  // printf("Data read: %s\n", rxBuf);

  close(fd);

	return 0;
}

