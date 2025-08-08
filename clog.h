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

/*
 * CLOG_OPTIONS:
 * Set of options to modify pre-defined parts of the logger.
 */
#ifdef CLOG_OPTIONS

CLogger set_clog_level(CLogger *clog, CLog_Level level){
  clog->level = level;
}

#endif // CLOG_OPTIONS

CLogger init_clog(){
  CLogger clog;
  clog.level = INFO;
  return clog;
}

#endif // CLOG
