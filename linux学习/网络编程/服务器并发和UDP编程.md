服务器并发和UDP编程:

 通过多线程方式实现:

在之前的代码上改进,在等待客户端请求函数accept执行成功之后创建一个新线程,将读取打印添加到子线程函数中,实现并发

```c
#include "socket.h"
#define SERV_PORT 5248
#define SERV_IP_ADDR "192.168.118.148"
int main(){
        int fd;
        char buff[32];
        struct sockaddr_in sin;
        pthread_t pid;
        if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
                perror("socket");
                exit(1);
        }

        bzero(&sin,sizeof(sin));
        sin.sin_family=AF_INET;
        sin.sin_port=htons(SERV_PORT);
        sin.sin_addr.s_addr=inet_addr(SERV_IP_ADDR);//inet_addr only used IPV4
        if(inet_pton(AF_INET,SERV_IP_ADDR,&sin.sin_addr)!=1){
                perror("inet_pton");
                exit(1);
        }
    
       if(bind(fd,(struct sockaddr*)&sin,sizeof(sin))<0){
                perror("bind");
                exit(1);
        }
        listen(fd,5);
        int newfd;
        int red;

void cli_data_handle(void *arg){
int newfd=*(int*)arg;
printf("handerler thread:newfd:%d\n",newfd);
while(1){
 bzero(buff,sizeof(buff));
 do{
     red=read(newfd,buff,32);
   }while(red<0&&EINTR==errno);
        if(red<0){
                perror("read");
                exit(1);
        }
 printf("read:%s\n",buff);
}
}
while(1){
newfd=accept(fd,NULL,NULL);
char ipv4_addr[32];
inet_ntop(AF_INET,(void *)&sin.sin_addr,ipv4_addr,sizeof(sin));
printf("clinet(%s:%d\n)",ipv4_addr,htons(sin.sin_port));
if(newfd<0){
                perror("accept");
                exit(1);
        }
pthread_create(&pid,NULL,(void *)cli_data_handle,(void *)&newfd );

}
close(fd);
return 0;
}
```

通过多进程实现并发:

```c
#include "socket.h"
#define SERV_PORT 5248
#define SERV_IP_ADDR "192.168.118.148"
int main(){
        int fd;
        char buff[32];
        struct sockaddr_in sin;
        pid_t pid;
        if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
                perror("socket");
                exit(1);
        }

        bzero(&sin,sizeof(sin));
        sin.sin_family=AF_INET;
        sin.sin_port=htons(SERV_PORT);
        sin.sin_addr.s_addr=inet_addr(SERV_IP_ADDR);//inet_addr only used IPV4
        if(inet_pton(AF_INET,SERV_IP_ADDR,&sin.sin_addr)!=1){
                perror("inet_pton");
                exit(1);
        }
    
       if(bind(fd,(struct sockaddr*)&sin,sizeof(sin))<0){
                perror("bind");
                exit(1);
        }
        listen(fd,5);
        int newfd;
        int red;

while(1){
newfd=accept(fd,NULL,NULL);
char ipv4_addr[32];
inet_ntop(AF_INET,(void *)&sin.sin_addr,ipv4_addr,sizeof(sin));
printf("clinet(%s:%d\n)",ipv4_addr,htons(sin.sin_port));
if(newfd<0){
                perror("accept");
                exit(1);
        }
pid =fork();

if(pid<0){
perror("fork");
exit(1);
}
else if(pid==0){
        while(1){
                red=read(newfd,buff,sizeof(buff));
                if(red<0){
                        perror("read");
                        exit(1);
                }
                printf("handerler thread:newfd:%d\n",newfd);
                printf("read:%s\n",buff);
        }
}
else if(pid>0){
close(newfd);
}
}
```

UDP编程:

- `htonl()`和`ntohl()`函数：用于将32位无符号整数从本地字节序转换为网络字节序，以及从网络字节序转换为本地字节序。
- `htons()`和`ntohs()`函数：用于将16位无符号整数从本地字节序转换为网络字节序，以及从网络字节序转换为本地字节序。
- `inet_pton()`函数：用于将字符串形式的IP地址转换为二进制格式的网络地址。
- `inet_ntop()`函数：用于将二进制格式的网络地址转换为字符串形式的IP地址。
- `inet_addr()`函数：已经过时，不推荐使用。可以使用`inet_aton()`函数代替。用于将字符串形式的IP地址转换为32位二进制格式的网络地址。
- `inet_aton()`函数：用于将字符串形式的IP地址转换为二进制格式的网络地址。

recvfrom函数:

```c
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
```

该函数接收来自指定套接字的数据，并将其存储在缓冲区`buf`中。它还返回接收到的字节数。如果出现错误，则返回-1。

- `sockfd`：用于接收数据的套接字描述符。
- `buf`：用于存储接收到的数据的缓冲区。
- `len`：缓冲区的长度。
- `flags`：接收数据时使用的标志。可以设置为0。
- `src_addr`：指向一个`struct sockaddr`类型的指针，用于存储发送方的地址信息。
- `addrlen`：指向一个`socklen_t`类型的指针，用于存储`src_addr`的大小。





服务器端:

```
#include "socket.h"
#define SERV_IP_ADDR "192.168.118.148"
#define SERV_PORT 5248
int main(){
struct sockaddr_in sin;
struct in_addr addr;
int fd;
int re;
char buf[32];
if((fd=socket(AF_INET,SOCK_DGRAM,0))<0){
perror("socket");
exit(1);
}
bzero(&sin,sizeof(sin));
sin.sin_family=AF_INET;
sin.sin_addr.s_addr=inet_aton(SERV_IP_ADDR,&addr);
sin.sin_addr=addr;
sin.sin_port=htons(SERV_PORT);
if((re=bind(fd,(struct sockaddr*)&sin,sizeof(sin)))<0){
perror("bind");
exit(1);
}
struct sockaddr_in cin;
socklen_t ssize=sizeof(cin);
while(1){
bzero(buf,sizeof(buf));
if(recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&cin,&ssize)<0){
perror("recvfrom");
continue;
}
char ipv4_addr[16];
inet_ntop(AF_INET,&cin,ipv4_addr,sizeof(ipv4_addr));
printf("recive from (%s:%d),data:%s",ipv4_addr,ntohs(cin.sin_port),buf);

}
return 0;
}
```

```
#include "socket.h"
#define SERV_IP_ADDR "192.168.118.148"

void usage(char *s){
printf("%s serv_ip serv_port\n",s);
printf("\n\t ser_ip:server ip address");
printf("\n\t serv_port:server port(>5000)\n\t");
}

int main(int argc,char**argv){
struct sockaddr_in sin;
int fd;
short port;
char buff[32];

if(argc !=3){
usage(argv[0]);
exit(1);
}
int SERV_PORT=atoi(argv[2]);
if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
perror("socket");
exit(1);
}
bzero(&sin,sizeof(sin));
sin.sin_family=AF_INET;
sin.sin_port=htons(SERV_PORT);
sin.sin_addr.s_addr=inet_addr(SERV_IP_ADDR);
if(inet_pton(AF_INET,SERV_IP_ADDR,&sin.sin_addr)!=1){
perror("inet_pton");
exit(1);
}
connect(fd,(struct sockaddr*)&sin,sizeof(sin));
while(1){
bzero(buff,sizeof(buff));
fgets(buff,sizeof(buff),stdin);
write(fd,buff,32);
}
}
```

