# common

#### 介绍
cpp开发的基础公共包

### 开发环境

​	相关开发软件的版本要求：

- g++  >= 7.4
- cmake >= 3.19.3
- git >= 2.7.4

### 包管理

​	使用vcpkg进行包的管理，在新的机器上进行开发编译时需要先安装vcpkg。仅仅将其当成包安装，管理的工具，在`CMakeLists.txt`文件中将其软件安装的目录`installed`作为搜素的路径。在文件中类是这样写。

~~~cmake
 #添加头文件路径
include_directories(${VCPKG_ROOT}/installed/x64-linux/include)
#添加动态库路径
link_directories(${VCPKG_ROOT}/installed/x64-linux/lib)

~~~

#### 目前下载的库

~~~shell
./vcpkg install libuuid
./vcpkg install mongoose  #安装的版本过低，不使用这个方式
./vcpkg install spdlog
~~~

### 依赖库

- `libuuid `   用于实现uuid的库，版本：`1.0.3-7`；
- `mongoose` 用于实现httpserver的库,目前集成到了项目中，版本：`7.1`；
- `spdlog` 用于实现日志的记录，版本：`1.8.0`；
- `nolhmann/json` 用于json的解析，目前集成到项目中，版本：`3.9.1`;