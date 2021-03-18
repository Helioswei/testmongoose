#把某个目录下的所有源代码和头文件放入到变量netTest_SRCS
file(GLOB_RECURSE  netTest_SRCS ./*.cpp)


#把当前目录下的文件编译成可执行程序
add_executable(net  ${netTest_SRCS})
#添加依赖的动态库
target_link_libraries(
    net
    mongoose
    )

