# 当前目录所有源文件作为SRC_LIST

# aux_source_directory：生成makefile以后，只要cmakelists不变，是不会重新生成makefile的
# 此时可以删掉build文件夹下的所有内容，重新生成
# aux_source_directory(. SRC_LIST)
set(SRC_LIST 
    mprpcapplication.cc 
    mprpcconfig.cc 
    rpcheader.pb.cc 
    rpcprovider.cc 
    mprpcchannel.cc
    mprpccontroller.cc
    logger.cc
    zookeeperutil.cc)
add_library(mprpc ${SRC_LIST})
# mprpc依赖于muduo库
# net依赖于base，需要写在前边
# muduo生成的是一个静态库，生成的动态库去链接静态库时会出现一点问题
# target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)
target_link_libraries(mprpc mymuduo pthread zookeeper_mt)
# zookeeper_mt是zookeeper的多线程版本

add_definitions(-std=c++17)