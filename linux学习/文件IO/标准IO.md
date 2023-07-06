# 文件IO

**文件基础:**

概念:一组相关数据的集合

**linux文件类型:**

- 常规类型 r
- 目录文件 d
- 字符设备文件 c
- 块设备文件 b
- 管道文件 p
- 套接字文件 s
- 符号链接文件 l



![image-20230706173153967](D:\Git\git-space\linux学习\imgs\image-20230706173153967.png)

**系统调用**（System Call）是操作系统提供给应用程序的一种编程接口，用于访问操作系统的服务功能。应用程序通过系统调用来请求操作系统执行特定的操作，如文件操作、网络通信、进程管理等。
系统调用是应用程序与操作系统之间的接口，它隐藏了底层操作系统的实现细节，提供了一组规范的函数调用接口。



#### 标准IO-流

FILE:

标准IO用一个结构体类型来存放打开的文件的相关信息

标准IO的所有操作都是围绕FILE来进行

流(stream)

FILE又被称为流(stream),分为文本流和二进制流.

**流的缓冲类型:**

- 全缓冲:当流的缓冲区无数据或无空间时才执行实际IO操作
- 行缓冲:当在输入和输出中遇到换行符(\n)时,进行IO操作
- 无缓冲:数据直接写入文件,流不进行缓冲

标准IO预定三个流,标准输入流 stdin ,标准输出流 stdout,标准错误流 stderr

![image-20230706175303991](D:\Git\git-space\linux学习\imgs\image-20230706175303991.png)

通过测试,缓冲区大小为1024个字节,当缓冲区未满遇到换行符\n时会进行行缓冲.





#### 文件的打开与关闭:

打开就是占用资源

关闭就是释放资源

**打开文件:**

FILE*fopen(const char *path,const char *mode);

Path:

普通文件当前路径不需要加目录,,其他要使用完整的路径

Mode参数:

- r 只读方式 
- w 写方式:若文件存在,长度清零,若不存在则创建文件.
-  a 读写:以读写方式打开文件,若文件不存在则创建,写的数据被追加到文件末尾.
- r+:以读写方式打开文件,文件必须存在

成功时返回流指针,出错时返回NULL,使用fopen函数必须先判断文件是否为空.



![image-20230706182057125](D:\Git\git-space\linux学习\imgs\image-20230706182057125.png)

![image-20230706182025838](D:\Git\git-space\linux学习\imgs\image-20230706182025838.png)

这里我定义了一个文件流指针fp,用来接收fopen函数的返回值,以只读的方式打开pointer.c文件.

**标准IO-处理错误信息:**

extern int errno;

void perror(const char *s);

char *strerror(int errno);

errno存放错误号,由系统生成

perror先输出字符串s,再输出错误号对应的错误信息

strerror根据错误号返回对应的错误信息

perror库函数 头文件 stdio.h

strerror库函数 头文件 errno.h string.h



![image-20230706184247362](D:\Git\git-space\linux学习\imgs\image-20230706184247362.png)

![image-20230706184337744](D:\Git\git-space\linux学习\imgs\image-20230706184337744.png)

**关闭文件:**

int fclose(LILE *stream);

fclose()调用成功返回0,失败返回EOF,并设置errno

流关闭时自动刷新缓冲中的数据并释放缓冲区

当一个程序正常终止时,所有打开的流都会关闭

流一旦关闭后就不能执行任何操作

![image-20230706204141327](D:\Git\git-space\linux学习\imgs\image-20230706204141327.png)

![image-20230706204109317](D:\Git\git-space\linux学习\imgs\image-20230706204109317.png)

