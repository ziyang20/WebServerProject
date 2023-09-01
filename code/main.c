#include <stdio.h>
#include <stdlib.h>

#include "server.h"

// WebServer 80 ../home
// WebServer 80
// WebServer
int main(int argc, char* argv[]) {
    // 初始化服务器
    if (initServer(argc < 2 ? 80 : atoi(argv[1])) == -1)
        return EXIT_FAILURE;

    // 运行服务器
    if (runServer(argc < 3 ? "../home" : argv[2]) == -1)
        return EXIT_FAILURE;

    // 终结化服务器
    deinitServer();

    return EXIT_SUCCESS;
}
