'''
@Author: Anxjing.AI
@Date: 2020-05-05 20:03:12
@LastEditTime: 2020-05-05 20:13:01
@LastEditors: Anajing.AI
@Description: 
@FilePath: \axjingWorks\algorithm_note\getOffer\二叉树中和为某一值的路径.py
@可以输入预定的版权声明、个性签名、空行等
'''


'''
题目描述
输入一颗二叉树的根节点和一个整数，打印出二叉树中
结点值的和为输入整数的所有路径。路径定义为从树的根结点
开始往下一直到叶结点所经过的结点形成一条路径。

思路：
1. 递归先序遍历树， 把结点加入路径。
2. 若该结点是叶子结点则比较当前路径和是否等于期待和。
3. 弹出结点，每一轮递归返回到父结点时，当前路径也应该回退一个结点
'''

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
class Solution:
    # 返回二维列表，内部每个列表表示找到的路径
    def FindPath(self, root, expectNumber):
        # write code here
        if not root:
            return []
         
        result = []
         
        def FindPathMain(root, path, currentSum):
            currentSum += root.val
             
            path.append(root)
            isLeaf = root.left == None and root.right == None
             
            if currentSum == expectNumber and isLeaf:
                onePath = []
                for node in path:
                    onePath.append(node.val)
                result.append(onePath)
             
            if currentSum < expectNumber:
                if root.left:
                    FindPathMain(root.left, path, currentSum)
                if root.right:
                    FindPathMain(root.right, path, currentSum)
             
            path.pop()
         
        FindPathMain(root, [], 0)
         
        return result