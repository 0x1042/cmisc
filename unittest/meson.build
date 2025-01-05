libcriterion = dependency(
    'criterion',
    method: 'pkg-config',
    required: true,
)

# samples = [
#     'xmacro_test.c',
#     'generic_select_test.c',
#     'hash_table_test.c',
# ]

samples = {
    'xmacro_test.c': {
        'inc': lib_xmacro_api,
        'lib': libxmacro,
    },
    'generic_select_test.c': {
        'inc': lib_xmacro_api,
        'lib': libxmacro,
    },
    'hash_table_test.c': {
        'inc': lib_ht_api,
        'lib': libht,
    },
}

foreach name, lib : samples
    e = executable(
        name + '.ut',
        name,
        dependencies: [libcriterion],
        include_directories: lib['inc'],
        link_with: lib['lib'],
    )
    test(
        name,
        e,
        args: [
            '--verbose',
            '--full-stats',
        ],
    )
endforeach
