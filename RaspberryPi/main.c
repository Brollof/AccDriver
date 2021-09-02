#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "accel.h"

int main(void)
{
  printf("Start\n");
  
  accel_t data = {0};
  if (accInit() == true)
  {
    printf("acc initialized\n");
  }
  else
  {
    printf("acc init ERROR!\n");
  }

  data = accGetData();
  accPrint(&data);

  accDeinit();
  return 0;
}
