/*
 * The clog.c file shows a small working
 * snippet of code using the clog.h library.
 */

#define CLOG

#include "clog.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
  RFC822,
  RFC2445
} Clog_Time_Format;

char *get_time(Clog_Time_Format format){
  static char buffer[128];
  time_t now = time(NULL);

  switch(format){
    case RFC822: { // https://www.rfc-editor.org/rfc/rfc822
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
    }

    case RFC2445: {// https://www.rfc-editor.org/rfc/rfc2445 , simplified version without timezone
      struct tm local_tm;
#if defined(__CYGWIN__) || defined(__unix__) || defined(__APPLE__)
      localtime_r(&now, &local_tm);
#else
  #error ("Unsupported compiler");
#endif // System
      snprintf(buffer, sizeof(buffer),
               "%04d%02d%02dT%02d%02d%02d",
               local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday,
               local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec);
      return buffer;
    }

    default: {
      snprintf(buffer, sizeof(buffer), "%ld", (long)now);
      return buffer;
      break;
    }
  }
}

int main()
{
  //CLogger logger;
  //logger = init_clog(.level=WARNING);

  //clog_info(logger, "That is a info message");
  //clog_debug(logger, "That is a debug message");
  //clog_warn(logger, "That is a warning message");

  printf("%s", get_time(RFC2445));

  return 0;
}
