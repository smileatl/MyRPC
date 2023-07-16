#include "mprpcapplication.h"
#include <unistd.h>
#include <iostream>

// 类的静态成员变量在类外初始化，static可不加
MprpcConfig MprpcApplication::m_config;

void ShowArgsHelp() {
    std::cout << "format: command -i <configfile>" << std::endl;
}

// 类外实现静态方法，不用带static
void MprpcApplication::Init(int argc, char** argv) {
    if (argc < 2) {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    // getopt用来分析命令行参数
    // 选项字符串里的字母后接着冒号":"，表示还有相关的参数
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
            // 正确
            case 'i':
                config_file = optarg;
                break;
            // 找不到符合的参数，出错
            case '?':
                // std::cout << "invalid args!" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            // 出错，无参数
            case ':':
                // std::cout << "need <configfile>" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    // 开始加载配置文件了  rpcserver_ip=  rpcserver_port
    // zookeeper_ip=  zookepper_port=
    // 需要char* c字符串，用c_str()转换
    m_config.LoadConfigFile(config_file.c_str());
    std::cout << "rpcserverip:" << m_config.Load("rpcserverip") << std::endl;
    std::cout << "rpcserverport:" << m_config.Load("rpcserverport")
              << std::endl;
    std::cout << "zookeeperip:" << m_config.Load("zookeeperip") << std::endl;
    std::cout << "zookeeperport:" << m_config.Load("zookeeperport")
              << std::endl;
}

MprpcApplication& MprpcApplication::GeitInstance() {
    static MprpcApplication app;
    return app;
}


MprpcConfig& MprpcApplication::GetConfig(){
    return m_config;
}