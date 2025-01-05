#include "generic_select.h"

#include <math.h>

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/options.h>

Test(gc, tynename) {
    {
        int64_t id = 123321;
        cr_log_info("%s type name is %s", STR(id), TYPE_NAME(id));
    }

    {
        double pi = 3.141592653;
        cr_log_info("%s type name is %s", STR(pi), TYPE_NAME(pi));
    }
}

Test(gc, abs) {
    {
        int64_t id = -123321;
        cr_log_info("%s abs is %lld", STR(pi), ABS(id));
    }

    {
        double pi = -3.141592653;
        cr_log_info("%s abs is %f", STR(pi), ABS(pi));
    }
}
