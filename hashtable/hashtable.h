#pragma once

#include <stddef.h>

typedef struct node_t {
    void * key;
    void * value;
    struct node_t * next;
} node_t;

typedef size_t (*fn_hash)(const void *);
typedef bool (*fn_equal)(const void *, const void *);
typedef void (*destructor)(void *);

typedef struct hash_table_t {
    node_t ** buckets;

    size_t size;
    size_t capacity;

    fn_hash hash;
    fn_equal equal;
    destructor key_del;
    destructor val_del;

    // size_t (*fn_hash)(const void * key);
    // bool (*fn_equal)(const void * one, const void * two);
    // void (*fn_del_key)(void * key);
    // void (*fn_del_val)(void * val);
} hash_table_t;

hash_table_t * new_ht(size_t cap, fn_hash hash, fn_equal equal, destructor key_del, destructor val_del);

bool check_resize(hash_table_t * ht);

bool ht_put(hash_table_t * ht, void * key, void * val);

void ht_put_node(hash_table_t * ht, node_t * node);

void * ht_get(hash_table_t * ht, void * key);

bool ht_remove(hash_table_t * ht, void * key);

void ht_clear(hash_table_t * ht);

void ht_del(hash_table_t * ht);

size_t str_hash(const void * key);

bool ht_resize(hash_table_t * ht);

// size_t int_hash(const void * key);

bool str_equal(const void * one, const void * two);

// size_t int_equal(const void * one, const void * two);

void debug_ht(hash_table_t * ht);
