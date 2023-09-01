#ifndef _CLIENT_H
#define _CLIENT_H

// 客户机参数
typedef struct tag_ClientArgs {
    char const* home;
    int conn;
}   CA;

// 客户机处理
void* client(void* arg);

#endif // _CLIENT_H
