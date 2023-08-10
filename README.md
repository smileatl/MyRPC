# 基于protobuf和zookeeper的RPC分布式网络通信框架

##  特征

- 使用protobuf实现RPC框架中数据的序列化/反序列化，提高网络传输的效率；
- 使用自实现的多线程网络库开发网络通信模块，使RPC服务提供方支持高并发与多线程的RPC请求;
- 使用服务器中间件zookeeper的服务注册和服务发现机制，实现分布式环境下的服务发现功能。



## 构建

```shell
git clone https://github.com/smileatl/mynetlib.git
cd mynetlib
mkdir build && cmake ..
make 
make install   
```

或使用自动化配置脚本

```shell
sudo ./autobuild.sh
```



## 文档

- [10.集群和分布式](./doc/10.集群和分布式.md)
- [20.RPC通信原理和技术选型](./doc/20.RPC通信原理和技术选型.md)
- [30.protobuf使用案例](./doc/30.protobuf使用案例.md)
- [40.本地服务发布成RPC服务](./doc/40.本地服务发布成RPC服务.md)
- [50.Thread相关类](./doc/50.Thread相关类.md)
- [60.Socket类和Acceptor类](./doc/60.Socket类和Acceptor类.md)
- [50.Mprpc框架基础类设计](./doc/50.Mprpc框架基础类设计.md)
- [60.开发PrcProvider的网络服务](./doc/60.开发PrcProvider的网络服务.md)
- [70.RpcProvider发布服务方法](./doc/70.RpcProvider发布服务方法.md)
- [80.RpcProvider发布rpc服务](./doc/80.RpcProvider发布rpc服务.md)
- [90.RpcChannel调用过程](./doc/90.RpcChannel调用过程.md)
- [100.Mprpc框架使用示例](./doc/100.Mprpc框架使用示例.md)
- [110.logger日志系统设计实现](./doc/110.logger日志系统设计实现.md)
- [120.zookeeper简介与安装](./doc/120.zookeeper简介与安装.md)
- [130.zookeeper C++客户端编程](./doc/130.zookeeper C++客户端编程.md)
- [140.使用mprpc编写客户端（服务调用方）程序示例](./doc/140.使用mprpc编写客户端（服务调用方）程序示例.md)



## 示例

### 运行

进入`zookeeper目录/bin/`

```shell
./zkServer.sh start

# 输出
ZooKeeper JMX enabled by default
Using config: /home/lsl/Desktop/code/project/mymprpc/package/zookeeper-3.4.10/bin/../conf/zoo.cfg
Starting zookeeper ... STARTED
```



进入`/bin`可执行文件目录

```shell
/provider -i test.conf rpcserverip:127.0.0.1

# 输出
rpcserverip:127.0.0.1
rpcserverport:8000
zookeeperip:127.0.0.1
zookeeperport:2181
[INFO]2023/08/10 23:23:27 : func=updateChannel => fd=6 events=3 index=-1 

[INFO]2023/08/10 23:23:27 : func=updateChannel => fd=7 events=3 index=-1 

2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@726: Client environment:zookeeper.version=zookeeper C client 3.4.10
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@730: Client environment:host.name=ubuntu
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@737: Client environment:os.name=Linux
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@738: Client environment:os.arch=5.15.0-78-generic
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@739: Client environment:os.version=#85~20.04.1-Ubuntu SMP Mon Jul 17 09:42:39 UTC 2023
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@747: Client environment:user.name=lsl
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@755: Client environment:user.home=/root
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@log_env@767: Client environment:user.dir=/home/lsl/Desktop/code/project/mymprpc/mymprpc/bin
2023-08-10 23:23:27,534:69942(0x7f97f0442780):ZOO_INFO@zookeeper_init@791: Initiating client connection, host=127.0.0.1:2181 sessionTimeout=30000 watcher=0x55a33ef25278 sessionId=0 sessionPasswd=<null> context=(nil) flags=0
2023-08-10 23:23:27,534:69942(0x7f97efc2c700):ZOO_INFO@check_events@1727: initiated connection to server [127.0.0.1:2181]
2023-08-10 23:23:27,536:69942(0x7f97efc2c700):ZOO_INFO@check_events@1773: session establishment complete on server [127.0.0.1:2181], sessionId=0x189e00a02be0001, negotiated timeout=30000
zookeeper_init success!
RpcProvider start service at ip:127.0.0.1 port:8000
```

