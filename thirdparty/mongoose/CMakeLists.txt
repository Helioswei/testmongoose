#把某个目录下的所有源代码和头文件放入到变量mon_SRCS
file(GLOB_RECURSE  mon_SRCS ./*.c)



set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#把当前目录下的文件编译成共享库
add_library(mongoose STATIC ${mon_SRCS})
#add_library(mongoose SHARED ${mon_SRCS})
#添加依赖的动态库
target_link_libraries(
    mongoose
    )
