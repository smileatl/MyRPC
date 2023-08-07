# set(SRC_LIST calluserservice.cc ../user.pb.cc)
set(SRC_LIST callfriendservice.cc ../friend.pb.cc)

add_executable(consumer ${SRC_LIST})
# provider是目标文件，后面都是要链接的库 -lmprpc -lprotobuf
target_link_libraries(consumer mprpc protobuf)

add_definitions(-std=c++17)
