#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#define __USE_GNU
#include <string.h>
#include <time.h>

#include "http.h"

// 解析请求
int parseRequest(char const* req, HTTP_REQUEST* hreq) {
    /*
    GET / HTTP/1.1\r\n
    Host: localhost:8000\r\n
    User-Agent: Mozilla/5.0\r\n
    Accept: text/html\r\n
    Connection: keep-alive\r\n
    \r\n
    ...
    */
    sscanf(req, "%s%s%s", hreq->method, hreq->path,
        hreq->protocol);
    char* connection = strcasestr(req, "connection");
    if (connection)
        sscanf(connection, "%*s%s", hreq->connection);
    printf("%d.%ld> [%s][%s][%s][%s]", getpid(),
        syscall(SYS_gettid), hreq->method, hreq->path,
        hreq->protocol, hreq->connection);

    if (strcasecmp(hreq->method, "get")) {
        printf("%d.%ld> 无效方法\n", getpid(),
            syscall(SYS_gettid));
        return -1;
    }

    if (strcasecmp(hreq->protocol, "http/1.0") &&
        strcasecmp(hreq->protocol, "http/1.1")) {
        printf("%d.%ld> 无效协议\n", getpid(),
            syscall(SYS_gettid));
        return -1;
    }

    return 0;
}

// 构造响应头
void constructHead(HTTP_RESPOND const* hres, char* head) {
    /*
    HTTP/1.1 200 OK\r\n
    Server: Tarena WebServer 1.0\r\n
    Date: Tue, 12 Nov 2019 06:33:00 GMT\r\n
    Content-Type: text/html\r\n
    Connection: keep-alive\r\n
    \r\n
    ...
    */
    char dateTime[32];
    time_t now = time(NULL);
    strftime(dateTime, sizeof(dateTime),
        "%a, %d %b %Y %T GMT", gmtime(&now));

    sprintf(head,
        "%s %d %s\r\n"
        "Server: Tarena WebServer 1.0\r\n"
        "Date: %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "Connection: %s\r\n\r\n",
        hres->protocol, hres->status, hres->desc,
        dateTime, hres->type,
        hres->length,
        hres->connection);
}
