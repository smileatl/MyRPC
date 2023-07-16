#include "mprpcconfig.h"

#include <iostream>
#include <string>

// 类的静态成员变量在类外初始化，static可不加
static MprpcConfig m_config;

// 负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char* config_file) {
    // 读config文件
    FILE* pf = fopen(config_file, "r");
    if (pf == nullptr) {
        std::cout << config_file << " is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // feof是否读取到了文件尾，已到返回非零值
    // 1.注释  2.正确的配置项 =  3.去掉开头的多余空格
    while (!feof(pf)) {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        // 去掉字符串前面多余的空格
        std::string read_buf(buf);
        Trim(read_buf);

        // 判断#的注释
        // 同时也跳过空行
        if (read_buf[0] == '#' || read_buf.empty()) {
            continue;
        }

        // 解析配置项
        int idx = read_buf.find('=');
        if (idx == -1) {
            // 配置项不合法
            continue;
        }

        std::string key;
        std::string value;
        // 因为idx为'='，所以空了一格
        key = read_buf.substr(0, idx);
        // key前后多余的空格去掉
        Trim(key);
        // rpcserverip=127.0.0.1\n
        int endidx = read_buf.find('\n', idx);
        value = read_buf.substr(idx + 1, endidx - idx - 1);
        // value前后多余的空格去掉
        Trim(value);
        m_configMap.insert({key, value});
    }
}
// 查询配置项信息
std::string MprpcConfig::Load(const std::string& key) {
    auto it = m_configMap.find(key);
    if (it == m_configMap.end()) {
        // 键值不存在，返回空字符串
        return "";
    }
    // 不然返回值
    return it->second;
}

void MprpcConfig::Trim(std::string& src_buf) {
    // 找出第一个不为空格的idx
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1) {
        // 说明字符串前面有空格
        // 取出子字符串
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }
    // 去掉字符串后面多余的空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1) {
        // 说明字符串后面有空格
        // 取出子字符串
        src_buf = src_buf.substr(0, idx + 1);
    }
}