# pragma once

#include "mprpcconfig.h"
// 把这些模块的头文件直接包含在框架里面
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// mprpc框架的基础类，负责框架的一些初始化操作 
class MprpcApplication{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GeitInstance();
    static MprpcConfig& GetConfig();

private:
    // 静态成员函数只能访问静态成员变量
    static MprpcConfig m_config; 

    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&)=delete;
    MprpcApplication(MprpcApplication&&)=delete;
};