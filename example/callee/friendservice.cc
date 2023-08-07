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