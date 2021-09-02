#ifndef __ACCEL_H
#define __ACCEL_H

#include <stdbool.h>
#include <stdint.h>

#define ACC_DATA_LEN 6 // 2 bytes for each axis

typedef struct accel_s
{
  int16_t x, y, z;
} accel_t;


bool accInit(void);
accel_t accGetData(void);
void accDeinit(void);
void accPrint(accel_t *data);

#endif
