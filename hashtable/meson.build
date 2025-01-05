lib_ht_sources = files(
    'hashtable.c',
    'hashtable.h',
    'trace.h',
)

lib_ht_api = include_directories('.')

libht = shared_library(
    'hashtable',
    lib_ht_sources,
    include_directories: [lib_ht_api],
    dependencies: [],
)
