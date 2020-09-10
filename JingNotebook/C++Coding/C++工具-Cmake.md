<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-26 16:18:46
 * @LastEditTime: 2020-08-26 19:39:23
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++工具-Cmake.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
-->
# C++工具：Cmake

## Cmake基本概念
CMake是个一个开源的跨平台自动化建构系统，用来管理软件建置的程序，并不依赖于某特定编译器，并可支持多层目录、多个应用程序与多个库。 它用配置文件控制建构过程（build process）的方式和Unix的make相似，只是CMake的配置文件取名为CMakeLists.txt。CMake并不直接建构出最终的软件，而是产生标准的建构档（如Unix的Makefile或Windows Visual C++的projects/workspaces），然后再依一般的建构方式使用。这使得熟悉某个集成开发环境（IDE）的开发者可以用标准的方式建构他的软件，这种可以使用各平台的原生建构系统的能力是CMake和SCons等其他类似系统的区别之处。 CMake配置文件(CMakeLists.txt)可设置源代码或目标程序库的路径、产生适配器（wrapper）、还可以用任意的顺序建构可执行文件。CMake支持in-place建构（二进档和源代码在同一个目录树中）和out-of-place建构（二进档在别的目录里），因此可以很容易从同一个源代码目录树中建构出多个二进档。CMake也支持静态与动态程序库的建构。

“CMake”这个名字是"Cross platform Make"的缩写。虽然名字中含有"make"，但是CMake和Unix上常见的“make”系统是分开的，而且更为高端。 它可与原生建置环境结合使用，例如：make、苹果的Xcode与微软的Visual Studio。

## 功能
1. 配置文件是用一种建构软件专用的特殊编程语言写的CMake脚本。
1. 内置C语言、C++、Fortran、Java的自动相依性分析功能。
1. 经由CMake脚本语言支持SWIG、Qt、FLTK。
1. 内置对微软Visual Studio .NET和过去的Visual Studio版本的支持，可以产生.dsp、.sln和.vcproj档。
1. 用传统的时间标签侦测文件内容的改变。
1. 支持分布式建构（在多台电脑上同时建构）
1. 在许多操作系统上进行跨平台编译，包括 Linux、与POSIX兼容的系统（AIX、*BSD系统、HP-UX、IRIX、MinGW/MSYS、Solaris）、Mac OS X和微软Windows 95/98/NT/2000/XP等。
1. 产生可以给Graphviz用的全局相依图。
1. 已经和Dart、CTest和CPack等软件测试和发布的工具集成。

--[来源](https://zh.wikipedia.org/wiki/CMake)

## 基本语法
```makefile
#CMake最低版本号要求
cmake_minimum_required(VERSION 3.0)

#指定项目名称
project(openailab_four_monitor)

#指定工程需要用到的一些库
set(ENV{PKG_CONFIG_PATH} /usr/local/AID/pkgconfig)
find_package(PkgConfig)
pkg_search_module(BLADECV REQUIRED bladecv)
pkg_search_module(GTK REQUIRED gtk±3.0)
#find_package(PkgConfig)
#find_package(Qt5 REQUIRED Widgets)
#find_package(Qt5 REQUIRED Core)
#find_package(Qt5 REQUIRED Gui)

#包含c++11特性
set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -std=c++11 -g”)
#指定版本信息
set(CMAKE_SYSTEM_VERSION 1)

#若是需要指定编译器路径
#set(CROSS_TOOLCHAIN_PREFIX “/path/arm-linux-”)
#指定编译器
#set(CMAKE_C_COMPILER   “KaTeX parse error: Expected 'EOF', got '#' at position 31: …N_PREFIX}gcc") #̲set(CMAKE_CXX_C…{CROSS_TOOLCHAIN_PREFIX}g++”)

#使用默认路径的g++指定编译器  
set(CMAKE_CXX_COMPILER “g++”)

#指定编译选项
set(CMAKE_BUILD_TYPE Debug )

#指定编译目录
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

#添加子目录,这样进入源码文件src目录可以继续构建  
#add_subdirectory(${PROJECT_SOURCE_DIR}/src)

#查找当前目录下的所有源文件，
#并将名称保存到DIR_LIB_SRCS目录
#aux_source_directory(. DIR_LIB_SRCS)

#指定头文件目录,PROJECT_SOURCE_DIR为工程的根目录  
include_directories(
${PROJECT_SOURCE_DIR}/include
/usr/local/AID
${BLADECV_INCLUDE_DIRS}
${GTK_INCLUDE_DIRS}
)

#添加需要链接的库文件目录
link_directories(
/usr/lib64/
${BLADECV_LIBRARY_DIRS}
${GTK_LIBRARY_DIRS}
)

#添加编译参数和横定义
#option(USE_BLADECV “bladecv” ON)
#if(USE_BLADECV)
#add_definitions(-DBLADECV)
#endif()

#设置编译选项(会将gcc g++全部加上)
#add_compile_options(-g -std=c++11)
add_compile_options(-fPIC)

#指定可执行文件的输出目录，输出到bin下面  
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#生成动态库    
#add_library(shared_demo SHARED demo.cpp -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lpthread
#-lbcv -lgtk-3 -lrtspclient)

#设置库输出名为 shared => libshared.so  
#set_target_properties(shared_demo PROPERTIES OUTPUT_NAME “shared”)

#生成静态库  
#add_library(static_demo STATIC demo.cpp -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lpthread
#-lbcv -lgtk-3 -lrtspclient)  
#设置输库出名为 static => libstatic.a  
#set_target_properties(static_demo PROPERTIES OUTPUT_NAME “static”)

#指定库文件输出路径  
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#在指定目录下查找库，并保存在LIBPATH变量中
#find_library(LIBPATHS  shared ${PROJECT_SOURCE_DIR}/lib /usr/lib64)

#指定生成目标
add_executable(demo demo.cpp)

#链接共享库
target_link_libraries(demo -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lpthread
-lbcv -lgtk-3 -lrtspclient ${BLADECV_LDFLAGS} ${GTK_LDFLAGS})
```