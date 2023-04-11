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

<img src="images\image-20230412001259694.png" alt="image-20230412001259694" style="zoom: 80%;" />

<img src="images\image-20230412002151876.png" alt="image-20230412002151876" style="zoom: 67%;" />

​       SETENA和CLRENA各有8个，一共是8对，从SETENA0到SETENA7,CLRENA到CLRENA7，若使用的芯片支持32个中断，则只SETENA0和CLRENA0才需要使用，SETENA和CLRENA可以按字，半字，字节方式访问。  特别的SETENA7和CLRENA7分别有16个使能位和16个除能位。

