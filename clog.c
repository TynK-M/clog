#include <stdio.h>
#include "clog.h"

int main(int argc, char *argv[])
{
  CLogger logger;
  logger = init_clog(.level= DEBUG);

  printf("%s", get_level(logger));

  return 0;
}
