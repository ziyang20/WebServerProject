#ifndef _SERVER_H
#define _SERVER_H

// 初始化服务器
int initServer(short port);

// 运行服务器
int runServer(char const* home);

// 终结化服务器
void deinitServer(void);

#endif // _SERVER_H
