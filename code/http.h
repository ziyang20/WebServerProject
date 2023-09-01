#ifndef _HTTP_H
#define _HTTP_H

#include <sys/types.h>
#include <limits.h>

// HTTP请求
typedef struct tag_HttpRequest {
    char method[32];       // 方法
    char path[PATH_MAX+1]; // 路径
    char protocol[32];     // 协议
    char connection[32];   // 连接
}   HTTP_REQUEST;

// 解析请求
int parseRequest(char const* req, HTTP_REQUEST* hreq);

// HTTP响应
typedef struct tag_HttpRespond {
    char  protocol[32];   // 协议
    int   status;         // 状态
    char  desc[256];      // 描述
    char  type[32];       // 类型
    off_t length;         // 长度
    char  connection[32]; // 连接
}   HTTP_RESPOND;

// 构造响应头
void constructHead(HTTP_RESPOND const* hres, char* head);

#endif // _HTTP_H
