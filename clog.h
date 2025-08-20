#ifndef CLOG
#define CLOG 

/*
 * CLOG LEVELS:
 * DEBUG, detailed diagnostic info
 * INFO, general runtime events
 * WARNING, unexpected non-critical issues
 * ERROR, serious problems that affect functionality
 * CRITICAL, severe errors causing shutdown
 */
typedef enum {
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL
} CLog_Level;

/*
 * CLOG LOGGER:
 * A basic logging structure for capturing log messages at a specific log level.
 *
 * Members:
 * - level: The current logging level defined by CLog_Level.
 * - items: Pointer to a dynamically allocated array of log message strings, timestamp, uuid, etc.
 * - count: The number of items currently hold.
 */
typedef struct{
  CLog_Level level;
  char *items;
  size_t count;
} CLogger;

char *get_level(CLogger clog){
  switch (clog.level) {
    case 0:
      return "DEBUG";
    case 1:
      return "INFO";
    case 2:
      return "WARNING";
    case 3:
        return "ERROR";
    case 4:
        return "CRITICAL";
    default:
      break;
  }

  return "UNWANTED RESULT";
}

typedef struct{
  CLog_Level level;
} Init_Params;

/*
 * Shoutout to 
 * Vjekoslav Krajačić(@vkrajacic on X, https://x.com/vkrajacic/status/1749816169736073295) for this useful macro
 * and to 
 * Tsoding(@tsoding on X, "Syntax You Never Heard About" ~ Tsoding Daily on YouTube) for showing it in a video.
 */
CLogger init_clog_(Init_Params params);
#define init_clog(...) \
  init_clog_((Init_Params) {.level = INFO, __VA_ARGS__} )

CLogger init_clog_(Init_Params params){
  CLogger clog;
  clog.level = params.level;
  return clog;
}

#endif // CLOG
