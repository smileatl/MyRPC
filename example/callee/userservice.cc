#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"

// rpc服务的提供者

/*
UserService原来是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
希望能实现跨机器
*/
class UserService : public fixbug::UserServiceRpc {  // 使用在rpc服务端（rpc服务提供者）
public:
    // 用户对象的登录服务
    bool Login(std::string name, std::string pwd) {
        std::cout << "doing local service: login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;
        return false;
    }

    bool Register(uint32_t id, std::string name, std::string pwd){
        std::cout << "doing local service: Register" << std::endl;
        std::cout << "id:"<< id << "name:" << name << " pwd:" << pwd << std::endl;
        return true;
    }

    /*  
    重写基类UserServiceRpc的虚函数
    下面这些方法都是框架直接调用的
    1. caller   ===>   Login(LoginRequest)  => muduo =>   callee 
    2. callee   ===>    Login(LoginRequest)  => 交到下面重写的这个Login方法上了
    */
    
    // 根据request做response，再返回回去
    virtual void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginReponse* response,
                       ::google::protobuf::Closure* done){
        // 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
        std::string name=request->name();
        std::string pwd=request->pwd();  

        // 做本地业务 
        bool login_result=Login(name, pwd); 

        // 把响应写入  包括错误码、错误消息、返回值
        fixbug::ResultCode *code=response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调操作  执行响应对象数据的序列化和网络发送（都是由框架来完成的）
        done->Run();
    }

    // 重写Register
    // 把本地的Register发布成rpc服务
    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t id=request->id();
        std::string name=request->name();
        std::string pwd=request->pwd();

        bool ret=Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();
    }                       

};

int main(int argc, char **argv) {
    // 框架只需要init一次
    // 调用框架的初始化操作  provider -i config.conf
    MprpcApplication::Init(argc, argv);

    RpcProvider provider;
    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    provider.NotifyService(new UserService());
    // provider.NotifyService(new ProductService());

    // 启动一个rpc服务发布节点  Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}





