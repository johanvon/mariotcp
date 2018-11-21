
MarioTCP:一个可单机支持千万并发连接的TCP服务器
=============================

**请注意：**

**过去几年有不少朋友加我，心想对不住大家了，建个群聚聚大家伙，请大家群里畅所欲言…请加QQ群：564994650， 里面有不少linux c的研发同学：）**

  

MrioTCP，超级马里奥，顾名思义，他不仅高效，而且超级简易和好玩。同时他可以是一个很简洁的Linux C 开发学习工程。毫不夸张的说，如果全部掌握这一个工程，你会成为一个Linux C的牛人；当然，你也可以通过源码包的mario.c(maritcp服务器示例程序）来学习，可以很快入门上手进行Linux C开发。

经过两个多月的测试（编写c++客户端测试及调优系统参数），测试结果得到单机最大带宽吞吐1000M，测试最高TCP长连接100万，每秒处理连接数达4万，此时系统压力load值很低。总之，它可以发挥一台服务器的最大极限以提供最高性能的服务；而且经过完备测试，运行稳定且占用系统资源非常少。  

他是建立在Sourceforge上的一个开源项目，由源码的作者冯建华(JohnFong)发起。源码可以在Sourceforge上下载。

sourceforge下载：[https://sourceforge.net/projects/mariotcp/files/latest/download](https://sourceforge.net/projects/mariotcp/files/latest/download)  

csdn下载：[http://download.csdn.net/detail/everlastinging/6195605](http://download.csdn.net/detail/everlastinging/6195605)

Getting Started
---------------

  

用MarioTCP来建立一个性能强大的TCP服务器非常简易！

　　工程源码包就是一个非常简洁的例子，生成了一个tcp服务器程序：maritcp。  
　　源码包中：  
　　mario.c是简易例子的main程序，直接make可以编译出maritcp，一个tcp服务器，业务逻辑只有一个功能：统计同时在线socket数、每隔1分钟输出一次。  
　　mario文件夹，MarioTCP的核心代码，make可以直接编译出静态的libmario.a。MarioTCP核心架构后续会介绍。  
　　test文件夹，是一个稍显简陋的客户端测试程序，通过与服务器建立连接、发送LOGIN包登陆服务器，此时maritcp服务器会使同时在线加1，客户端断开时服务器在线数减1。  
  
现在讲一下如何定制一个自己业务逻辑的tcp服务器，只需五步：  
　　1、初始化SERVER  
　　SERVER *server = init_server(conf->port, conf->workernum, conf->connnum, conf->timeout, conf->timeout);  
　　传入参数分别是：  
　　服务器Listen端口，工作线程数，每个线程支持的连接数，读超时时间，写超时时间。  
　　workernum * connum 就是服务器支持的长连接数，一个worker可以轻松支持10万长连接。  
  
2、实现业务逻辑函数并注册  
　　具体业务逻辑函数请见Function模块。可通过mario.h中定义的名为“regist_*”的函数来注册。  
  
/*  
　　\* 注册业务处理函数  
　　/  
　　void regist\_akg\_func(uint16 id, FUNC_PTR func);  
　　id可以是0-65535的任意数，此id封装在MarioTCP的协议中（见本文最后）。  
　　id的范围，可以根据业务逻辑来定制，例如maritcp通过protocol.h中定义的CMD结构体来设定：  
　　typedef enum _CMD {  
　　CMD\_FUNCTION\_BASE = 0x6100,  
　　CMD\_FUNCTION\_LOGIN = 0x6101  
　　} CMD;  
  
如果你想为maritcp增加一个"say_hello"的服务，可以这么做：  
　　1）在CMD中增加：CMD\_FUNCTION\_SAY_HELLO = 0x602  
　　2) 在function中增加函数：  
　　sint32 say_hello(CONN c) {  
　　I)通过CONN来解析客户端发过来请求的参数  
　　II）将“hello”设定到c->out_buf  
　　III)bufferevent\_write(c->bufev, c->out\_buf, hrsp->pkglen);  
　　IV)return 0;  
　　}  
　　3)在mario.c中增加：regist\_akg\_func(CMD\_FUNCTION\_SAY\_HELLO, say\_hello);  
  
怎么样？自己定制业务逻辑，还是很简单高效吧！  
  
3、启动日志线程start\_log\_thread()  
　　MarioTCP的日志功能封装还不够好，在“go on 1.0.0”页面中继续讨论...  
  
4、启动服务器start_server((void*) server);  
　　OK，一个可以支持100万甚至更多长连接的TCP服务器，诞生了！  

  

Go On 1.0.0
-----------

  

第一个发布版本为0.9.9，尽管用这个包，通过几分钟就可以实现一个定制了你的业务逻辑的、稳定高效的TCP服务器，但是MarioTCP还有很多有待完善的地方，让我们一起尽快解决如下问题，让MarioTCP-1.0.0尽快发布！

  
1、MarioTCP协议如何优化  
　　为了使MarioTCP足够安全，规定了一个简易的MarioTCP协议，经过三次握手连接到MarioTCP的client，接下来发的包要求格式必须是“HEAD+Data”的形式，而HEAD结构体定义在mario_akg.h中：  
　　typedef struct _HEAD {  
　　uint32 stx;  
　　uint16 pkglen;  
　　uint16 akg_id;  
　　} HEAD;  
　　pkglen是整个包的长度，即“HEAD+Data”。  
　　akg\_id及自定义的业务逻辑函数对应的id，例如“Getting Started”页面中的CMD\_FUNCTION\_SAY\_HELLO  
　　stx是你自定义的协议密文，通过regist_stx(uint32 stx)来注册(见mario.c)  
  
尽管MarioTCP的协议足够简单了，而且协议最开头的密文可以自定义，但是是否可以更简单或者无协议，以最大程度的方便开发使用，需要大家的建议和帮助！  
  
2、日志系统过于死板  
　　MarioTCP有一套自成系统的日志功能，但是比较晦涩难懂。  
　　接下来再展开...  
  
3、业务逻辑稳定性支持  
　　MarioTCP对于网络连接和读写，非常高效和稳定。  
　　但是MarioTCP的线程池是固定个数的，且是全局唯一初始化的，死掉的线程不可再重启；分配网络任务的Master线程不具备监听worker的功能，一个线程死掉了、任务却还会一直分配过来，造成服务堆积且不处理。如果业务逻辑如果非常复杂和低效，就会出现这个问题。  
　　在大型线上项目中，用到MarioTCP的地方，都会通过业务逻辑模块的监听、告警及程序自动处理来避免上述问题。由于时间问题还没有把此功能抽象到MarioTCP中。  

　　这件事情，近期我会抓紧处理。也希望有朋友建议和帮助！！

  

Why Supper
----------

  

一、为什么超级高效  
　　1、网络服务用到的所有结构体和内存都是启动程序时初始化的，无销毁，无回收。  
　　无销毁好理解，不解释。  
　　无回收，是指所有内存单元拿来即用，用完及可，不用做reset操作。  
　　2、一个master线程进行accept  
　　经过测试发现多进程或线程进行accept和一个进程或线程accept，在极限压力下区别不大。  
　　一个master比多个master好在不用再通过锁来解决同步问题。  
　　3、master与worker时单一生产者消费者模式，完全无锁通信  
　　不光accept无锁，分配connection、后续的conncetion处理都是无锁的。  
　　甚至业务逻辑（见示例maritcp的统计在线数功能）、MarioTCP的日志系统（这也是日志系统抽象不够的一个原因，之前的设计太依赖于整体架构了）都是无锁处理的！  
　　4、一个worker一套libevent环境  
　　libevent处理10万长连接的网络读写事件，其性能达到最大化了。  
　　每个worker都独立一套libevent，这个结构经过测试，发现开销很小、性能很高。  
  
二、单机百万长连接、四万cps（连接每秒）如何做测试得来  
　　1、设置系统最大文件数为unlimited  
　　2、设置系统的tcp内存内核参数到256M以上  
　　3、设置系统的ip到15个，那么可服务的长连接数理论上最少15*(65535-1024)个  
　　4、用epoll或libevent开一个可同时连接5w的客户端程序；程序还要实现每秒随机挑选1000个连接断掉，并再新创建1000个连接。另外在随机挑选几千连接发包。  
　　同时再多台机器上开启20个客户端，那么就是100w长连接，每秒2w个连接断掉、2w个新连接加入进来，并且有若干包发过来。  
　　5、设置服务端可重用SYN_WAIT的连接；客户端断连接的方式是主动断掉（防止客户端程序端口堆积）  
　　总之很折腾的一个测试，前前后后大约2个多月才测试完毕。  
　　以上内容凭记忆写的，怕有错误或疏漏，回头为了公布测试代码和测试结果给大家，会再次开发、测试并调整补过上述内容。
