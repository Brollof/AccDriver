#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "accel.h"


static int serialPort = 0;

static void printXYZ_raw(uint8_t *buf)
{
  int16_t x = buf[0] | (buf[1] << 8);
  int16_t y = buf[2] | (buf[3] << 8);
  int16_t z = buf[4] | (buf[5] << 8);

  printf("x: %d, y: %d, z: %d\n", x, y, z);
}

void accPrint(accel_t *data)
{
  printf("x: %d, y: %d, z: %d\n", data->x, data->y, data->z);
}
 
bool accInit(void)
{
  serialPort = serialOpen("/dev/serial0", 9600);
  if (serialPort < 0)
  {
    return false;
  }

  if (wiringPiSetup() == -1)
  {
    serialClose(serialPort);
    return false;
  }

  return true;
}

accel_t accGetData(void)
{
	uint8_t buf[16] = {0};
	uint8_t i = 0;
	uint8_t c = 'g'; // get data
	accel_t data = {0};

	serialPutchar(serialPort, c);

	while (i < ACC_DATA_LEN)
	{
		int count = serialDataAvail(serialPort);
		while (count > 0)
		{
			count--;
			buf[i++] = serialGetchar(serialPort);
		}
	}	
	
  data.x = buf[0] | (buf[1] << 8);
  data.y = buf[2] | (buf[3] << 8);
  data.z = buf[4] | (buf[5] << 8);

  printXYZ_raw(buf);
  accPrint(&data);

	return data;	
}

void accDeinit(void)
{
  serialClose(serialPort);
}

