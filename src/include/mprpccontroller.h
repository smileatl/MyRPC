#pragma once
#include <google/protobuf/service.h>
#include <string>

// 重写Rpc controller
class MprpcController:public google::protobuf::RpcController{
public:
    MprpcController();
    void Reset();
    // 成功与否，以及失败的错误信息
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    // 目前未实现具体的功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);

private:
    bool m_failed; // RPC方法执行过程中的状态
    std::string m_errText; // RPC方法执行过程中的错误信息
};

