标准IO刷新流

int fflush (FILE *fp);

成功时返回0,出错时返回EOF

将流缓冲区中的数据写入实际的文件

linux下只能刷新输出缓冲区,输入缓冲区丢弃



`#include <stdio.h>`

`int main() {`
    `FILE *file = fopen("example.txt", "w");`
    `if (file != NULL) {`
        `fputs("Hello, World!", file);`
        `fflush(file); // 刷新缓冲区，确保数据写入文件`
        `fclose(file);`
    `} else {`
        `printf("Error opening file.\n");`
    `}`

```
return 0;
```

`}`



定位流 :

long ftell(FILE*stream)

long fseek(FILE *stream,long offset, int whence);

void rewind(FILE*stream)

ftell()成功时返回流的当前读写位置,出错时返回EOF

fseek()定位一个流,成功时返回0,出错时返回EOF

whence参数:SEEK_SET/SEEK_CUR/SEEK_END

SEEK_SET 从距文件开头 offset位移量为新的读写位置



格式化输出:

int fprintf(FILE *stream,const char *fmt,...)

int sprintf(char *s,const char *fmt,...)

成功时返回输出的字符个数,出错时返回EOF

格式化输入:

int fscanf(FILE *stream,const char *format,...)

int sscanf(const char *str,const char *format,...)

