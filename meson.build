project(
    'cmisc',
    'c',
    version: '1.0.0',
    default_options: [
        'warning_level=3',
        'c_std=c2x',
    ],
)

cc = meson.get_compiler('c')
message('compiler:', cc.get_id())
message('compiler version:', cc.version())
message('compiler linker:', cc.get_linker_id())

thread_dep = dependency('threads')

enable_trace = get_option('trace')

message('enable_trace:', enable_trace)

if enable_trace
    add_project_arguments('-DTRACE', language: 'c')
endif

subdir('src')
subdir('hashtable')
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
