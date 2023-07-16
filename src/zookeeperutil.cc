#include "zookeeperutil.h"
#include "mprpcapplication.h"
#include <iostream>
#include <semaphore.h>
 
// 全局的watcher观察期  zkserver给zkclient的通知
// zhandle_t *zh：当前客户端的句柄
void global_wathcer(zhandle_t *zh, int type, int state, const char *path, void *wathcerCtx){
    // 回调的消息类型是和会话相关的消息类型
    if(type==ZOO_SESSION_EVENT){
        // zkclient和zkserver连接成功
        if(state==ZOO_CONNECTED_STATE){
            // 从指定的句柄zh上获取信号量
            sem_t *sem=(sem_t*)zoo_get_context(zh);
            // 给信号量资源+1
            sem_post(sem);
        }
    }
}

ZkClient::ZkClient():m_zhandle(nullptr){

}

ZkClient::~ZkClient(){
    // 如果不为空，说明已经跟zkserver连接了
    if(m_zhandle!=nullptr){
        // 关闭句柄，释放资源 MySQL_Conn
        zookeeper_close(m_zhandle);
    }
}

// 连接zkserver
// 是一个异步连接过程
void ZkClient::Start(){
    // 获取ip、端口号
    std::string host=MprpcApplication::GeitInstance().GetConfig().Load("zookeeperip");
    std::string port=MprpcApplication::GeitInstance().GetConfig().Load("zookeeperport");
    std::string connstr =host+":"+port;

    /* 
    zookeeper_mt: 多线程版本
    zookeeper的API客户端提供了三个线程
    API调用线程
    网络I/O线程  pthread_create poll
    watcher回调线程 pthread_create 
    */

    // connstr.c_str()：主机和端口号
    // global_wathcer：回调函数
    // 30000：会话的超时时间
    // 最后返回句柄
    m_zhandle=zookeeper_init(connstr.c_str(), global_wathcer, 30000, nullptr, nullptr, 0);
    // 有可能初始化不成功
    if(nullptr==m_zhandle){
        std::cout<<"zookeeper_init error!"<<std::endl;
        exit(EXIT_FAILURE);
    }
  
    // 信号量，初始化为0
    sem_t sem;
    sem_init(&sem, 0, 0);
    // 给句柄设置了一个信号量
    zoo_set_context(m_zhandle, &sem);

    // 看到信号量有资源了，连接成功了，就往下执行
    sem_wait(&sem);
    std::cout << "zookeeper_init success!" << std::endl;
}


// 每个节点都有一个path

// state：节点状态，是临时性节点还是永久性节点
void ZkClient::Create(const char* path, const char* data, int datalen, int state){
    char path_buffer[128];
    int bufferlen=sizeof(path_buffer);
    int flag;
    // 先判断path表示的znode节点是否存在，如果存在，就不在重复创建了
    flag=zoo_exists(m_zhandle, path, 0, nullptr);
    // 表示path的znode节点不存在
    if(flag==ZNONODE){
        // 创建指定path的znode节点了
        flag=zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen);
        if(flag==ZOK){
            std::cout<<"znode create success... path:"<<path<<std::endl;
        }
        else{
            std::cout<<"flag:"<<flag<<std::endl;
            std::cout<<"znode create error... path:"<<path<<std::endl;
            exit(EXIT_FAILURE);
        }
    }

}

// 根据指定的path，获取znode节点的值
std::string ZkClient::GetDate(const char* path){
    char buffer[64];
    int bufferlen=sizeof(buffer);
    int flag=zoo_get(m_zhandle, path, 0, buffer, &bufferlen, nullptr);
    if(flag!=ZOK){
        std::cout<<"get znode error... path:"<<path<<std::endl;
        return "";
    }
    else{
        return buffer;
    }
}