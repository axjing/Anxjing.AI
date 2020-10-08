'''
Author: Anxjing.AI
Date: 2020-09-26 11:33:35
LastEditTime: 2020-09-26 11:36:42
LastEditors: Anajing.AI
Description: 
FilePath: \Anxjing.AI\algorithm_note\pythonBook\生产者消费者.py
THIS FILE IS PART OF Anxjing.AI PROJECT
'''
#生产者和消费者，使用生成器的方式，就是一个简单的并行，
import time
# 这是一个消费者 一直在等待完成吃包子的动作
def consumer(name):
    print('%s准备打小三了！'%name)  #打印出对应的消费者的名字
    while True:   #执行一个死循环 实际上就是需要调用时才会执行，没有调用就会停止在yield
        biaozi = yield  #在它就收到内容的时候后就把内容传给baozi
        print('小三【%s】来了，被【%s】打了'%(biaozi,name))
def producer(name):
    c1 = consumer('A')  #它只是把c1变成一个生成器
    c2 = consumer('B')
    c1.__next__() #第一个next只是会走到yield然后停止
    c2.__next__()
    print('婊子开始做小三了')
    for i in range(1,10):
        time.sleep(1)
        print('三年打了两个婊子')
        c1.send(i)  #这一步其实就是调用next方法的同时传一个参数i给field接收，然后baozi=i
        c2.send(i+1)
        #其实这里是这样的，在send的时候只是继续执行yield下面的语句，然后去去yield，再次停在这儿

producer('熊本熊')
c = consumer('光头强') #没next一次就会将程序执行一次
c.__next__()
c.__next__()
c.__next__()

