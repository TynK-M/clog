/*
 * The clog.c file shows a small working
 * snippet of code using the clog.h library.
 */

#define CLOG

#include "clog.h"

int main(int argc, char *argv[])
{
  CLogger logger;
  logger = init_clog(.level=DEBUG);

  clog_info(logger, "message");
  clog_debug(logger, "message");
  clog_warn(logger, "message");

  return 0;
}
