<!--
 * @Author: Anxjing.AI
 * @Date: 2020-05-10 23:49:01
 * @LastEditTime: 2020-05-10 23:59:26
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\dataStructAlgor\剑指offer复杂链表的复制.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
 -->
- 题目描述：
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针random指向一个随机节点），
请对此链表进行深拷贝，并返回拷贝后的头结点。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）

- 思路：

1. 复制每个节点，如：复制节点A得到A1，将A1插入节点A后面
2. 遍历链表，A1->random = A->random->next;
3. 将链表拆分成原链表和复制后的链表

    1. 遍历链表，复制每个结点，如复制结点A得到A1，将结点A1插到结点A后面；
    2. 重新遍历链表，复制老结点的随机指针给新结点，如A1.random = A.random.next;
    3. 拆分链表，将链表拆分为原链表和复制后的链表

```python
# -*- coding:utf-8 -*-
class RandomListNode:
    def __init__(self, x):
        self.label = x
        self.next = None
        self.random = None
class Solution:
    # 返回 RandomListNode
    def Clone(self, pHead):
        if not pHead:
            return None
         
        dummy = pHead
         
        # first step, N' to N next
        while dummy:
            dummynext = dummy.next
            copynode = RandomListNode(dummy.label)
            copynode.next = dummynext
            dummy.next = copynode
            dummy = dummynext
         
        dummy = pHead
         
        # second step, random' to random'
        while dummy:
            dummyrandom = dummy.random
            copynode = dummy.next
            if dummyrandom:
                copynode.random = dummyrandom.next
            dummy = copynode.next
         
        # third step, split linked list
        dummy = pHead
        copyHead = pHead.next
        while dummy:
            copyNode = dummy.next
            dummynext = copyNode.next
            dummy.next = dummynext
            if dummynext:
                copyNode.next = dummynext.next
            else:
                copyNode.next = None
            dummy = dummynext
 
        return copyHead
```
**【欢迎关注、点赞、收藏、私信、交流】共同学习进步**
