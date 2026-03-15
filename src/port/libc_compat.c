// PC-compatible implementation of N64 libc functions
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// N64 SDK's _Printf signature:
// int _Printf(char *(*prout)(char*, const char*, size_t), char *arg, const char
// *fmt, va_list args);
//
// prout: output function that copies 'size' bytes from 'src' to wherever 'dest'
// points,
//        returns pointer to next position
// arg: initial destination argument passed to prout
// fmt: format string
// args: va_list of arguments

typedef char *(*outfun)(char *, const char *, size_t);

int _Printf(outfun prout, char *arg, const char *fmt, va_list args) {
  char buf[1024];
  int len;

  // Format the string using standard vsnprintf
  len = vsnprintf(buf, sizeof(buf), fmt, args);

  if (len < 0) {
    return 0;
  }

  if (len >= (int)sizeof(buf)) {
    len = sizeof(buf) - 1;
  }

  // Call the output function with the formatted result
  if (prout != NULL && len > 0) {
    prout(arg, buf, len);
  }

  return len;
}

#ifdef _WIN32
// bcopy for Windows
void bcopy(const void* src, void* dest, size_t n) {
    memmove(dest, src, n);
}
#endif