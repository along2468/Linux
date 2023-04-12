# NVIC与中断控制（The NVIC and Interrupt Control）

#### NVIC概述：

​         NVIC全称：Nested Vectored Interrupt Controller (矢量中断控制器)，它与CM3内核的逻辑紧密耦合，共同完成对中断的响应，NVIC的寄存器以存储器映射的方式访问，除了包含控制寄存器和中断处理的控制逻辑外，NVIC还包含了MPU的控制寄存器、SysTick定时器以及调试控制。

​        NVIC共支持1-240个外部中断输入，同时NVIC还支持一个永不可屏蔽中断(NMI)输入。NVIC的中断控制和状态寄存器都只能在特权级下访问，但是存在一个例外，软件触发中断寄存器可以在用户级下访问以产生软件中断。所有的中断控制寄存器和状态控制寄存器均可以按字、半字、字节的方式访问。

#### 中断配置：

-  使能和除能  对应的寄存器是SETENA寄存器和CLRENA寄存器
-  悬起和解悬  对应的寄存器是SETPEND寄存器和CLRPEND寄存器
-  优先级          优先级寄存器是PRI寄存器
-  活动状态       活动状态寄存器是ACTIVE寄存器族

​        此外，异常掩蔽寄存器：（PRIMASK和FUAULTMASK以及BASEPRI）,向量表偏移量寄存器，软件触发中断寄存器，优先级分组位段也会对中断处理造成影响。

#### 中断的使能和除能（SETENA寄存器和CLRENA寄存器）：

​        CM3中有240个使能位和240个除能位，每个中断拥有一对，240个对分布在8对32位寄存器中，要想使能一个中断，需将SETENA对应的位设为1，反之，要想除能一个中断，要在CLRENA对应的位写入1。（往SETENA和CLRENA写入0没有任何效果）

