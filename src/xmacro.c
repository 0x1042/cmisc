#include "xmacro.h"
#include <string.h>

// 3. enum to str
const char *mhd_to_str(http_method_t mhd) {
  if (mhd >= 0 && mhd < HTTP_UNKNOWN) {
    return http_method_infos[mhd];
  }

  return "UNKNOWN";
}

// 4. str to enum

http_method_t str_to_mhd(const char *str) {
  for (int i = 0; i < HTTP_UNKNOWN; i++) {
    if (strcasecmp(str, http_method_infos[i]) == 0) {
      return (http_method_t)i;
    }
  }
  return HTTP_UNKNOWN;
}
