#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "accel.h"

int main(void)
{
  accel_t data = {0};

  if (accInit() == true)
  {
    printf("acc initialized\n");
  }
  else
  {
    printf("acc init ERROR!\n");
    return -1;
  }

  data = accGetData();
  accPrint(&data);
  accDeinit();

  return 0;
}
