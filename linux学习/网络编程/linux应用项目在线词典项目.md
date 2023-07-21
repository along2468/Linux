linux应用项目:在线词典项目



第一步:进行客户端总体设计,包含登录,注册,查询单词,历史记录功能:

```cc
#include "word.h"

#define N 32
#define R 1 //register
#define L 2 //login
#define Q 3 //query

//客户端服务器双方通信结构体
typedef struct {
        int type;
        char name[N];
        char data[256];
}MSG;

void do_register(int socketfd,MSG *msg){
        printf("register...\n");
}
int do_login(int socketfd,MSG *msg){
        printf("login...\n");
        return 1;
}
int do_query(int socketfd,MSG *msg){
printf("query:...\n");
return 1;
}
int do_history(int socketfd,MSG *msg){
        printf("history:...\n");
        return 1;
}
int main(int argc,char *argv[]){
        int n;
        MSG msg;
        int socketfd;
        struct sockaddr_in  skaddr;
        struct in_addr addr;
struct in_addr addr;
    if(argc !=3){
            printf("usage:%s serverip port.\n",argv[0]);
            return -1;
    }

    if((socketfd=socket(AF_INET,SOCK_STREAM,0))<0){
            perror("socket");
            return -1;
    }
    bzero(&skaddr,sizeof(skaddr));
    skaddr.sin_family=AF_INET;
    skaddr.sin_addr.s_addr=inet_aton(argv[1],&addr);
    skaddr.sin_addr=addr;
    skaddr.sin_port=htons(atoi(argv[2]));

    if(connect(socketfd,(struct sockaddr*)&skaddr,sizeof(skaddr))<0){
            perror("connect");
            return -1;

            while(1){

                    printf("****************************************************\n");
                    printf("** 1.register            2.login           3.quit **\n");
                    printf("****************************************************\n");
                    printf("请选择功能:\n");
                    scanf("%d",&n);
```


```c
                    getchar();

                    switch(n){
                            case 1:
                                    do_register(socketfd,&msg);
                                    break;
                            case 2:
                                    if(do_login(socketfd,&msg)==1){
                                            goto next;
                                    }
                                    break;
                            case 3:
                                    close(socketfd);
                                    exit(0);
                                    break;
                            default:
                                    printf("命令错误!!!\n");
                    }
            }
    }
```
```cc
next:
        while(1){
                printf("********************************************************\n");
                printf("* 1.query_word   2.history_record   3.quit  *\n");
                printf("********************************************************\n");
                printf("please choose :\n");
                scanf("%d",&n);
                getchar();
                switch(n){
                        case 1:
                                do_query(socketfd,&msg);
                                break;
                        case 2:
                                do_history(socketfd,&msg);
                                break;
                        case 3:
                                close(socketfd);
                                exit(0);
                                break;
                        default:
                printf("命令错误!!!\n");

}
}
return 0;
}
```

