#pragma once

// 1. 定义数据类型列表

#define HTTP_METHODS \
    X(HTTP_GET, "GET") \
    X(HTTP_POST, "POST") \
    X(HTTP_HEAD, "HEAD") \
    X(HTTP_PUT, "PUT") \
    X(HTTP_CONNECT, "CONNECT") \
    X(HTTP_TRACE, "TRACE") \
    X(HTTP_DELETE, "DELETE") \
    X(HTTP_OPTIONS, "OPTIONS")

#define X(val, desc) val,

typedef enum { HTTP_METHODS HTTP_UNKNOWN } http_method_t;

#undef X

// 2. 定义字符串数组

#define X(val, desc) desc,

static const char * http_method_infos[] = {HTTP_METHODS};

#undef X

// 3. enum to str
const char * mhd_to_str(http_method_t mhd);

// 4. str to enum

http_method_t str_to_mhd(const char * str);
