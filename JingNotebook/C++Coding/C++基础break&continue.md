<!--
 * @Author: Anxjing.AI
 * @Date: 2020-07-23 21:17:12
 * @LastEditTime: 2020-07-23 21:22:46
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础break&continue.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
--> 
# C++基础:break&continue区别：

## continue
continue语句只能应用在循环（for；while；do...while）结构中，其作用是跳过循环体中尚未执行的部分，接着进行下一次循环条件的判断，直到循环条件不成立时才跳出循环。
```C++

#include <stdio.h>

int main()

{

    int i = 5,n = 0;

    while(i--)

    {

        if(i == 3)

           continue;

        else if(i == 1)

            n = 6;

    }

    n = n + 5;

    printf("i=%d\n",i);

    printf("n=%d\n",n);

        return 0;    

}
```
*output：i=1，n=11，具体程序执行步骤可以自己推导。*


## break
break语句用来结束当前正在执行的循环（for；while；do...while）结构或多路分支（switch）结构，转而执行这些结构后的语句，注意：break语句一次只跳出一个循环，即break所在的最内层循环，若要跳出多重循环，需要使用goto语句，在switch语句中，break直接跳出switch，执行switch结构后的语句。
```C++

#include <stdio.h>

int main()

{

    int i = 5,n = 0;

    while(i--)

    {

        if(i == 3)

           break;

        else if(i == 1)

            n = 6;

    }

    n = n + 5;

    printf("i=%d\n",i);

    printf("n=%d\n",n);

        return 0;    

}		

```
*当i=3时，break直接跳出while循环，执行n=n+5，最后n=5。
output:i=3，n=5。*
  


