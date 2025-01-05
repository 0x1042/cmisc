#include "xmacro.h"

#include <string.h>

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/options.h>

Test(http_mhd, to_str1) {
    const char * tmp = mhd_to_str(HTTP_GET);
    cr_log_info("HTTP_GET %s ", tmp);
    cr_assert(tmp, "GET");
}

Test(http_mhd, to_str2) {
    const char * tmp = mhd_to_str(HTTP_CONNECT);
    cr_log_info("HTTP_CONNECT %s ", tmp);
    cr_assert(tmp, "CONNECT");
}

Test(http_mhd, from_str1) {
    http_method_t tmp = str_to_mhd("GET");
    cr_log_info("GET %d ", tmp);
    cr_assert_eq(tmp, HTTP_GET);
}

Test(http_mhd, from_str2) {
    http_method_t tmp = str_to_mhd("Post");
    cr_log_info("Post %d ", tmp);
    cr_assert_eq(tmp, HTTP_POST);
}

Test(http_mhd, from_str3) {
    http_method_t tmp = str_to_mhd("TRACE");
    cr_log_info("TRACE %d ", tmp);
    cr_assert_eq(tmp, HTTP_TRACE);
}
