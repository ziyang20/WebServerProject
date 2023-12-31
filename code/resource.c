#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>

#include "resource.h"
#include "mime.h"

// 搜索资源
int searchResource(char const* path) {
    return access(path, R_OK);
}

// 识别类型
int indentifyType(char const* path, char* type) {
    char* suffix = strchr(path, '.');
    if (!suffix) {
        printf("%d.%ld> 无法获取文件扩展名\n", getpid(),
            syscall(SYS_gettid));
        return -1;
    }

    size_t i;
    for (i = 0; i < sizeof(s_mime) / sizeof(s_mime[0]);
        ++i)
        if (!strcasecmp(suffix, s_mime[i].suffix)) {
            strcpy(type, s_mime[i].type);
            return 0;
        }

    printf("%d.%ld> 不可识别的资源类型：%s\n", getpid(),
        syscall(SYS_gettid), suffix);
    return -1;
}
