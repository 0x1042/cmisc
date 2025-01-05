#include "hashtable.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trace.h"

hash_table_t * new_ht(size_t cap, fn_hash hash, fn_equal equal, destructor key_del, destructor val_del) {
    hash_table_t * ht = malloc(sizeof(hash_table_t));

    if (!ht) {
        return NULL;
    }

    ht->buckets = calloc(cap, sizeof(node_t *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }

    ht->size = 0;
    ht->capacity = cap;
    ht->hash = hash;
    ht->equal = equal;
    ht->key_del = key_del;
    ht->val_del = val_del;

    DEBUG("new hash table success. capacity:%zu", ht->capacity);
    return ht;
}

bool check_resize(hash_table_t * ht) {
    if (ht->size >= ht->capacity * 3 / 4) {
        return ht_resize(ht);
    }
    DEBUG("not resize. %zu:%zu", ht->capacity, ht->size);
    return true;
}

static void del_node(hash_table_t * ht, node_t * tmp) {
    if (!tmp) {
        return;
    }
    if (ht->key_del) {
        ht->key_del(tmp->key);
    }

    if (ht->val_del) {
        ht->val_del(tmp->value);
    }

    free(tmp);
}

bool ht_put(hash_table_t * ht, void * key, void * val) {
    if (!check_resize(ht)) {
        return false;
    }
    size_t index = ht->hash(key) % ht->capacity;
    node_t * tmp = ht->buckets[index];

    DEBUG("capacity:%zu index:%zu conflict:%d", ht->capacity, index, (tmp != NULL));

    while (tmp) {
        if (ht->equal(tmp->key, key)) {
            DEBUG("conflict. update key %s %s", (const char *)key, (const char *)tmp->key);

            if (ht->val_del) {
                ht->val_del(tmp->value);
            }
            tmp->value = val;
            return true;
        }
        tmp = tmp->next;
    }

    DEBUG("add new key %s %s", (const char *)key, (const char *)val);

    node_t * new_node = malloc(sizeof(node_t));
    if (!new_node) {
        return false;
    }

    new_node->key = key;
    new_node->value = val;
    new_node->next = NULL;
    if (!tmp) {
        ht->buckets[index] = new_node;
    } else {
        tmp->next = new_node;
    }

    ht->size++;

    DEBUG("capacity:%zu add_new index:%zu size:%zu", ht->capacity, index, ht->size);

    return true;
}

void ht_put_node(hash_table_t * ht, node_t * node) {
    size_t index = ht->hash(node->key) % ht->capacity;

    if (!ht->buckets[index]) {
        ht->buckets[index] = node;
    } else {
        node->next = ht->buckets[index];
        ht->buckets[index] = node;
    }

    ht->size++;
}

void * ht_get(hash_table_t * ht, void * key) {
    size_t index = ht->hash(key) % ht->capacity;
    node_t * tmp = ht->buckets[index];
    while (tmp) {
        if (ht->equal(key, tmp->key)) {
            return tmp->value;
        }
        tmp = tmp->next;
    }

    return NULL;
}

bool ht_remove(hash_table_t * ht, void * key) {
    size_t index = ht->hash(key) % ht->capacity;
    node_t * tmp = ht->buckets[index];
    node_t * pre = NULL;

    while (tmp) {
        if (ht->equal(key, tmp->key)) {
            if (pre) {
                pre->next = tmp->next;
            } else {
                ht->buckets[index] = tmp->next;
            }
            del_node(ht, tmp);
            ht->size--;
            return true;
        }
        pre = tmp;
        tmp = tmp->next;
    }
    return false;
}

void ht_clear(hash_table_t * ht) {
    for (size_t i = 0; i < ht->capacity; i++) {
        node_t * tmp = ht->buckets[i];
        while (tmp) {
            node_t * next = tmp->next;

            del_node(ht, tmp);
            tmp = next;
        }

        ht->buckets[i] = NULL;
    }

    ht->size = 0;
}

void ht_del(hash_table_t * ht) {
    if (!ht) {
        return;
    }

    ht_clear(ht);
    free(ht->buckets);
    free(ht);
}

size_t str_hash(const void * key) {
    const char * str = (const char *)key;
    size_t magic = 5381;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        magic = ((magic << 5) + magic) + str[i];
    }
    return magic;
}

// size_t int_hash(const void * key);

bool str_equal(const void * one, const void * two) {
    return strcmp((const char *)one, (const char *)two) == 0;
}

// size_t int_equal(const void * one, const void * two);
//

bool ht_resize(hash_table_t * ht) {
    node_t ** old_buckets = ht->buckets;
    size_t old_cap = ht->capacity;

    node_t ** new_buckets = calloc(ht->capacity * 2, sizeof(node_t *));

    if (!new_buckets) {
        return false;
    }

    ht->buckets = new_buckets;
    ht->capacity = ht->capacity * 2;
    ht->size = 0;

    DEBUG("enable resize. %zu->%zu", old_cap, ht->capacity);

    // copy

    for (size_t i = 0; i < old_cap; i++) {
        node_t * tmp = old_buckets[i];
        while (tmp) {
            node_t * next = tmp->next;
            ht_put_node(ht, tmp);
            tmp = next;
        }
    }

    free(old_buckets);
    return true;
}

void debug_ht(hash_table_t * ht) {
    if (ht->size == 0) {
        printf("empty hash table\n");
        return;
    }

    printf("===============hash table %zu:%zu =============\n", ht->capacity, ht->size);

    size_t cap = ht->capacity;

    for (size_t i = 0; i < cap; i++) {
        node_t * tmp = ht->buckets[i];
        if (!tmp) {
            printf("index:%zu is null\n", i);
            continue;
        }
        while (tmp) {
            node_t * next = tmp->next;
            printf("index:%zu %s->%d\n", i, (const char *)tmp->key, *(int *)tmp->value);
            tmp = next;
        }
    }
    printf("===============hash table=============\n");
}
