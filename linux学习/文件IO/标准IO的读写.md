## 标准IO的读写

**流支持不同的读写方式:**
读写一个字符:fgetc() /fputc()一次读/写一个字符

读写一行:fgets()和fputs()一次读/写一行

读写若干个对象:fread()/fwrite()每次读/写若干个对象,每个对象具有相同的长度.

**下列函数用来输入一个字符:**

#include<stdio.h>

int fgetc(FILE*stream);

int getc(FILE*stream);

int getchar(void);

成功时返回读取的字符;若到文件末尾或出错时返回EOF(-1)

getchar()等同于fgetc(stdin)

getc和fgetc区别一个是宏一个是函数.

##### 标准IO输出:

**下列函数用来输出一个字符:**

#include <stdio.h>

int fputc(int c,FILE*stream);

int putc(int c,FILE*stream);

int putchar(int c);

成功时返回写入的字符;出错时返回EOF

putchar(c)等同于fputc(c,stdout)



按行输入:

下列函数用来输入一行:

#include<stdio.h>

char *gets(char *s);

char *fgets(char *s,int size,FILE *stream);

成功时返回s,到文件末尾或出错时返回NULL

gets使用容易造成缓冲区溢出

遇到\n或已输入size-1个字符时返回,总是包含\0



按行输出:

int puts(const char *s);

int fputs(const char *s,FILE *stream);





按对象读写:

size_t fread(void *ptr,size_t size,size_t n,FILE *fp);

size_t fwrite(const void *ptr,size_t size,size_t n,FILE *fp);

成功返回读写的对象的个数,出错时返回EOF,既可以读写文本文件,也可以读写数据文件