libcriterion = dependency(
    'criterion',
    method: 'pkg-config',
    required: true,
)

samples = [
    'xmacro_test.c',
    'generic_select_test.c',
]

foreach sample : samples
    e = executable(
        sample + '.bin',
        sample,
        dependencies: [libcriterion],
        include_directories: [libxmacro_api],
        link_with: [libxmacro],
    )
    test(
        sample,
        e,
        args: [
            '--verbose',
            '--full-stats',
        ],
    )
endforeach
