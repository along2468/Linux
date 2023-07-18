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