/*
 * The clog.c file shows a small working
 * snippet of code using the clog.h library.
 */

#define CLOG
#define RFC822

#include "clog.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

char *get_time(){
  static char buffer[128];
  time_t now = time(NULL);

#ifdef RFC822 // https://www.rfc-editor.org/rfc/rfc82
  struct tm local_tm; 
  struct tm gm_tm;

#if defined(__CYGWIN__) || defined(__unix__) || defined(__APPLE__)
  localtime_r(&now, &local_tm);
  gmtime_r(&now, &gm_tm);
#else
  #error ("Unsupported compiler");
#endif // System

  long offset = (long)difftime(mktime(&local_tm), mktime(&gm_tm));
  int sign = (offset < 0) ? -1 : 1;
  offset = labs(offset);
  int hours = (int)(offset / 3600);
  int mins  = (int)((offset % 3600) / 60);

  static const char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  static const char *mon[]  = {"Jan","Feb","Mar","Apr","May","Jun",
                               "Jul","Aug","Sep","Oct","Nov","Dec"};

  snprintf(buffer, sizeof(buffer),
           "%s, %02d %s %04d %02d:%02d:%02d %+03d%02d",
           wday[local_tm.tm_wday],
           local_tm.tm_mday, mon[local_tm.tm_mon], local_tm.tm_year + 1900,
           local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec,
           (sign < 0 ? '-' : '+'), hours, mins);
  return buffer;
#else
  snprintf(buffer, sizeof(buffer), "%ld", (long)now);
  return buffer;
#endif // RFC822  
}

int main()
{
  //CLogger logger;
  //logger = init_clog(.level=WARNING);

  //clog_info(logger, "That is a info message");
  //clog_debug(logger, "That is a debug message");
  //clog_warn(logger, "That is a warning message");

  printf("%s", get_time());

  return 0;
}
