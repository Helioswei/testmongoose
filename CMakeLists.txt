#cmake 最低版本需求，不加入此行会受到警告的信息
cmake_minimum_required(VERSION 3.0)

#项目名
project(Common)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG")
    #set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

endif()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    message(STATUS "use ccache")
    set(CMAKE_CXX_COMPILER "ccache")
    set(CMAKE_CXX_COMPILER_ARG1 "g++")
endif()

set(CXX_FLAGS
# -DVALGRIND
-DCHECK_PIHREAD_RETURN_VALUE
-D_FILE_OFFSET_BITS=64
-Wall
-Wextra
#-Werror
-fPIC
-Wconversion
-Wno-unused-parameter
-Wold-style-cast
-Woverloaded-virtual
-Wpointer-arith
-Wshadow
-Wwrite-strings
-march=native
#-MMD
-std=c++14
-rdynamic
-Wno-error=deprecated-declarations
-Wno-deprecated-declarations
#-Wno-implicit-fallthrough
)

if(CMAKE_BUILD_BITS EQUAL 32)
    list(APPEND CXX_FLAGS "-m32")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  list(APPEND CXX_FLAGS "-Wno-null-dereference")
  list(APPEND CXX_FLAGS "-Wno-sign-conversion")
  list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
  list(APPEND CXX_FLAGS "-Wthread-safety")
  list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


#添加模块
add_subdirectory(thirdparty) #第三方库，需要最先编译
add_subdirectory(network) #网络操作库
