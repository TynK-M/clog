#define CLOG

#include "clog.h"

int main(int argc, char *argv[])
{
  CLogger logger;
  logger = init_clog(.level=WARNING);

  clog_info(logger, "message");
  clog_debug(logger, "message");
  clog_warn(logger, "message");

  return 0;
}
