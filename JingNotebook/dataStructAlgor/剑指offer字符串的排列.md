<!--
 * @Author: Anxjing.AI
 * @Date: 2020-05-11 21:55:12
 * @LastEditTime: 2020-05-11 22:01:38
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\dataStructAlgor\剑指offer字符串的排列.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
 -->
- 题目描述

输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c
所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

    - 描述:

    输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。


- 思路：

递归法，问题转换为先固定第一个字符，求剩余字符的排列；求剩余字符排列时跟原问题一样。

(1) 遍历出所有可能出现在第一个位置的字符（即：依次将第一个字符同后面所有字符交换）；

(2) 固定第一个字符，求后面字符的排列（即：在第1步的遍历过程中，插入递归进行实现）。

- 温馨提示：

(1) 先确定递归结束的条件; 

(2) 形如 aba 或 aa 等特殊测试用例的情况；

(3) 输出的排列可能不是按字典顺序排列的，可能导致无法完全通过测试用例，考虑输出前排序，或者递归之后取消复位操作。



```python
class Solution:
    def Permutation(self, ss):
        if len(ss) <= 1:
            return ss
        res = set()
        # 遍历字符串，固定第一个元素，第一个元素可以取a,b,c...，然后递归求解
        for i in range(len(ss)):
            for j in self.Permutation(ss[:i] + ss[i+1:]): # 依次固定了元素，其他的全排列（递归求解）
                res.add(ss[i] + j) # 集合添加元素的方法add(),集合添加去重（若存在重复字符，排列后会存在相同，如baa,baa）
        return sorted(res)         # sorted()能对可迭代对象进行排序,结果返回一个新的list
```


**【欢迎关注、点赞、收藏、私信、交流】共同学习进步**
