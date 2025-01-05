#pragma once
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// _Generic(expression,association-list)
//
//association-list 对应一组类型和对应表达式的组合,按照,分割
// type1: expression1,
// type2: expression2,
// type3: expression3,

#define TYPE_NAME(x) \
    _Generic( \
        (x), \
        int8_t: "int8_t", \
        int16_t: "int16_t", \
        int32_t: "int32_t", \
        int64_t: "int64_t", \
        uint8_t: "uint8_t", \
        uint16_t: "uint16_t", \
        uint32_t: "uint32_t", \
        uint64_t: "uint64_t", \
        float: "float", \
        double: "double", \
        size_t: "size_t", \
        nullptr_t: "nullptr_t", \
        default: "unknown")

#define FORMATER(x) _Generic((x), int: "%d", double: "%f", char *: "%s", default: "unknown")

#define ABS(x) _Generic((x), int: abs, int64_t: llabs, double: fabs, float: fabs, default: fabs)(x)

#define STR(x) #x
