网络采用分层的思想:

每一层实现不同的功能,对上层地数据做透明传输

每一层向上提供服务,同时使用下层提供的服务



各层典型的协议:



网络接口与物理层

MAC地址:48位全球唯一,网络设备的身份标识

ARP/RARP:

ARP（Address Resolution Protocol）和RARP（Reverse Address Resolution Protocol）是两种用于在计算机网络中解析网络层地址和物理层地址之间映射关系的协议。

1. ARP（Address Resolution Protocol）：

   - ARP用于将网络层地址（如IPv4地址）解析为物理层地址（如MAC地址）。
   - 当主机需要发送数据到一个目标主机时，它需要知道目标主机的MAC地址才能发送数据帧。
   - 主机可以通过ARP协议向局域网中的其他主机广播一个ARP请求，请求中包含目标IP地址。
   - 目标主机收到ARP请求后，如果发现自己的IP地址与请求中的目标IP地址匹配，就会向发送方回复一个ARP响应，包含自己的MAC地址。
   - 发送方主机收到ARP响应后，就知道了目标主机的MAC地址，可以使用该地址发送数据。

2. RARP（Reverse Address Resolution Protocol）：

   - RARP用于将物理层地址（如MAC地址）解析为网络层地址（如IPv4地址）。

   - RARP通常用于无盘工作站或网络设备，它们没有存储自己的IP地址，需要通过RARP协议从网络中获取IP地址。

   - 当一个无盘工作站启动时，它会向网络中广播一个RARP请求，请求中包含自己的MAC地址。

   - RARP服务器（通常是在局域网中的一个专用服务器）收到RARP请求后，会查找对应的IP地址，并将其回复给发出请求的设备。

   - 无盘工作站收到RARP响应后，就获得了自己的IP地址，可以在网络中进行通信。

     

     PPP协议:拨号协议



网络层:

Ip地址

IP:IPV4,IPV6

ICMP:internet控制管理协议,ping命令属于ICMP

IGMP:internet分组管理协议,广播,组播



传输层:



应用层:



要区分局域网IP、广播IP和组播IP，可以根据它们的特定规则和地址范围进行判断。

1. 局域网IP：
   - 局域网IP地址通常是私有IP地址，用于在局域网内部进行通信。
   - 私有IP地址范围：
     - IPv4：10.0.0.0 到 10.255.255.255，172.16.0.0 到 172.31.255.255，192.168.0.0 到 192.168.255.255。
     - IPv6：FC00::/7。

2. 广播IP：
   - 广播IP地址用于向一个网络中的所有设备发送广播消息。
   - 广播IP地址的特点是将网络地址的主机位全部置为1。
   - 在IPv4网络中，广播IP地址通常是将网络地址的主机位全部置为1的地址，例如，对于192.168.0.0/24网络，广播IP地址为192.168.0.255。
   - 在IPv6网络中，广播地址被取消，使用多播地址来实现类似的功能。

3. 组播IP：
   - 组播IP地址用于向一组特定设备发送组播消息。
   - 组播IP地址是一种多对多的通信模型，只有那些已经加入到特定组播组的设备才会接收到组播消息。
   - 组播IP地址在IPv4和IPv6网络中都有支持，有特定的地址范围。
   - 在IPv4网络中，组播IP地址范围是224.0.0.0到239.255.255.255。
   - 在IPv6网络中，组播IP地址范围是FF00::/8。

通过检查一个IP地址是否在上述范围内，可以判断它是局域网IP、广播IP还是组播IP。请注意，这些规则是一般性的指导，特定网络环境和配置可能会有不同的规则和限制。

TCP编程API:

##### socket函数:

int socket(int domain,int type,int protocol);

在编程中，`socket()` 函数用于创建套接字（socket）。它是网络编程中常用的函数之一，用于建立网络连接、进行数据传输等操作。`socket()` 函数的参数包括：

