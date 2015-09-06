#include <string.h>
#include "utils.h"

unsigned char startsWith(const char* prefix, const char* str) {
  size_t lenpre = strlen(prefix),
         lenstr = strlen(str);
  return lenstr < lenpre ? 1 : !(strncmp(prefix, str, lenpre) == 0);
}
