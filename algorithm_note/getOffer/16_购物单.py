'''
@Author: your name
@Date: 2020-01-14 16:40:20
@LastEditTime : 2020-01-14 17:20:51
@LastEditors  : Please set LastEditors
@Description: In User Settings Edit
@FilePath: \axjingWorks\algorithm_note\huawei\16_购物单.py
'''

'''
题目描述
王强今天很开心，公司发给N元的年终奖。王强决定把年终奖用于购物，他把想买的物品分为两类：主件与附件，附件是从属于某个主件的，下表就是一些主件与附件的例子：
主件	附件
电脑	打印机，扫描仪
书柜	图书
书桌	台灯，文具
工作椅	无
如果要买归类为附件的物品，必须先买该附件所属的主件。每个主件可以有 0 个、 1 个或 2 个附件。附件不再有从属于自己的附件。王强想买的东西很多，为了不超出预算，他把每件物品规定了一个重要度，分为 5 等：用整数 1 ~ 5 表示，第 5 等最重要。他还从因特网上查到了每件物品的价格（都是 10 元的整数倍）。他希望在不超过 N 元（可以等于 N 元）的前提下，使每件物品的价格与重要度的乘积的总和最大。
    设第 j 件物品的价格为 v[j] ，重要度为 w[j] ，共选中了 k 件物品，编号依次为 j 1 ， j 2 ，……， j k ，则所求的总和为：
v[j 1 ]*w[j 1 ]+v[j 2 ]*w[j 2 ]+ … +v[j k ]*w[j k ] 。（其中 * 为乘号）
    请你帮助王强设计一个满足要求的购物单。
 

输入描述:
输入的第 1 行，为两个正整数，用一个空格隔开：N m
（其中 N （ <32000 ）表示总钱数， m （ <60 ）为希望购买物品的个数。）
从第 2 行到第 m+1 行，第 j 行给出了编号为 j-1 的物品的基本数据，每行有 3 个非负整数 v p 

（其中 v 表示该物品的价格（ v<10000 ）， p 表示该物品的重要度（ 1 ~ 5 ）， q 表示该物品是主件还是附件。如果 q=0 ，表示该物品为主件，如果 q>0 ，表示该物品为附件， q 是所属主件的编号）
 
输出描述:
 输出文件只有一个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值（ <200000 ）。
 '''



while True:
    try:
        f_int = input().split(" ")
        N = int(f_int[0])
        m = int(f_int[1])
        l = [[0]*3 for i in range(m+1)]
        for i in range(m):
            temp = input().split(" ")
            l[i+1][0] = int(temp[0])
            l[i+1][1] = int(temp[1])
            l[i+1][2] = int(temp[2])

        value = []
        for i in range(m+1):
            value.append([0] * (N+1))
        for i in range(1, m+1):
            for j in range(1, N+1):
                if l[i][2] == 0:
                    if l[i][0] <= j:
                        value[i][j] = max(value[i-1][j], l[i][0] * l[i][1] + value[i-1][j-l[i][0]])
                    else:
                        if l[i][0] + l[l[i][2]][0] <= j:
                            value[i][j] = max(value[i - 1][j], l[i][0] * l[i][1] + l[l[i][2]][0] * l[l[i][2]][1] + value[i - 1][j - l[i][0] - l[l[i][2]][0]])
        print(value[m][N])
    except:
        break