1. `domain：指定套接字的地址族，常见的有：
   - `AF_INET`：IPv4 地址族。
   - `AF_INET6`：IPv6 地址族。
   - `AF_UNIX`：UNIX 域地址族。

2. `type`（套接字类型）：指定套接字的类型，常见的有：
   - `SOCK_STREAM`：流式套接字，提供可靠的、面向连接的、基于 TCP 的数据传输。
   - `SOCK_DGRAM`：数据报套接字，提供不可靠的、无连接的、基于 UDP 的数据传输。
   - `SOCK_RAW`：原始套接字，提供对网络协议的直接访问。

3. `protocol`（协议）：指定使用的协议，通常可以省略，由系统自动选择合适的协议。常见的协议有：
   - `0` 或 `IPPROTO_IP`：使用默认的协议。
   - `IPPROTO_TCP`：TCP 协议。
   - `IPPROTO_UDP`：UDP 协议。

`socket()` 函数的返回值是一个整数，即套接字描述符（socket descriptor），用于后续的套接字操作，如绑定地址、监听连接、发送和接收数据等。如果返回值为 `-1`，则表示创建套接字失败，可以通过查看 `errno` 变量获取错误码。



##### bind函数:

int bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);

sockfd:通过socket函数拿到的文件描述符fd

addr:struct sockaddr的结构体变量的地址

addrlen:地址长度



`struct sockaddr` 是一个通用的地址结构体，用于在网络编程中表示各种类型的网络地址。它是在 `<sys/socket.h>` 头文件中定义的，具体定义如下：

```c
struct sockaddr {
    sa_family_t sa_family;    // 地址族，用于指定地址的类型
    char sa_data[14];         // 地址数据，具体格式根据地址族而定
};
```

`struct sockaddr` 结构体的成员包括：

1. `sa_family`：地址族，用于指定地址的类型。可以是以下常见的值之一：
   - `AF_INET`：IPv4 地址族
   - `AF_INET6`：IPv6 地址族
   - `AF_UNIX`：UNIX 域地址族
   - 等等...

2. `sa_data`：地址数据，具体格式根据地址族而定。不同的地址族有不同的数据结构和长度。

`struct sockaddr` 结构体是一个通用的地址结构体，它被用于在网络编程中传递各种类型的地址信息。在实际使用时，通常会将 `struct sockaddr` 转换为具体的地址结构体，如 `struct sockaddr_in`（IPv4 地址结构体）或 `struct sockaddr_in6`（IPv6 地址结构体），以便进行更具体的操作。

`struct sockaddr_in` 是用于表示 IPv4 地址的具体信息的结构体，在网络编程中广泛使用。它是在 `<netinet/in.h>` 头文件中定义的，具体定义如下：

```c
struct sockaddr_in {
    sa_family_t sin_family;       // 地址族，通常为 AF_INET
    in_port_t sin_port;           // 16 位端口号
    struct in_addr sin_addr;      // 32 位 IPv4 地址
    char sin_zero[8];             // 用于填充，通常设置为全零
};
```

`struct sockaddr_in` 结构体的成员包括：

1. `sin_family`：地址族，通常为 `AF_INET`，表示 IPv4 地址族。

2. `sin_port`：16 位端口号，使用网络字节序（big-endian）表示。

3. `sin_addr`：32 位 IPv4 地址，使用网络字节序表示。它是一个 `struct in_addr` 类型的结构体，定义如下：

   ```c
   struct in_addr {
       in_addr_t s_addr;   // 32 位 IPv4 地址
   };
   ```

   `s_addr` 成员存储了实际的 IPv4 地址。

4. `sin_zero`：用于填充字段，通常设置为全零。

`struct sockaddr_in` 结构体用于表示 IPv4 地址的具体信息，包括地址族、端口号和 IPv4 地址。在网络编程中，可以使用 `struct sockaddr_in` 结构体来指定要连接的服务器地址、绑定的本地地址等。通过将其与 `struct sockaddr` 进行类型转换，可以在网络编程中进行地址相关的操作，如建立连接、发送和接收数据等。



`inet_pton` 函数用于将字符串形式的 IP 地址转换为网络字节序的二进制形式。

inet_pton` 函数的原型如下：

```c
int inet_pton(int af, const char *src, void *dst);
```

参数说明：
- `af`：表示地址族（address family），常见的有 `AF_INET` 表示 IPv4 地址族，`AF_INET6` 表示 IPv6 地址族。
- `src`：指向包含人类可读的 IP 地址的字符串的指针。
- `dst`：指向存储转换后 IP 地址的内存区域的指针。

`inet_pton` 函数将字符串形式的 IP 地址转换为网络字节序的二进制形式，并将结果存储在 `dst` 指向的内存区域中。

以下是一个示例，展示了 `inet_pton` 函数的使用：

```c
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    const char *ip = "192.0.2.1";
    struct in_addr addr;
    if (inet_pton(AF_INET, ip, &(addr.s_addr)) <= 0) {
        printf("Invalid address\n");
        return 1;
    }

    printf("IP address in network byte order: 0x%08X\n", addr.s_addr);
    return 0;
}
```

- 如果转换成功，函数返回一个非零值（通常是1）。
- 如果转换失败，函数返回0，并且 `dst` 中的内容是未定义的



##### `listen` 函数用于将一个套接字（socket）转换为被动监听状态，以便接受传入的连接请求。它通常用于服务器端程序中。

在 C 语言的标准库中，`listen` 函数的原型如下：

```c
int listen(int sockfd, int backlog);
```

参数说明：
- `sockfd`：表示要监听的套接字的文件描述符。
- `backlog`：同时允许几路客户端和服务器进行连接的过程 

一般填5,ARM最大为8

##### accept函数:

阻塞等待客户端连接请求

int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);

sockfd 通过socket()创建,并bind(),listen()函数设置过的文件描述符

addr和addrlen

成功时返回已经建立好的newfd



以下是服务器端程序代码:

```c
#include "socket.h"
#define SERV_PORT 5248
#define SERV_IP_ADDR "192.168.118.147"
int main(){
int fd;
char buff[32];
struct sockaddr_in sin;

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
newfd=accept(fd,NULL,NULL);
if(newfd<0){
perror("accept");
exit(1);
}
while(1){
bzero(buff,sizeof(buff));
do{
red=read(newfd,buff,32);
}while(red<0&&EINTR==errno);
if(red<0){
perror("read");
exit(1);
}
if(!red){
break;
}
printf("read:%s\n",buff);
}
close(newfd);
close(fd);
return 0;
}
```

接下来是客户端代码:

```C
#include "socket.h"
#define SERV_PORT 5248
#define SERV_IP_ADDR "192.168.118.147"
int main(){
struct sockaddr_in sin;
int fd;
char buff[32];
if(fd=socket(AF_INET,SOCK_STREAM,0)<0){
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

