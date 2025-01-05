lib_xmacro_sources = files(
    'generic_select.c',
    'generic_select.h',
    'xmacro.c',
    'xmacro.h',
)

lib_xmacro_api = include_directories('.')

libxmacro = shared_library(
    'xmacro',
    lib_xmacro_sources,
    include_directories: [lib_xmacro_api],
    dependencies: [],
)
