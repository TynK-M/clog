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

typedef struct{
  *char level;
  *char items;
  size_t count;
} CLogger;


#endif // CLOG
