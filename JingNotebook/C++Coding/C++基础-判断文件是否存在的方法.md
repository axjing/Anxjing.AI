<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-05 19:36:50
 * @LastEditTime: 2020-08-11 19:31:27
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-判断文件是否存在的方法.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
--> 
# C++基础：判断文件是否存在的方法

## 使用以下几种函数判断文件是否存在
1. #include <fstream> --> 使用ifstream打开文件流，成功则存在，失败则不存在;
1. #include <stdio.h> --> 以fopen读方式打开文件，成功则存在，否则不存在;
1. #include <unistd.h> --> 使用access函数获取文件状态，成功则存在，否则不存在
1. #include <sys/stat.h> --> 使用stat函数获取文件状态，成功则存在，否则不存在

```cpp
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std

bool isFileExists_ifstream(string& name) {
    ifstream f(name.c_str());
    return f.good();
}

bool isFileExists_fopen(string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

bool isFileExists_access(string& name) {
    return (access(name.c_str(), F_OK ) != -1 );
}

bool isFileExists_stat(string& name) {
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}

```

[参考衔接2](https://github.com/axjing/Anxjing.AI/blob/master/JingNotebook)