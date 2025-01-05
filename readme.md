# meson 编译控制宏

- [meson 编译控制宏](#meson-编译控制宏)
  - [macro](#macro)
  - [get option](#get-option)
  - [add option](#add-option)
  - [use](#use)

## macro

```c
#ifdef TRACE
#    define DEBUG(fmt, ...) \
        printf("\033[36m[DEBUG] %s:%d %s " fmt "\033[0m\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#    define DEBUG(fmt, ...)
#endif
```

## get option

```meson
enable_trace = get_option('trace')

if enable_trace
    add_project_arguments('-DTRACE', language: 'c')
endif
```

##  add option

```python
// meson_options.txt
option('trace', type: 'boolean', value: false)
```

## use

```
meson setup {{target}} -Db_sanitize=address -Db_lundef=false -Dtrace=true
```