```shell
./consumer -i test.conf

# 输出
rpcserverip:127.0.0.1
rpcserverport:8000
zookeeperip:127.0.0.1
zookeeperport:2181
============================================
header_size: 36
rpc_header_str: 
FriendServiceRpcGetFriendsList 
service_name: FriendServiceRpc
method_name: GetFriendsList
args_str: 
============================================
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@726: Client environment:zookeeper.version=zookeeper C client 3.4.10
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@730: Client environment:host.name=ubuntu
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@737: Client environment:os.name=Linux
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@738: Client environment:os.arch=5.15.0-78-generic
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@739: Client environment:os.version=#85~20.04.1-Ubuntu SMP Mon Jul 17 09:42:39 UTC 2023
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@747: Client environment:user.name=lsl
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@755: Client environment:user.home=/home/lsl
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@log_env@767: Client environment:user.dir=/home/lsl/Desktop/code/project/mymprpc/mymprpc/bin
2023-08-10 23:26:36,262:70169(0x7f9331a47740):ZOO_INFO@zookeeper_init@791: Initiating client connection, host=127.0.0.1:2181 sessionTimeout=30000 watcher=0x55a94162982e sessionId=0 sessionPasswd=<null> context=(nil) flags=0
2023-08-10 23:26:36,276:70169(0x7f9331a32700):ZOO_INFO@check_events@1727: initiated connection to server [127.0.0.1:2181]
2023-08-10 23:26:36,278:70169(0x7f9331a32700):ZOO_INFO@check_events@1773: session establishment complete on server [127.0.0.1:2181], sessionId=0x189e00a02be0004, negotiated timeout=30000
zookeeper_init success!
2023-08-10 23:26:36,282:70169(0x7f9331a47740):ZOO_INFO@zookeeper_close@2526: Closing zookeeper sessionId=0x189e00a02be0004 to [127.0.0.1:2181]

rpc GetFriendsList response success!
index:1 name:gao yang
index:2 name:liu hong
index:3 name:wnag shuo 
```



### 代码示例

#### friendservice.cc

```cpp
#include <iostream>
#include <string>
#include <vector>
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "friend.pb.h"
#include "logger.h"

// FriendService 是一个本地服务，提供了两个进程内的本地方法Login和GetFriendLists
// 使用在rpc服务的发布端（rpc服务提供者）
class FriendService : public fixbug::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid) {
        std::cout << "do GetFriendsList service! userid:"<< userid <<std::endl;
        std::vector<std::string> vec;
        vec.push_back("gao yang");
        vec.push_back("liu hong");
        vec.push_back("wnag shuo ");
        return vec;
    }

    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController* controller,
                        const ::fixbug::GetFriendsListRequest* request,
                        ::fixbug::GetFriendsListResponse* response,
                        ::google::protobuf::Closure* done) {
        // 1.框架给业务上报了请求参数 GetFriendsListRequest ，应用获取相应数据做本地业务
        uint32_t userid = request->userid();
        // 2.做业务
        std::vector<std::string> friendsList = GetFriendsList(userid);
        // 3.把响应写入
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for (std::string& name : friendsList) {
            std::string* p = response->add_friends();
            *p = name;
        }

        // 4.做回调操作,执行响应对象数据的序列化和网络发送（都是由框架完成）
        done->Run();
    }
};

int main(int argc, char** argv) {

    LOG_INFO("first log message!");
    LOG_ERROR("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);
    // 框架只需要init一次
    // 调用框架的初始化操作  provider -i config.conf
    MprpcApplication::Init(argc, argv);

    RpcProvider provider;
    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    provider.NotifyService(new FriendService());
    // provider.NotifyService(new ProductService());

    // 启动一个rpc服务发布节点  Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}
```



#### callfriendservice.cc

```cpp
#include <iostream>
#include "friend.pb.h"
#include "mprpcapplication.h"

int main(int argc, char** argv) {
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc, argv);

    // 演示调用功能远程发布的rpc方法的Login
    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法的请求参数
    fixbug::GetFriendsListRequest request;
    request.set_userid(1000);
    // rpc方法的响应
    fixbug::GetFriendsListResponse response;

    // 发起rpc方法的调用  同步的rpc调用过程  MprpcChannel::callMethod
    MprpcController controller;
    stub.GetFriendsList(
        &controller, &request, &response,
        nullptr);  // RpcChannel->RpcChannel::callMethod
                   // 集中来做所有rpc方法调用的参数序列化和网络发送
 
    // 一次rpc调用完成，读调用的结果
    // 通过controller来输出错误信息
    if (controller.Failed()) {
        std::cout << controller.ErrorText() << std::endl;
    } else {
        // rpc调用的过程是顺利的
        if (0 == response.result().errcode()) {
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size();
            for (int i = 0; i < size; ++i) {
                std::cout << "index:" << (i + 1)
                          << " name:" << response.friends(i) << std::endl;
            }
        } else {
            std::cout << "rpc GetFriendsList response error : "
                      << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}
```