![image](https://github.com/along2468/STM32F103-/blob/master/Cortex-M3%E5%AD%A6%E4%B9%A0/imgs/image-20230412001259694.png)
![image](https://github.com/along2468/STM32F103-/blob/master/Cortex-M3%E5%AD%A6%E4%B9%A0/imgs/image-20230412002151876.png)


​       SETENA和CLRENA各有8个，一共是8对，从SETENA0到SETENA7,CLRENA到CLRENA7，若使用的芯片支持32个中断，则只SETENA0和CLRENA0才需要使用，SETENA和CLRENA可以按字，半字，字节方式访问。  特别的SETENA7和CLRENA7分别有16个使能位和16个除能位。

#### 中断的悬起与解悬：（SETPEND和CLRPEND寄存器簇）

​        中断发生时，如果正在处理同级或高级优先级异常，或者被掩蔽，则中断不能立即得到响应，此时中断被悬起。悬起状态通过SETPEND和CLRPEND设置

<img src="C:\Users\ALong\AppData\Roaming\Typora\typora-user-images\image-20230412231406279.png" alt="image-20230412231406279" style="zoom:80%;" />

####  优先级：

​        每个外部中断都有一个对应的优先级寄存器，每个寄存器占用8位，最少只使用高三位，4个相邻寄存器拼成一个32位寄存器。

第0组：所有4位用于指定响应优先级
第1组：最高1位用于指定抢占式优先级，最低3位用于指定响应优先级
第2组：最高2位用于指定抢占式优先级，最低2位用于指定响应优先级
第3组：最高3位用于指定抢占式优先级，最低1位用于指定响应优先级
第4组：所有4位用于指定抢占式优先级

​        优先级被分为高低两个位段，分别是抢占优先级和响应优先级，抢占优先级，其数字越低，优先级越高。相同下比较响应优先级，其数字越低，优先级越高

#### 活动状态：

​          每个外部中断都有一个活动状态位。在处理器执行了其 ISR 的第一条指令后，它的活动位就被置 1，并且直到 ISR 返回时才硬件清零，哪怕一个中断被抢占，其活动状态也依然为 1，活动状态寄存器与前面的使能/除能和悬起/解悬寄存器相同，只是不再成对出现。它们也能按字、半字、字节访问，但他们是**只读**的。

<img src="C:\Users\ALong\AppData\Roaming\Typora\typora-user-images\image-20230412233405255.png" alt="image-20230412233405255" style="zoom:80%;" />

#### PRIMASK 与 FAULTMASK 特殊功能寄存器：

​          PRIMASK 用于除能在 NMI 和硬 fault 之外的所有异常，它有效地把当前优先级改为 0

![image-20230412233715450](D:\Git\git-space\Cortex-M3学习\imgs\image-20230412233715450.png)

​        FAULTMASK更绝，它把当前优先级改为‐1。连硬fault都被掩蔽了。使用方法

与PRIMASK的相似。FAULTMASK会在异常退出时自动清零

掩蔽寄存器动不了NMI,因为NMI是用在最危急的情况下的,系统为它开出单行道。

#### BASEPRI寄存器：

​        BASEPRI寄存器即对中断掩蔽进行更细腻的控制——只掩蔽优先级低于某一阈值的中断——它们的优先级在数字上大于等于某个数。这个数存储在BASEPRI中。如果往BASEPRI中写0，则BASEPRI将停止掩蔽任何中断。

​        使用BASEPRI时，可以任意设置新的优先级阈值；但是使用BASEPRI_MAX时只允许新的优先级阈值比原来的那个在数值上更小，也就是说，只能一次次地扩大掩蔽范围。

#### 其它异常的配置寄存器：

###### 系统Handler控制及状态寄存器SHCSR

<img src="C:\Users\ALong\AppData\Roaming\Typora\typora-user-images\image-20230412234806773.png" alt="image-20230412234806773" style="zoom:80%;" />

​        上表中的活动位虽然也是可写的，但是改动时必须予以极度的小心，否则这是玩火行为

###### 中断控制及状态寄存器ICSR

<img src="C:\Users\ALong\AppData\Roaming\Typora\typora-user-images\image-20230412234925395.png" alt="image-20230412234925395" style="zoom:80%;" />

​       对于NMI、SysTick定时器以及PendSV，可以通过此寄存器手工悬起它们。

#### 软件中断：

​        软件中断，包括手工产生的普通中断，能以多种方式产生。最简单的就是使用相应的

SETPEND寄存器，更专业更快捷的则是通过使用软件触发中断寄存器STIR

#### SysTick定时器：

​        SysTick定时器被捆绑在NVIC中，用于产生SYSTICK异常。为多个任务许以不同数目的时间片，确保没有一个任务能霸占系统；或者把每个定时器周期的某个时间范围赐予特定的任务等，还有操作系统提供的各种定时功能，都与这个滴答定时器有关。因此，需要一个定时器来产生周期性的中断，STCLK的具体来源则由芯片设计者决定，因此不同产品之间的时钟频率可能会大不相同，需要检视芯片的器件手册来决定选择什么作为时钟源。

###### SysTick控制及状态寄存器

<img src="D:\Git\git-space\Cortex-M3学习\imgs\image-20230412235504981.png" alt="image-20230412235504981" style="zoom:80%;" />

###### SysTick重装载数值寄存器

<img src="D:\Git\git-space\Cortex-M3学习\imgs\image-20230412235559342.png" alt="image-20230412235559342" style="zoom:80%;" />

###### SysTick校准数值寄存器

<img src="D:\Git\git-space\Cortex-M3学习\imgs\image-20230412235650915.png" alt="image-20230412235650915" style="zoom:80%;" />

###### SysTick当前数值寄存器

<img src="D:\Git\git-space\Cortex-M3学习\imgs\image-20230412235735082.png" alt="image-20230412235735082" style="zoom:80%;" />

​        SysTick定时器除了能服务于操作系统之外，还能用于其它目的：如作为一个闹铃，用于

测量时间等。当处理器在调试期间被喊停时，则SysTick定时器亦将暂停运作。
