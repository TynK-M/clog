#ifdef CLOG

/*
 * Needed dependencies.
 */
#include <stdio.h>

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

#define LOG_LEVELS(X) \
    X(DEBUG, debug)   \
    X(INFO, info)     \
    X(WARNING, warn)  \
    X(ERROR, err)     \
    X(CRITICAL, crit)
#undef X

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

/*
 * Main macro of the library.
 * It creates the various clog_*(* = debug/info/warn/err/crit).
 */
#define MAKE_LOG_FUNCTIONS(clog_level, func_name) \
void clog_##func_name(CLogger logger, const char *message) { \
    if (logger.level <= clog_level) { \
        printf("[%s] %s\n", #clog_level, message); \
    } \
}

LOG_LEVELS(MAKE_LOG_FUNCTIONS)

#undef X

#ifdef CLOG_DEBUG
/*
 * Function used for debug, it shows the level of the CLogger.
 */
const char *get_level(CLogger clog) {
    switch (clog.level) {
        #define CASE(enum_level, func_name) case enum_level: return #enum_level;
        LOG_LEVELS(CASE)
        #undef CASE
        default: return "UNWANTED RESULT";
    }
}

/*
 * Standard output for using debug features without CLOG_DEBUG defined.
 */
#else
static inline const char *get_level(CLogger clog) {
    return "CLOG_ERROR: get_level requires defined CLOG_DEBUG";
}
#endif // CLOG_DEBUG

#endif // CLOG

/*
   Version history:
   0.0.4 (21/08/2025) :
    - Added the macro LOG_LEVELS to have the possibilty to get bot the uppercase and lowercase name of the level.
    - Changed the get_level() to use LOG_LEVELS
    - Added the macro MAKE_LOG_FUNCTIONS that creates all the different main functions to log.
    - Added the LICENSE inside clog.h
    - Wrote the README.md
   0.0.3 (21/08/2025) :
    - Added versioning information inside clog.h
    - Introduced CLOG_DEBUG flag
    - Moved get_level() under CLOG_DEBUG
    - Added compile-time error if debug functions are used without CLOG_DEBUG
   0.0.2 (20/08/2025) : https://github.com/TynK-M/clog/compare/v0.0.1...v0.0.2
   0.0.1 (20/08/2025) : https://github.com/TynK-M/clog/commits/v0.0.1
*/

/*
  MIT License

  Copyright (c) 2025 TynK-M

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/