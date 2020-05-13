'''
@Author: Anxjing.AI
@Date: 2020-05-12 10:05:34
@LastEditTime: 2020-05-12 10:40:12
@LastEditors: Anajing.AI
@Description: 
@FilePath: \Anxjing.AI\algorithm_note\anExams\meituan01.py
@THIS FILE IS PART OF Anxjing.AI PROJECT
'''

def tran(nm_li):
    res_lis = [[nm_li[j][i] for j in range(len(nm_li))] for i in range(len(nm_li[0]))]
    return res_lis


def clac(nm_li):
    nm_lis = tran(nm_li)
    cal_num = 0
    max_l = []
    for i in range(len(nm_lis)):
        max_num = 0
        max_ij = []
        for j in range(len(nm_lis[i])-1):
            if nm_lis[i][j] > nm_lis[i][j+1]:
                max_num = nm_lis[i][j]
                max_ij.append(i)
                max_ij.append(j)
                
            else:
                max_num = nm_lis[i][j+1]
                max_ij.append(i)
                max_ij.append(j+1)
        max_l.append(max_num)
        mi

while True:
    try:
        nm = input().split()
        n = int(nm[0])
        m = int(m[1])
        nm_lis = []
        for i in range(n):
            m_lis = []
            for j in range(m):
                m_j = int(input())
                m_lis.append(m_j)
            nm_lis.append(m_lis)
        
    except:
        break