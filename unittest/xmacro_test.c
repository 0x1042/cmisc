#include "xmacro.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/options.h>
#include <string.h>

Test(http_mhd, to_str) {

  {
    const char *tmp = mhd_to_str(HTTP_GET);
    cr_log_info("HTTP_GET %s ", tmp);
    cr_assert(tmp, "GET");
  }

  {
    const char *tmp = mhd_to_str(HTTP_CONNECT);
    cr_log_info("HTTP_CONNECT %s ", tmp);
    cr_assert(tmp, "CONNECT");
  }
}

Test(http_mhd, from_str) {
  {
    http_method_t tmp = str_to_mhd("GET");
    cr_log_info("GET %d ", tmp);
    cr_assert_eq(tmp, HTTP_GET);
  }
  {
    http_method_t tmp = str_to_mhd("Post");
    cr_log_info("Post %d ", tmp);
    cr_assert_eq(tmp, HTTP_POST);
  }
  {
    http_method_t tmp = str_to_mhd("TRACE");
    cr_log_info("TRACE %d ", tmp);
    cr_assert_eq(tmp, HTTP_TRACE);
  }
}
