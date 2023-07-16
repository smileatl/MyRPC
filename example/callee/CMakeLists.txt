
# 根据这两个.cc文件生成可执行文件
# set(SRC_LIST userservice.cc ../user.pb.cc )
set(SRC_LIST friendservice.cc ../friend.pb.cc )

add_executable(provider ${SRC_LIST})
# 链接动态库
# 之前几个CMakeLists创建的动态库，还有一个protobuf
# 使用mprpc框架的地方，不管网络用的是谁，这是框架内部的事
target_link_libraries(provider mprpc protobuf)

