<!--
 * @Author: Anxjing.AI
 * @Date: 2020-05-11 11:07:30
 * @LastEditTime: 2020-05-11 11:09:07
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\dataStructAlgor\二叉树与双向链表.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
 -->

- 题目描述
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。

- 思路
非递归思路：
1. 二叉树的中序遍历
2. 中序遍历中每个结点的链


递归思路
1. 将左子树构建成双链表，返回链表头
2. 定位至左子树的最右的一个结点
3. 如果左子树不为空，将当前root加到左子树链表
4. 将右子树构造成双链表，返回链表头
5. 如果右子树不为空，将该链表追加到root结点之后
```python
# 非递归思路
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
class Solution:
    def Convert(self, pRootOfTree):
        if not pRootOfTree:
            return None
         
        p = pRootOfTree
         
        stack = []
        resStack = []
         
        while p or stack:
            if p:
                stack.append(p)
                p = p.left
            else:
                node = stack.pop()
                resStack.append(node)
                p = node.right
             
        resP = resStack[0]
        while resStack:
            top = resStack.pop(0)
            if resStack:
                top.right = resStack[0]
                resStack[0].left = top
         
        return resP

# 递归思路
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
class Solution:
    def Convert(self, root):
        if not root:
            return None
        if not root.left and not root.right:
            return root
         
        # 将左子树构建成双链表，返回链表头
        left = self.Convert(root.left)
        p = left
         
        # 定位至左子树的最右的一个结点
        while left and p.right:
            p = p.right
         
        # 如果左子树不为空，将当前root加到左子树链表
        if left:
            p.right = root
            root.left = p
         
        # 将右子树构造成双链表，返回链表头
        right = self.Convert(root.right)
        # 如果右子树不为空，将该链表追加到root结点之后
        if right:
            right.left = root
            root.right = right
             
        return left if left else root

```

**【欢迎关注、点赞、收藏、私信、交流】共同学习进步**