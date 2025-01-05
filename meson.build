project(
    'cmisc',
    'c',
    version: '1.0.0',
    default_options: [
        'warning_level=3',
        'c_std=c2x',
    ],
)

thread_dep = dependency('threads')

subdir('src')
subdir('unittest')

executable(
    'cmisc',
    'main.c',
    dependencies: [
        thread_dep,
    ],
    link_with: [
        libxmacro,
    ],
    install: true,
)
