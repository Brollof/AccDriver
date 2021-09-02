#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "accel.h"

int msleep(long tms)
{
  struct timespec ts;
  int ret;

  if (tms < 0)
  {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = tms / 1000;
  ts.tv_nsec = (tms % 1000) * 1000000;

  do
  {
    ret = nanosleep(&ts, &ts);
  } while (ret && errno == EINTR);

  return ret;
}

int main(int argc, char *argv[])
{
  accel_t data = {0};
  bool loop = false;
  int opt;

  if (accInit() == true)
  {
    printf("Init done\n");
  }
  else
  {
    printf("Init ERROR!\n");
    return -1;
  }

  while ((opt = getopt(argc, argv, "l")) != -1)
  {
    switch (opt)
    {
      case 'l':
        printf("loop mode\n");
        loop = true;
        break;				
      default:
        fprintf(stderr, "Usage: %s [-l]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  do
  {
    data = accGetData();
    accPrint(&data);

    if (loop)
      msleep(500);

  } while (loop);

  accDeinit();
  return 0;
}
