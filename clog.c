/*
 * The clog.c file shows a small working
 * snippet of code using the clog.h library.
 */

#define CLOG

#include "clog.h"

int main()
{
  CLogger logger;
  logger = init_clog(.level=WARNING);

  clog_info(logger, "That is a info message");
  clog_debug(logger, "That is a debug message");
  clog_warn(logger, "That is a warning message");

  return 0;
}
