#include <stdio.h>
#include <string.h>

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/logging.h>

#include "hashtable.h"
#include "trace.h"

Test(ht, init) {
    hash_table_t * ht = new_ht(16, str_hash, str_equal, free, free);

    cr_assert(ht != NULL);
    cr_expect_eq(ht->capacity, 16);
}

Test(ht, size) {
    hash_table_t * ht = new_ht(16, str_hash, str_equal, free, free);

    ht_put(ht, "hello", "world");
    cr_expect_eq(ht->size, 1);

    ht_put(ht, "hello1", "world1");
    cr_expect_eq(ht->size, 2);
}

Test(ht, get) {
    hash_table_t * ht = new_ht(16, str_hash, str_equal, free, free);

    ht_put(ht, "hello", "world");

    void * val = ht_get(ht, "hello");

    const char * real_val = (const char *)val;

    const char * world = "world";

    cr_log_info("real val is %s %lu %d", real_val, strlen(real_val), strcmp(real_val, world) == 0);

    cr_expect(strcmp(real_val, "world") == 0);
}

Test(ht, resize) {
    hash_table_t * ht = new_ht(4, str_hash, str_equal, free, free);

    for (int i = 1; i < 10; i++) {
        char str[5];
        snprintf(str, sizeof(str), "%d", i + 1);

        char * key = strdup(str);
        int * value = malloc(sizeof(int));
        *value = ((i + 1) * 100);
        ht_put(ht, key, value);
    }

    debug_ht(ht);

    ht_del(ht);
}
