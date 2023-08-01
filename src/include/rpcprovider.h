#pragma once
#include <google/protobuf/service.h>
#include <memory>
#include <mymuduo/TcpServer.h>
#include <mymuduo/EventLoop.h>
#include <mymuduo/InetAddress.h>
#include <mymuduo/TcpConnection.h>
#include <functional>
#include <google/protobuf/descriptor.h>
#include <string>
#include <unordered_map>
#include "logger.h"

// 框架提供的专门服务发布rpc服务的网络对象类
class RpcProvider{
public:
    // Service能接收任意从Service基类继承的对象
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();


private:
    // // 组合了TcpServer
    // 只有run方法会访问，写成函数的局部变量
    // std::unique_ptr<muduo::net::TcpServer> m_tcpserverPtr;

    // 组合了EventLoop
    // 在多个成员方法中都会使用
    mymuduo::EventLoop m_eventLoop;

    // 服务类型信息
    struct ServiceInfo{
        google::protobuf::Service *m_service; // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap; // 保存服务方法
    };
    // 存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;


    // 新的socket连接回调
    void OnConnection(const mymuduo::TcpConnectionPtr&);
    // 已建立连接用户的读写事件回调
    void OnMessage(const mymuduo::TcpConnectionPtr&, mymuduo::Buffer*, mymuduo::Timestamp);
    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const mymuduo::TcpConnectionPtr&, google::protobuf::Message*);


};